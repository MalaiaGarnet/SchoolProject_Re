#include "Manager_File.h"


// 싱글턴
#pragma region SINGLETONE

Manager_File* Manager_File::instance = nullptr;

Manager_File* Manager_File::Create_Instance()
{
	if (instance == nullptr)
		instance = new Manager_File();
	return instance;
}

Manager_File* Manager_File::Get_Instance()
{
	return instance;
}

void Manager_File::Release_Instance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

#pragma endregion



Manager_File::Manager_File()
{
}


Manager_File::~Manager_File()
{
}

LinkedList<Data_User*>* Manager_File::Load_Data()
{
	LinkedList<Data_User*>* list = new LinkedList<Data_User*>();
	FILE* fp = nullptr;
	fopen_s(&fp, "user_data.sav", "rb");
	if (fp == nullptr)
	{
		return list;
	}

	while (1)
	{
		char temp_id[STRING_SIZE];
		char temp_pass[STRING_SIZE];
		bool temp_prologue;
		int temp_charalist_size;				// 캐릭터 리스트 사이즈
		LinkedList<Data_Character*>* temp_charalist = new LinkedList<Data_Character*>();			// 캐릭터 리스 

		fread(temp_id, sizeof(char[STRING_SIZE]), 1, fp);			// ID
		fread(temp_pass, sizeof(char[STRING_SIZE]), 1, fp);		// Pass
		fread(&temp_prologue, sizeof(bool), 1, fp);					// 프롤로그

		fread(&temp_charalist_size, sizeof(int), 1, fp);				// 캐릭터 리스트 사이즈
		if (feof(fp))
		{
			break;
		}
		for (int i = 0; i < temp_charalist_size; i++)						// 캐릭터 리스트, 모든 캐릭터를 반복
		{
			cout << i << endl;
			Data_Character* chara = new Data_Character();
			int temp_weaponlist_size;			// 무기 리스트 사이즈
			int temp_armorlist_size;				// 방어구 리스트 사이즈
			int temp_accessorylist_size;			// 장신구 리스트 사이즈
			LinkedList<Data_Item_Weapon*>* temp_weaponlist = new LinkedList<Data_Item_Weapon*>();			// 무기 리스트
			LinkedList<Data_Item_Armor*>* temp_armorlist = new LinkedList<Data_Item_Armor*>();					// 방어구 리스트
			LinkedList<Data_Item_Accessory*>* temp_accessorylist = new LinkedList<Data_Item_Accessory*>();	// 장신구 리스트

			// 캐릭터 정보
			fread(chara, 1, sizeof(Data_Character), fp);

			// 장비
			chara->Set_Weapon(Read_Weapon(fp));
			chara->Set_Armor(Read_Armor(fp));
			chara->Set_Accessory(Read_Accessory(fp));

			// 인벤토리
			fread(&temp_weaponlist_size, sizeof(int), 1, fp);			// 무기 리스트 사이즈
			fread(&temp_armorlist_size, sizeof(int), 1, fp);				// 방어구 리스트 사이즈
			fread(&temp_accessorylist_size, sizeof(int), 1, fp);			// 장신구 리스트 사이즈

			for (int i = 0; i < temp_weaponlist_size; i++)						// 무기 리스트
				temp_weaponlist->Insert(Read_Weapon(fp));
			for (int i = 0; i < temp_armorlist_size; i++)						// 방어구 리스트
				temp_armorlist->Insert(Read_Armor(fp));
			for (int i = 0; i < temp_accessorylist_size; i++)						// 장신구 리스트
				temp_accessorylist->Insert(Read_Accessory(fp));

			chara->Set_WeaponInv_List(temp_weaponlist);
			chara->Set_ArmorInv_List(temp_armorlist);
			chara->Set_AccessoryInv_List(temp_accessorylist);

			temp_charalist->Insert(chara);
			//delete chara;
		}


		Data_User* ptr = new Data_User(temp_id, temp_pass);
		ptr->Set_Prologue(temp_prologue);
		ptr->Set_Character_List(temp_charalist);
		//memcpy(ptr, &info, sizeof(Data_User));

		list->Insert(ptr);
	}
	fclose(fp);
	return list;
}

