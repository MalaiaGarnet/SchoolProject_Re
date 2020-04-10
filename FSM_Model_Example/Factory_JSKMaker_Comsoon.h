#pragma once
#include "Factory_JSKMaker.h"
class Factory_JSKMaker_Comsoon : public Factory_JSKMaker
{
public:
	Factory_JSKMaker_Comsoon();
	virtual ~Factory_JSKMaker_Comsoon();

	virtual Data_Item_Weapon* Create_Weapon();		// 무기
	virtual Data_Item_Armor* Create_Armor();			// 방어구
	virtual Data_Item_Accessory* Create_Accessory();	// 장신구
};

