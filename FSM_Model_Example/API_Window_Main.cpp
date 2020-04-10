#include "API_Window_Main.h"


// 싱글턴
API_Window_Main* API_Window_Main::instance = nullptr;

API_Window_Main* API_Window_Main::Create_Instance()
{
	if(instance == nullptr)
		instance = new API_Window_Main();

	// 자신이 만들어짐과 동시에 관리할 윈도우, 요소를 생성
	API_Window_Frame::Create_Instance();
	Att_Mouse::Create_Instance();

	// 매니저 만들기
	Manager_Data::Create_Instance();
	Manager_File::Create_Instance();
	Manager_Scene::Create_Instance();
	Manager_Image::Create_Instance();

	return instance;
}

API_Window_Main* API_Window_Main::Get_Instance()
{
	return instance;
}

void API_Window_Main::Release_Instance()
{
	Manager_Data::Get_Instance()->Save_All_Datas();

	// 자신이 제거되기 전 관리했던 윈도우들, 요소를 제거
	API_Window_Frame::Release_Instance();
	Att_Mouse::Release_Instance();

	// 매니저 치우기
	Manager_Data::Release_Instance();
	Manager_File::Release_Instance();
	Manager_Scene::Release_Instance();
	Manager_Image::Release_Instance();

	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

/*
	윈도우들 초기화
*/
void API_Window_Main::Initialize()
{
	Manager_Data::Get_Instance()->Load_All_Datas();
	API_Window_Frame::Get_Instance()->Initialize(GetModuleHandle(NULL));
}

/*
	메시지 받고 윈도우들에게 실행시키기
*/
int API_Window_Main::Run()
{
	MSG msg;

	// 메시지가 있는 동안은 반복
	while (GetMessage(&msg, NULL, 0, 0))
	{
		API_Window_Frame::Get_Instance()->Run(msg);
	}

	return (int)msg.wParam;
}