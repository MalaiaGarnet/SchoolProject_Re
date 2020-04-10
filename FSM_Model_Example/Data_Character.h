#pragma once
#include "Global_Info.h"
#include "Template_LinkedList.h"
#include "Factory_JSKMaker.h"
#include "Data_Item_Weapon.h"
#include "Data_Item_Armor.h"
#include "Data_Item_Accessory.h"

class Data_Character
{
private:
	TYPE_RACE m_Race; // 캐릭터의 종족

	char m_Name[STRING_SIZE]; // 이름
	int m_Level; // 레벨
	int m_Currency; // 돈

	// 능력치
	int m_Base_hp;
	int m_Base_atk;
	int m_Base_def;
	int m_Base_dex;
	int m_Base_agi;

	// 장비
	Data_Item_Weapon* m_Weapon;
	Data_Item_Armor* m_Armor;
	Data_Item_Accessory* m_Accessory;

	// 인벤토리
	LinkedList<Data_Item_Weapon*>* m_Weapon_List;
	LinkedList<Data_Item_Armor*>* m_Armor_List;
	LinkedList<Data_Item_Accessory*>* m_Accessory_List;

public:
	Data_Character();
	Data_Character(TYPE_RACE _race, const char* _name, Factory_JSKMaker* _jskMaker);
	~Data_Character();

	TYPE_RACE Get_CharaIndex() { return m_Race; }

	const char* Get_Name() { return m_Name; }
	int Get_Level() { return m_Level; }
	int Get_Currency() { return m_Currency; }
	bool Sub_Currency(int amount);

	int Get_HP();
	int Get_ATK();
	int Get_DEF();
	int Get_DEX();
	int Get_AGI();

	Data_Item_Weapon* Get_Weapon() { return m_Weapon; }
	Data_Item_Armor* Get_Armor() { return m_Armor; }
	Data_Item_Accessory* Get_Accessory() { return m_Accessory; }

	const char* Get_WeaponName() { return m_Weapon != nullptr ? m_Weapon->Get_Name() : "없음"; }
	const char* Get_ArmorName() { return m_Armor != nullptr ? m_Armor->Get_Name() : "없음"; }
	const char* Get_AccessoryName() { return m_Accessory != nullptr ? m_Accessory->Get_Name() : "없음"; }

	const char* Get_WeaponDesc() { return m_Weapon != nullptr ? m_Weapon->Get_Desc() : "없엉"; }
	const char* Get_ArmorDesc() { return m_Armor != nullptr ? m_Armor->Get_Desc() : "없엉"; }
	const char* Get_AccessoryDesc() { return m_Accessory != nullptr ? m_Accessory->Get_Desc() : "없다능"; }

	Data_Item_Weapon* Get_Weapon_In_Inv(int index);
	Data_Item_Armor* Get_Armor_In_Inv(int index);
	Data_Item_Accessory* Get_Accessory_In_Inv(int index);

	int Get_WeaponInv_Size() { return m_Weapon_List->Size(); }
	int Get_ArmorInv_Size() { return m_Armor_List->Size(); }
	int Get_AccessoryInv_Size() { return m_Accessory_List->Size(); }

	// set
	Data_Item_Weapon* Set_Weapon(Data_Item_Weapon* _data)
	{
		Data_Item_Weapon* temp = m_Weapon;
		m_Weapon = _data;
		return temp;
	}
	Data_Item_Armor* Set_Armor(Data_Item_Armor* _data)
	{
		Data_Item_Armor* temp = m_Armor;
		m_Armor = _data;
		return temp;
	}
	Data_Item_Accessory* Set_Accessory(Data_Item_Accessory* _data)
	{
		Data_Item_Accessory* temp = m_Accessory;
		m_Accessory  = _data;
		return temp;
	}

	void Set_WeaponInv_List(LinkedList<Data_Item_Weapon*>* _list);
	void Set_ArmorInv_List(LinkedList<Data_Item_Armor*>* _list);
	void Set_AccessoryInv_List(LinkedList<Data_Item_Accessory*>* _list);

	void Add_Currency(int amount) { m_Currency += amount; }
	void Add_Weapon(Data_Item_Weapon* _data);
	void Add_Armor(Data_Item_Armor* _data);
	void Add_Accessory(Data_Item_Accessory* _data);

	void Remove_Item(Data_Item* _data);
	void Change_Equipment(Data_Item* _data);
};

