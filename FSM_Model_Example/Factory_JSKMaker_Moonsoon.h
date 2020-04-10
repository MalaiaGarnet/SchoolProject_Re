#pragma once
#include "Factory_JSKMaker.h"
class Factory_JSKMaker_Moonsoon : public Factory_JSKMaker
{
public:
	Factory_JSKMaker_Moonsoon();
	virtual ~Factory_JSKMaker_Moonsoon();

	virtual Data_Item_Weapon* Create_Weapon();		// 公扁
	virtual Data_Item_Armor* Create_Armor();			// 规绢备
	virtual Data_Item_Accessory* Create_Accessory();	// 厘脚备
};

