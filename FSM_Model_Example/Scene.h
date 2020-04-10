#pragma once
#include <Windows.h>
#include "Global_Info.h"
#include "Att_BackBit.h"


/*
	��
	�޼ҵ��� ������ ������ Ŭ����
*/
class Scene
{
protected:
	HWND m_Hwnd;
	Att_BackBit* m_Backbit;

public:
	Scene(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene();

	virtual void Initialize() = 0; // �� �ʱ�ȭ, Add �� �� �ߵ�
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam) = 0; // �� �⵿, Run �� �� �ߵ�
};