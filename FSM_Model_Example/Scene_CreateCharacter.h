#pragma once
#include "Scene.h"
#include "Scene_Lobby.h"
#include "Bitmap_Character.h"
#include "API_Window_Main.h"

#include "Factory_JSKMaker_Comsoon.h"
#include "Factory_JSKMaker_Moonsoon.h"
#include "Factory_JSKMaker_Gongsoon.h"

/*
	ĳ���� ���� ��
	ĳ���͸� �����ϴ� ������ ��� �ִ�
*/
class Scene_CreateCharacter : public Scene
{
private:
	HWND m_Name_Edit;
	HWND m_Create_Button, m_Cancel_Button, m_Next_Button, m_Prev_Button;
	int m_Current_Cursor;
	Data_User* user;

public:
	Scene_CreateCharacter(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_CreateCharacter();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen(); // ��ũ�� �׸���

	void Cancel(); // �ڷ� ���ư���
	void Create_Character(); // ĳ���� �����
	void Next();
	void Prev();
};

