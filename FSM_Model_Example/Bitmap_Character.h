#pragma once
#include <Windows.h>
#include "API_Window_Main.h"

#define CHARA_BITMAP_WIDTH 128
#define CHARA_BITMAP_HEIGHT 64

class Bitmap_Character
{
private:
	char m_Path[STRING_SIZE];
	HBITMAP m_Bitmap;

public:
	Bitmap_Character(const char* _path);
	~Bitmap_Character();

	void Draw_Character(HDC _hdc, POINT _pos);
};

