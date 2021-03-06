#pragma once
#include "ItemTable.h"

class Factory_JSKMaker
{
public:
	Factory_JSKMaker();
	virtual ~Factory_JSKMaker();

	virtual Data_Item_Weapon* Create_Weapon() = 0;		// 무기
	virtual Data_Item_Armor* Create_Armor() = 0;			// 방어구
	virtual Data_Item_Accessory* Create_Accessory() = 0;		// 장신구
};

