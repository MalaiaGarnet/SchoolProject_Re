#pragma once
#include "Method_Draw.h"
class Method_Draw_Line : public Method_Draw
{
public:
	Method_Draw_Line(Att_BackBit* _bit, Att_Mouse* _mouse, HWND _hwnd);
	virtual ~Method_Draw_Line();

	virtual void Draw_Start(POINT _pos);		// �׸��� ����, _pos�� ù ��ġ
	virtual void Draw_Move();					// Ŀ�� �̵�
	virtual void Draw_End();						// �׸��� ��
};

