#pragma once
#include "Scene.h"
#include "Scene_Login.h"
#include "Scene_CreateCharacter.h"
#include "Scene_CharaLobby.h"
#include "Data_User.h"
#include "Data_Character.h"
#include "Bitmap_Character.h"

/*
	로비 씬
	로그인 후 메인 화면을 담고 있다
*/
class Scene_Lobby : public Scene
{
private:
	HWND m_Create_Chara_Button, m_Logout_Button, m_Unregister_Button;
	HWND m_Next_Button, m_Prev_Button, m_Play_Button, m_Remove_Chara_Button;
	int m_Current_Cursor;
	Data_User* user;

public:
	Scene_Lobby(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_Lobby();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen(); // 스크린 그리기
	void Draw_Slot(Data_Character* _chara, HDC _hdc, RECT _rect, POINT _offset); // 슬롯 그리기
	void Update_Buttons(); // 버튼 숨김여부 갱신

	void Logout();
	void Unregister();
	void Play();

	void Create_Character();
	void Remove_Character();
	void Next();
	void Prev();
};

