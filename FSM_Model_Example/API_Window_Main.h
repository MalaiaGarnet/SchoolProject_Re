#pragma once
#include <Windows.h>

#include "API_Window_Frame.h"

#include "Manager_File.h"
#include "Manager_Data.h"
#include "Manager_Scene.h"
#include "Manager_Image.h"

#include "Att_Mouse.h"
#include "Att_BackBit.h"

/*
	메인 클래스
	윈도우 관리를 맡는다
*/
class API_Window_Main
{
private:
	static API_Window_Main* instance;

	API_Window_Main() {}
	~API_Window_Main() {}
public:
	// 멤버 변수
	HINSTANCE hInst;
	// 싱글턴 함수
	static API_Window_Main* Create_Instance();
	static API_Window_Main* Get_Instance();
	static void Release_Instance();

	void Initialize(); // 윈도우 구성
	int Run(); // 윈도우 굴리기
};

