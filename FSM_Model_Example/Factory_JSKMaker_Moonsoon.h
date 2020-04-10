#pragma once
#include "Factory_JSKMaker.h"
class Factory_JSKMaker_Moonsoon : public Factory_JSKMaker
{
public:
	Factory_JSKMaker_Moonsoon();
	virtual ~Factory_JSKMaker_Moonsoon();

	virtual Data_Item_Weapon* Create_Weapon();		// ����
	virtual Data_Item_Armor* Create_Armor();			// ��
	virtual Data_Item_Accessory* Create_Accessory();	// ��ű�
};

