#pragma once
#include <Windows.h>
#include "Global_Info.h"
#include "Att_BackBit.h"


/*
	씬
	메소드의 역할을 가지는 클래스
*/
class Scene
{
protected:
	HWND m_Hwnd;
	Att_BackBit* m_Backbit;

public:
	Scene(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene();

	virtual void Initialize() = 0; // 씬 초기화, Add 할 때 발동
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam) = 0; // 씬 기동, Run 할 때 발동
};