void Manager_File::Save_Data(LinkedList<Data_User*>* _user_list)
{
	FILE* fp = nullptr;
	
	remove("user_data.sav");
	fopen_s(&fp, "user_data.sav", "wb");
	if (fp == nullptr) return;

	for (ListNode<Data_User*>* node = _user_list->Get_Head()->m_Next; node != nullptr; node = node->m_Next)
	{
		Data_User* user = node->m_Data;
		int temp_charalist_size = user->Get_Character_Size();

		fwrite(user->Get_ID(), 1, sizeof(char[STRING_SIZE]), fp);				// ID
		fwrite(user->Get_Password(), 1, sizeof(char[STRING_SIZE]), fp);	// PASS
		fwrite(user->Get_Prologue_Buffer(), 1, sizeof(bool), fp);				// PROLOGUE

		fwrite(&temp_charalist_size, 1, sizeof(int), fp);							// 캐릭터 리스트 크기
		for (int i = 0; i < temp_charalist_size; i++)						// 캐릭터 리스트, 캐릭터마다 반복
		{
			Data_Character* chara = user->Get_Character(i);
			if (chara != nullptr)
			{
				int temp_weaponlist_size = chara->Get_WeaponInv_Size();
				int temp_armorlist_size = chara->Get_ArmorInv_Size();
				int temp_accessorylist_size = chara->Get_AccessoryInv_Size();

				// 캐릭터 정보
				fwrite(chara, 1, sizeof(Data_Character), fp);

				// 장비
				Write_Weapon(chara->Get_Weapon(), fp);
				Write_Armor(chara->Get_Armor(), fp);
				Write_Accessory(chara->Get_Accessory(), fp);

				// 인벤토리
				fwrite(&temp_weaponlist_size, 1, sizeof(int), fp);						// 무기 리스트 크기
				fwrite(&temp_armorlist_size, 1, sizeof(int), fp);							// 방어구 리스트 크기
				fwrite(&temp_accessorylist_size, 1, sizeof(int), fp);					// 장신구 리스트 크기

				for (int i = 0; i < temp_weaponlist_size; i++)								// 무기 리스트
				{
					Data_Item_Weapon* data = chara->Get_Weapon_In_Inv(i);
					if (data != nullptr)
						Write_Weapon(data, fp);
				}
				for (int i = 0; i < temp_armorlist_size; i++)								// 방어구 리스트
				{
					Data_Item_Armor* data = chara->Get_Armor_In_Inv(i);
					if (data != nullptr)
						Write_Armor(data, fp);
				}
				for (int i = 0; i < temp_accessorylist_size; i++)							// 장신구 리스트
				{
					Data_Item_Accessory* data = chara->Get_Accessory_In_Inv(i);
					if (data != nullptr)
						Write_Accessory(data, fp);
				}
			}
		}
	}
}

void Manager_File::Write_Weapon(Data_Item_Weapon* weapon, FILE* fp)
{
	int price = weapon->Get_Price();
	int icon_Index = weapon->Get_Icon_Index();
	int hp = weapon->Get_Additive_HP();
	int atk = weapon->Get_Additive_Atk();
	int def = weapon->Get_Additive_Def();
	int dex = weapon->Get_Additive_Dex();
	int agi = weapon->Get_Additive_Agi();

	fwrite(weapon->Get_Name(), 1, sizeof(char[STRING_SIZE]), fp);
	fwrite(weapon->Get_Desc(), 1, sizeof(char[STRING_SIZE * 2]), fp);

	fwrite(&price, 1, sizeof(int), fp);
	fwrite(&icon_Index, 1, sizeof(int), fp);
	fwrite(&hp, 1, sizeof(int), fp);
	fwrite(&atk, 1, sizeof(int), fp);
	fwrite(&def, 1, sizeof(int), fp);
	fwrite(&dex, 1, sizeof(int), fp);
	fwrite(&agi, 1, sizeof(int), fp);
}

void Manager_File::Write_Armor(Data_Item_Armor* armor, FILE* fp)
{
	int price = armor->Get_Price();
	int icon_Index = armor->Get_Icon_Index();
	int hp = armor->Get_Additive_HP();
	int atk = armor->Get_Additive_Atk();
	int def = armor->Get_Additive_Def();
	int dex = armor->Get_Additive_Dex();
	int agi = armor->Get_Additive_Agi();

	fwrite(armor->Get_Name(), 1, sizeof(char[STRING_SIZE]), fp);
	fwrite(armor->Get_Desc(), 1, sizeof(char[STRING_SIZE * 2]), fp);

	fwrite(&price, 1, sizeof(int), fp);
	fwrite(&icon_Index, 1, sizeof(int), fp);
	fwrite(&hp, 1, sizeof(int), fp);
	fwrite(&atk, 1, sizeof(int), fp);
	fwrite(&def, 1, sizeof(int), fp);
	fwrite(&dex, 1, sizeof(int), fp);
	fwrite(&agi, 1, sizeof(int), fp);
}

