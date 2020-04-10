#pragma once
#include "Global_Info.h"

class Data_Item
{
protected:
	char m_Name[STRING_SIZE];
	char m_Desc[STRING_SIZE * 2];
	int m_Price;
	int m_Icon_Index;
	int m_HP;
	int m_Atk;
	int m_Def;
	int m_Dex;
	int m_Agi;

public:
	Data_Item();
	Data_Item(const char* _name, const char* _desc, int _price, int _icon_index, int _hp, int _atk, int _def, int _dex, int _agi);
	~Data_Item();

	virtual const char* Get_Category() = 0;
	const char* Get_Name() { return m_Name; }
	const char* Get_Desc() { return m_Desc; }
	int Get_Price() { return m_Price; }

	int Get_Icon_Index() { return m_Icon_Index; }
	int Get_Additive_HP() { return m_HP; }
	int Get_Additive_Atk() { return m_Atk; }
	int Get_Additive_Def() { return m_Def; }
	int Get_Additive_Dex() { return m_Dex; }
	int Get_Additive_Agi() { return m_Agi; }
};