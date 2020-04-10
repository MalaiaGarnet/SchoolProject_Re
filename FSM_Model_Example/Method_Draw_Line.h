#pragma once
#include "Method_Draw.h"
class Method_Draw_Line : public Method_Draw
{
public:
	Method_Draw_Line(Att_BackBit* _bit, Att_Mouse* _mouse, HWND _hwnd);
	virtual ~Method_Draw_Line();

	virtual void Draw_Start(POINT _pos);		// 그리기 시작, _pos는 첫 위치
	virtual void Draw_Move();					// 커서 이동
	virtual void Draw_End();						// 그리기 끝
};

