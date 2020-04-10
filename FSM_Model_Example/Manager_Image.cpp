#include "Manager_Image.h"
#include "Bitmap_Character.h"

// ╫л╠шео
#pragma region SINGLETONE
Manager_Image* Manager_Image::instance = nullptr;

Manager_Image* Manager_Image::Create_Instance()
{
	if (instance == nullptr)
		instance = new Manager_Image();
	return instance;
}

Manager_Image* Manager_Image::Get_Instance()
{
	return instance;
}

void Manager_Image::Release_Instance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

#pragma endregion

Manager_Image::Manager_Image()
{
	race_chara[0] = new Bitmap_Character("1_normal.bmp");
	race_chara[1] = new Bitmap_Character("2_normal.bmp");
	race_chara[2] = new Bitmap_Character("3_normal.bmp");
}


Manager_Image::~Manager_Image()
{
	delete race_chara[0];
	delete race_chara[1];
	delete race_chara[2];
}
