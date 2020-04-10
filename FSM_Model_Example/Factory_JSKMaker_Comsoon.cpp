#include "Factory_JSKMaker_Comsoon.h"



Factory_JSKMaker_Comsoon::Factory_JSKMaker_Comsoon()
{
}


Factory_JSKMaker_Comsoon::~Factory_JSKMaker_Comsoon()
{
}

Data_Item_Weapon* Factory_JSKMaker_Comsoon::Create_Weapon()
{
	return new Data_Item_Weapon(ItemTable::Weapons[0]);
}

Data_Item_Armor* Factory_JSKMaker_Comsoon::Create_Armor()
{
	return new Data_Item_Armor(ItemTable::Armors[0]);
}

Data_Item_Accessory* Factory_JSKMaker_Comsoon::Create_Accessory()
{
	return new Data_Item_Accessory(ItemTable::Accessories[0]);
}
