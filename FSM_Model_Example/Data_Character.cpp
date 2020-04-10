#include "Data_Character.h"


Data_Character::Data_Character()
{
	m_Race = TYPE_RACE::COMSOON;

	strcpy_s(m_Name, STRING_SIZE, "");
	m_Level = 1;
	m_Currency = 10000;

	m_Base_hp = 100;
	m_Base_atk = 5;
	m_Base_def = 5;
	m_Base_dex = 5;
	m_Base_agi = 5;

	m_Weapon = nullptr;
	m_Armor = nullptr;
	m_Accessory = nullptr;

	m_Weapon_List = new LinkedList<Data_Item_Weapon*>();
	m_Armor_List = new LinkedList<Data_Item_Armor*>();
	m_Accessory_List = new LinkedList<Data_Item_Accessory*>();
}

Data_Character::Data_Character(TYPE_RACE _race, const char* _name, Factory_JSKMaker* _jskMaker)
{
	m_Race = _race;

	strcpy_s(m_Name, STRING_SIZE, _name);
	m_Level = 1;
	m_Currency = 10000;

	m_Base_hp = 100;
	m_Base_atk = 5;
	m_Base_def = 5;
	m_Base_dex = 5;
	m_Base_agi = 5;

	if (_jskMaker != nullptr)
	{
		m_Weapon = _jskMaker->Create_Weapon();
		m_Armor = _jskMaker->Create_Armor();
		m_Accessory = _jskMaker->Create_Accessory();
		delete _jskMaker;
	}
	else
	{
		m_Weapon = nullptr;
		m_Armor = nullptr;
		m_Accessory = nullptr;
	}

	m_Weapon_List = new LinkedList<Data_Item_Weapon*>();
	m_Armor_List = new LinkedList<Data_Item_Armor*>();
	m_Accessory_List = new LinkedList<Data_Item_Accessory*>();
}


Data_Character::~Data_Character()
{
	
	if (m_Weapon != nullptr)
		delete m_Weapon;
	if (m_Armor != nullptr)
		delete m_Armor;
	if (m_Accessory != nullptr)
		delete m_Accessory;
		
}

bool Data_Character::Sub_Currency(int amount)
{
	if (m_Currency - amount < 0)
		return false;
	m_Currency -= amount;
	return true;
}

int Data_Character::Get_HP()
{
	int hp = m_Base_hp;
	if (m_Weapon != nullptr)
		hp += m_Weapon->Get_Additive_HP();
	if (m_Armor != nullptr)
		hp += m_Armor->Get_Additive_HP();
	if (m_Accessory != nullptr)
		hp += m_Accessory->Get_Additive_HP();
	return hp;
}

int Data_Character::Get_ATK()
{
	int atk = m_Base_atk;
	if (m_Weapon != nullptr)
		atk += m_Weapon->Get_Additive_Atk();
	if (m_Armor != nullptr)
		atk += m_Armor->Get_Additive_Atk();
	if (m_Accessory != nullptr)
		atk += m_Accessory->Get_Additive_Atk();
	return atk;
}

int Data_Character::Get_DEF()
{
	int def = m_Base_def;
	if (m_Weapon != nullptr)
		def += m_Weapon->Get_Additive_Def();
	if (m_Armor != nullptr)
		def += m_Armor->Get_Additive_Def();
	if (m_Accessory != nullptr)
		def += m_Accessory->Get_Additive_Def();
	return def;
}

int Data_Character::Get_DEX()
{
	int dex = m_Base_dex;
	if (m_Weapon != nullptr)
		dex += m_Weapon->Get_Additive_Dex();
	if (m_Armor != nullptr)
		dex += m_Armor->Get_Additive_Dex();
	if (m_Accessory != nullptr)
		dex += m_Accessory->Get_Additive_Dex();
	return dex;
}

