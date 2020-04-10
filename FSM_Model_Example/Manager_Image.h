#pragma once
#include "Global_Info.h"

class Bitmap_Character;

/*
	�̹��� �Ŵ���
	���� �� ��Ʈ�� �̹����� �����Ѵ�
*/
class Manager_Image
{
private:
	static Manager_Image* instance;

	// �����ֱ�� �̹�����
	Bitmap_Character* race_chara[3];

	Manager_Image();
	~Manager_Image();
public:
	// �̱��� �Լ�
	static Manager_Image* Create_Instance();
	static Manager_Image* Get_Instance();
	static void Release_Instance();

	Bitmap_Character* Get_CharaBitmap(TYPE_RACE _race) { return race_chara[_race]; }
};

