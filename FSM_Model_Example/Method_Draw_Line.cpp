#include "Method_Draw_Line.h"



Method_Draw_Line::Method_Draw_Line(Att_BackBit* _bit, Att_Mouse* _mouse, HWND _hwnd) : Method_Draw(_bit, _mouse, _hwnd)
{
}

Method_Draw_Line::~Method_Draw_Line()
{
}

void Method_Draw_Line::Draw_Start(POINT _pos)
{
	m_First_Pos = _pos;
}

void Method_Draw_Line::Draw_Move()
{
	HDC hdc = m_Backbit->GetBitmapDC();
	POINT before_point = m_Mouse->Get_BeforeCoord(hwnd);
	POINT current_point = m_Mouse->Get_CurrentCoord(hwnd);

	SetROP2(hdc, R2_NOT);

	// 이전 직선을 지우기
	MoveToEx(hdc, m_First_Pos.x, m_First_Pos.y, NULL);
	LineTo(hdc, before_point.x, before_point.y);

	// 현재 직선을 그리기
	MoveToEx(hdc, m_First_Pos.x, m_First_Pos.y, NULL);
	LineTo(hdc, current_point.x, current_point.y);

	m_Backbit->DeleteBitmapDC(hdc);
	InvalidateRect(hwnd, NULL, false);
}

void Method_Draw_Line::Draw_End()
{
	HDC hdc = m_Backbit->GetBitmapDC();
	POINT current_point = m_Mouse->Get_CurrentCoord(hwnd);
	MoveToEx(hdc, m_First_Pos.x, m_First_Pos.y, NULL);
	LineTo(hdc, current_point.x, current_point.y);
	m_Backbit->DeleteBitmapDC(hdc);
	InvalidateRect(hwnd, NULL, false);
}
