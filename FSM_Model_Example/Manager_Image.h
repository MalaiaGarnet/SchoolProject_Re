#pragma once
#include "Global_Info.h"

class Bitmap_Character;

/*
	이미지 매니저
	게임 내 비트맵 이미지를 관리한다
*/
class Manager_Image
{
private:
	static Manager_Image* instance;

	// 보여주기용 이미지들
	Bitmap_Character* race_chara[3];

	Manager_Image();
	~Manager_Image();
public:
	// 싱글턴 함수
	static Manager_Image* Create_Instance();
	static Manager_Image* Get_Instance();
	static void Release_Instance();

	Bitmap_Character* Get_CharaBitmap(TYPE_RACE _race) { return race_chara[_race]; }
};

