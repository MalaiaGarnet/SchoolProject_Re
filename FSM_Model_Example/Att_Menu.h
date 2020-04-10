#pragma once
#include <Windows.h>
#include "resource.h"

enum DRAW_TYPE { NONE, FREELINE, LINE, SQUARE, CIRCLE };

class Att_Menu
{
private:
	int m_MenuIndex; // 메뉴 인덱스값 (IDR_MENU1 등)
	DRAW_TYPE m_DrawType; // 그리기 타입
	
public:
	Att_Menu(int _index);
	~Att_Menu();

	void Process(WPARAM _wparam);

	const int Get_MenuIndex() { return m_MenuIndex; }
	const DRAW_TYPE Get_DrawType() { return m_DrawType; }
};

