#include "Data_Item.h"



Data_Item::Data_Item()
{
	strcpy_s(m_Name, STRING_SIZE, "");
	strcpy_s(m_Desc, STRING_SIZE, "");
	m_Price = 0;

	m_Icon_Index = 0;
	m_HP = 0;
	m_Atk = 0;
	m_Def = 0;
	m_Dex = 0;
	m_Agi = 0;
}

Data_Item::Data_Item(const char* _name, const char* _desc, int _price, int _icon_index, int _hp, int _atk, int _def, int _dex, int _agi)
{
	strcpy_s(m_Name, STRING_SIZE, _name);
	strcpy_s(m_Desc, STRING_SIZE * 2, _desc);
	m_Price = _price;

	m_Icon_Index = _icon_index;
	m_HP = _hp;
	m_Atk = _atk;
	m_Def = _def;
	m_Dex = _dex;
	m_Agi = _agi;
}


Data_Item::~Data_Item()
{
}
