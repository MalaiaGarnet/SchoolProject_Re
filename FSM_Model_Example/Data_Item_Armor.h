#pragma once
#include "Data_Item.h"
class Data_Item_Armor : public Data_Item
{
public:
	Data_Item_Armor();
	Data_Item_Armor(const char* _name, const char* _desc, int _price, int _icon_index, int _hp, int _atk, int _def, int _dex, int _agi)
		: Data_Item(_name, _desc, _price, _icon_index, _hp, _atk, _def, _dex, _agi) {}
	virtual ~Data_Item_Armor();

	virtual const char* Get_Category() { return "��"; };
};

