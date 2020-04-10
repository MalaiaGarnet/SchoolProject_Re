#include "API_Window_Main.h"


// �̱���
API_Window_Main* API_Window_Main::instance = nullptr;

API_Window_Main* API_Window_Main::Create_Instance()
{
	if(instance == nullptr)
		instance = new API_Window_Main();

	// �ڽ��� ��������� ���ÿ� ������ ������, ��Ҹ� ����
	API_Window_Frame::Create_Instance();
	Att_Mouse::Create_Instance();

	// �Ŵ��� �����
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

	// �ڽ��� ���ŵǱ� �� �����ߴ� �������, ��Ҹ� ����
	API_Window_Frame::Release_Instance();
	Att_Mouse::Release_Instance();

	// �Ŵ��� ġ���
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
	������� �ʱ�ȭ
*/
void API_Window_Main::Initialize()
{
	Manager_Data::Get_Instance()->Load_All_Datas();
	API_Window_Frame::Get_Instance()->Initialize(GetModuleHandle(NULL));
}

/*
	�޽��� �ް� ������鿡�� �����Ű��
*/
int API_Window_Main::Run()
{
	MSG msg;

	// �޽����� �ִ� ������ �ݺ�
	while (GetMessage(&msg, NULL, 0, 0))
	{
		API_Window_Frame::Get_Instance()->Run(msg);
	}

	return (int)msg.wParam;
}