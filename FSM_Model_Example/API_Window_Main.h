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
	���� Ŭ����
	������ ������ �ô´�
*/
class API_Window_Main
{
private:
	static API_Window_Main* instance;

	API_Window_Main() {}
	~API_Window_Main() {}
public:
	// ��� ����
	HINSTANCE hInst;
	// �̱��� �Լ�
	static API_Window_Main* Create_Instance();
	static API_Window_Main* Get_Instance();
	static void Release_Instance();

	void Initialize(); // ������ ����
	int Run(); // ������ ������
};

