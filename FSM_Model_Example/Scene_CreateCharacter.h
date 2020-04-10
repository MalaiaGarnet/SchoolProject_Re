#pragma once
#include "Scene.h"
#include "Scene_Lobby.h"
#include "Bitmap_Character.h"
#include "API_Window_Main.h"

#include "Factory_JSKMaker_Comsoon.h"
#include "Factory_JSKMaker_Moonsoon.h"
#include "Factory_JSKMaker_Gongsoon.h"

/*
	캐릭터 생성 씬
	캐릭터를 생성하는 과정을 담고 있다
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

	void Draw_Screen(); // 스크린 그리기

	void Cancel(); // 뒤로 돌아가기
	void Create_Character(); // 캐릭터 만들기
	void Next();
	void Prev();
};

