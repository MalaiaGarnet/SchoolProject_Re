#include "Method_Draw.h"

Method_Draw::Method_Draw(Att_BackBit* _bit, Att_Mouse* _mouse, HWND _hwnd)
{
	m_Backbit = _bit;
	m_Mouse = _mouse;
	hwnd = _hwnd;
	m_First_Pos = { 0, 0 };
}

Method_Draw::~Method_Draw()
{
}
