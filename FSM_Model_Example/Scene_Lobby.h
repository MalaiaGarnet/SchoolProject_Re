#pragma once
#include "Scene.h"
#include "Scene_Login.h"
#include "Scene_CreateCharacter.h"
#include "Scene_CharaLobby.h"
#include "Data_User.h"
#include "Data_Character.h"
#include "Bitmap_Character.h"

/*
	�κ� ��
	�α��� �� ���� ȭ���� ��� �ִ�
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

	void Draw_Screen(); // ��ũ�� �׸���
	void Draw_Slot(Data_Character* _chara, HDC _hdc, RECT _rect, POINT _offset); // ���� �׸���
	void Update_Buttons(); // ��ư ���迩�� ����

	void Logout();
	void Unregister();
	void Play();

	void Create_Character();
	void Remove_Character();
	void Next();
	void Prev();
};

