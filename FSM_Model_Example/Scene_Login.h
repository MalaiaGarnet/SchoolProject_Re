#pragma once
#include "Scene.h"

/*
	로그인 씬
	로그인 화면을 담당하고 있다
*/


class Scene_Login : public Scene
{
private:
	HWND m_Id_edit, m_Pass_edit;
	HWND m_Login_button, m_Register_button;

public:
	Scene_Login(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_Login();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);
	
	void Draw_Screen();

	void Process_Login();
	void Process_Register();
};

