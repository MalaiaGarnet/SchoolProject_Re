#include "Bitmap_Character.h"



Bitmap_Character::Bitmap_Character(const char* _path)
{
	strcpy_s(m_Path, STRING_SIZE, _path);
	m_Bitmap = (HBITMAP)LoadImage(NULL, m_Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

Bitmap_Character::~Bitmap_Character()
{
	DeleteObject(m_Bitmap);
}

void Bitmap_Character::Draw_Character(HDC _hdc, POINT _pos)
{
	int frame = API_Window_Frame::Get_Instance()->Get_Frame_Tick() % 4;
	HDC memDC = CreateCompatibleDC(_hdc);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(memDC, m_Bitmap);
	HBRUSH myBrush, oldBrush;

	myBrush = CreateSolidBrush(RGB(50, 50, 50));
	oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, _pos.x - CHARA_BITMAP_WIDTH / 2 + 20, _pos.y + CHARA_BITMAP_HEIGHT / 2 - 10, _pos.x + CHARA_BITMAP_WIDTH / 2 - 20, _pos.y + CHARA_BITMAP_HEIGHT / 2);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);

	GdiTransparentBlt(_hdc, _pos.x - CHARA_BITMAP_WIDTH / 2 - 5, _pos.y - CHARA_BITMAP_HEIGHT / 2 - 5, CHARA_BITMAP_WIDTH, CHARA_BITMAP_HEIGHT, memDC,
		CHARA_BITMAP_WIDTH * frame, 0, CHARA_BITMAP_WIDTH, CHARA_BITMAP_HEIGHT, RGB(255, 0, 255));

	SelectObject(memDC, OldBitmap);
	DeleteDC(memDC);
}