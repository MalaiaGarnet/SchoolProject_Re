#pragma once

#include "Global_Info.h"
#include "Data_Item_Weapon.h"
#include "Data_Item_Armor.h"
#include "Data_Item_Accessory.h"


class ItemTable
{
public:
	static int Weapon_Size;
	static int Armor_Size;
	static int Accessories_Size;

	static const Data_Item_Weapon Weapons[];
	static const Data_Item_Armor Armors[];
	static const Data_Item_Accessory Accessories[];
};