#pragma once
#include <Windows.h>
#include "Att_Mouse.h"
#include "Att_BackBit.h"

class Method_Draw
{
protected:
	POINT m_First_Pos;
	HWND hwnd;
	Att_BackBit* m_Backbit;
	Att_Mouse* m_Mouse;

public:
	Method_Draw(Att_BackBit* _bit, Att_Mouse* _mouse, HWND _hwnd);
	virtual ~Method_Draw();

	virtual void Draw_Start(POINT _pos) {};		// �׸��� ����, _pos�� ù ��ġ
	virtual void Draw_Move() {};					// Ŀ�� �̵�
	virtual void Draw_End() {};						// �׸��� ��
};

