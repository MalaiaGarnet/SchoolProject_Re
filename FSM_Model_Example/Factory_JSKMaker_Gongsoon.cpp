#include "Factory_JSKMaker_Gongsoon.h"



Factory_JSKMaker_Gongsoon::Factory_JSKMaker_Gongsoon()
{
}


Factory_JSKMaker_Gongsoon::~Factory_JSKMaker_Gongsoon()
{
}

Data_Item_Weapon* Factory_JSKMaker_Gongsoon::Create_Weapon()
{
	return new Data_Item_Weapon(ItemTable::Weapons[2]);
}

Data_Item_Armor* Factory_JSKMaker_Gongsoon::Create_Armor()
{
	return new Data_Item_Armor(ItemTable::Armors[2]);
}

Data_Item_Accessory* Factory_JSKMaker_Gongsoon::Create_Accessory()
{
	return new Data_Item_Accessory(ItemTable::Accessories[2]);
}