int Data_Character::Get_AGI()
{
	int agi = m_Base_agi;
	if (m_Weapon != nullptr)
		agi += m_Weapon->Get_Additive_Agi();
	if (m_Armor != nullptr)
		agi += m_Armor->Get_Additive_Agi();
	if (m_Accessory != nullptr)
		agi += m_Accessory->Get_Additive_Agi();
	return agi;
}

Data_Item_Weapon* Data_Character::Get_Weapon_In_Inv(int index)
{
	if (index < 0) return nullptr;

	ListNode<Data_Item_Weapon*>* node = m_Weapon_List->Get_Head();

	for (int i = 0; i <= index; i++)
	{
		node = node->m_Next;
		if (node == nullptr)
			return nullptr;
	}
	return node->m_Data;
}

Data_Item_Armor* Data_Character::Get_Armor_In_Inv(int index)
{
	if (index < 0) return nullptr;

	ListNode<Data_Item_Armor*>* node = m_Armor_List->Get_Head();

	for (int i = 0; i <= index; i++)
	{
		node = node->m_Next;
		if (node == nullptr)
			return nullptr;
	}
	return node->m_Data;
}

Data_Item_Accessory* Data_Character::Get_Accessory_In_Inv(int index)
{
	if (index < 0) return nullptr;

	ListNode<Data_Item_Accessory*>* node = m_Accessory_List->Get_Head();

	for (int i = 0; i <= index; i++)
	{
		node = node->m_Next;
		if (node == nullptr)
			return nullptr;
	}
	return node->m_Data;
}

void Data_Character::Set_WeaponInv_List(LinkedList<Data_Item_Weapon*>* _list)
{
	//if (m_Weapon_List != nullptr)
	//	delete m_Weapon_List;

	m_Weapon_List = _list;
}

void Data_Character::Set_ArmorInv_List(LinkedList<Data_Item_Armor*> * _list)
{
	//if (m_Armor_List != nullptr)
	//	delete m_Armor_List;

	m_Armor_List = _list;
}

void Data_Character::Set_AccessoryInv_List(LinkedList<Data_Item_Accessory*> * _list)
{
	//if (m_Accessory_List != nullptr)
	//	delete m_Accessory_List;

	m_Accessory_List = _list;
}

void Data_Character::Add_Weapon(Data_Item_Weapon* _data)
{
	m_Weapon_List->Insert(_data);
}

void Data_Character::Add_Armor(Data_Item_Armor* _data)
{
	m_Armor_List->Insert(_data);
}

void Data_Character::Add_Accessory(Data_Item_Accessory* _data)
{
	m_Accessory_List->Insert(_data);
}

void Data_Character::Remove_Item(Data_Item* _data)
{
	// 무기인지 체크
	Data_Item_Weapon* weapon = dynamic_cast<Data_Item_Weapon*>(_data);
	if (weapon != nullptr)
		m_Weapon_List->Delete(weapon);

	// 방어구인지 체크
	Data_Item_Armor * armor = dynamic_cast<Data_Item_Armor*>(_data);
	if (armor != nullptr)
		m_Armor_List->Delete(armor);

	// 장신구인지 체크
	Data_Item_Accessory * accessory = dynamic_cast<Data_Item_Accessory*>(_data);
	if (accessory != nullptr)
		m_Accessory_List->Delete(accessory);
}

void Data_Character::Change_Equipment(Data_Item* _data)
{
	// 무기인지 체크
	Data_Item_Weapon* weapon = dynamic_cast<Data_Item_Weapon*>(_data);
	if (weapon != nullptr)
		m_Weapon_List->Insert(Set_Weapon(weapon));

	// 방어구인지 체크
	Data_Item_Armor * armor = dynamic_cast<Data_Item_Armor*>(_data);
	if (armor != nullptr)
		m_Armor_List->Insert(Set_Armor(armor));

	// 장신구인지 체크
	Data_Item_Accessory * accessory = dynamic_cast<Data_Item_Accessory*>(_data);
	if (accessory != nullptr)
		m_Accessory_List->Insert(Set_Accessory(accessory));
}
