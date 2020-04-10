#pragma once
#include <Windows.h>
#include "resource.h"
#include "Att_Menu.h"
#include "Att_Mouse.h"
#include "Att_Backbit.h"
#include "Method_Draw_Line.h"

#include "Manager_Scene.h"
#include "Scene_Title.h"

/*
	������ ������ Ŭ����
	�������� ǥ���� ����Ѵ�
	Window_Main�� ��������� �������� ���� ���������
*/

class API_Window_Frame
{
	static API_Window_Frame* instance;

	// ��� ����
	HINSTANCE hInst;
	HWND hWnd;
	int frame_tick;

	API_Window_Frame() {}
	~API_Window_Frame() {}
public:
	// �̱��� �Լ�
	static API_Window_Frame* Create_Instance();
	static API_Window_Frame* Get_Instance();
	static void Release_Instance();

	void Initialize(HINSTANCE _inst); // �����츦 �����Ѵ�
	int Run(MSG _msg); // �����츦 ������

	int Get_Frame_Tick() { return frame_tick; }

	// �����µ� ���� ���ν���
	static LRESULT CALLBACK Process(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

