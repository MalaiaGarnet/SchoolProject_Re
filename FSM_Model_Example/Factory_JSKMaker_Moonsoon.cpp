#include "Factory_JSKMaker_Moonsoon.h"



Factory_JSKMaker_Moonsoon::Factory_JSKMaker_Moonsoon()
{
}


Factory_JSKMaker_Moonsoon::~Factory_JSKMaker_Moonsoon()
{
}

Data_Item_Weapon* Factory_JSKMaker_Moonsoon::Create_Weapon()
{
	return new Data_Item_Weapon(ItemTable::Weapons[1]);
}

Data_Item_Armor* Factory_JSKMaker_Moonsoon::Create_Armor()
{
	return new Data_Item_Armor(ItemTable::Armors[1]);
}

Data_Item_Accessory* Factory_JSKMaker_Moonsoon::Create_Accessory()
{
	return new Data_Item_Accessory(ItemTable::Accessories[1]);
}
