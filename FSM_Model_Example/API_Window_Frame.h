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
	윈도우 프레임 클래스
	윈도우의 표현을 담당한다
	Window_Main이 만들어지는 시점에서 같이 만들어진다
*/

class API_Window_Frame
{
	static API_Window_Frame* instance;

	// 멤버 변수
	HINSTANCE hInst;
	HWND hWnd;
	int frame_tick;

	API_Window_Frame() {}
	~API_Window_Frame() {}
public:
	// 싱글턴 함수
	static API_Window_Frame* Create_Instance();
	static API_Window_Frame* Get_Instance();
	static void Release_Instance();

	void Initialize(HINSTANCE _inst); // 윈도우를 구성한다
	int Run(MSG _msg); // 윈도우를 굴린다

	int Get_Frame_Tick() { return frame_tick; }

	// 굴리는데 쓰일 프로시저
	static LRESULT CALLBACK Process(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