void Manager_File::Write_Accessory(Data_Item_Accessory* accessory, FILE* fp)
{
	int price = accessory->Get_Price();
	int icon_Index = accessory->Get_Icon_Index();
	int hp = accessory->Get_Additive_HP();
	int atk = accessory->Get_Additive_Atk();
	int def = accessory->Get_Additive_Def();
	int dex = accessory->Get_Additive_Dex();
	int agi = accessory->Get_Additive_Agi();

	fwrite(accessory->Get_Name(), 1, sizeof(char[STRING_SIZE]), fp);
	fwrite(accessory->Get_Desc(), 1, sizeof(char[STRING_SIZE * 2]), fp);

	fwrite(&price, 1, sizeof(int), fp);
	fwrite(&icon_Index, 1, sizeof(int), fp);
	fwrite(&hp, 1, sizeof(int), fp);
	fwrite(&atk, 1, sizeof(int), fp);
	fwrite(&def, 1, sizeof(int), fp);
	fwrite(&dex, 1, sizeof(int), fp);
	fwrite(&agi, 1, sizeof(int), fp);
}

Data_Item_Weapon* Manager_File::Read_Weapon(FILE* fp)
{
	char name[STRING_SIZE];
	char desc[STRING_SIZE * 2];
	int price = 0;
	int icon_Index = 0;
	int hp = 0;
	int atk = 0;
	int def = 0;
	int dex = 0;
	int agi = 0;

	fread(name, sizeof(char[STRING_SIZE]), 1, fp);
	fread(desc, sizeof(char[STRING_SIZE * 2]), 1, fp);
	fread(&price, sizeof(int), 1, fp);
	fread(&icon_Index, 1, sizeof(int), fp);
	fread(&hp, sizeof(int), 1, fp);
	fread(&atk, sizeof(int), 1, fp);
	fread(&def, sizeof(int), 1, fp);
	fread(&dex, sizeof(int), 1, fp);
	fread(&agi, sizeof(int), 1, fp);

	Data_Item_Weapon* weapon = new Data_Item_Weapon(name, desc, price, icon_Index, hp, atk, def, dex, agi);
	return weapon;
}

Data_Item_Armor* Manager_File::Read_Armor(FILE* fp)
{
	char name[STRING_SIZE];
	char desc[STRING_SIZE * 2];
	int price = 0;
	int icon_Index = 0;
	int hp = 0;
	int atk = 0;
	int def = 0;
	int dex = 0;
	int agi = 0;

	fread(name, sizeof(char[STRING_SIZE]), 1, fp);
	fread(desc, sizeof(char[STRING_SIZE * 2]), 1, fp);
	fread(&price, sizeof(int), 1, fp);
	fread(&icon_Index, 1, sizeof(int), fp);
	fread(&hp, sizeof(int), 1, fp);
	fread(&atk, sizeof(int), 1, fp);
	fread(&def, sizeof(int), 1, fp);
	fread(&dex, sizeof(int), 1, fp);
	fread(&agi, sizeof(int), 1, fp);

	Data_Item_Armor* armor = new Data_Item_Armor(name, desc, price, icon_Index, hp, atk, def, dex, agi);
	return armor;
}

Data_Item_Accessory* Manager_File::Read_Accessory(FILE* fp)
{
	char name[STRING_SIZE];
	char desc[STRING_SIZE * 2];
	int price = 0;
	int icon_Index = 0;
	int hp = 0;
	int atk = 0;
	int def = 0;
	int dex = 0;
	int agi = 0;

	fread(name, sizeof(char[STRING_SIZE]), 1, fp);
	fread(desc, sizeof(char[STRING_SIZE * 2]), 1, fp);
	fread(&price, sizeof(int), 1, fp);
	fread(&icon_Index, 1, sizeof(int), fp);
	fread(&hp, sizeof(int), 1, fp);
	fread(&atk, sizeof(int), 1, fp);
	fread(&def, sizeof(int), 1, fp);
	fread(&dex, sizeof(int), 1, fp);
	fread(&agi, sizeof(int), 1, fp);

	Data_Item_Accessory* accessory = new Data_Item_Accessory(name, desc, price, icon_Index, hp, atk, def, dex, agi);
	return accessory;
}
