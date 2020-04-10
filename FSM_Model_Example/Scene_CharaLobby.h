#pragma once
#include "Scene.h"
#include "API_Window_Main.h"
#include "Scene_Lobby.h"
#include "Scene_Equipment.h"
#include "Scene_Shop.h"

/*
	캐릭터 로비 씬
	캐릭터 로그인 후 로비 화면을 담고 있다
	전투, 장비, 상점, 캐릭터 선택 화면으로
*/
class Scene_CharaLobby : public Scene
{
private:
	HWND m_Battle_Button, m_Shop_Button, m_Equip_Button, m_Prev_Button;
	Data_Character* m_Character;

public:
	Scene_CharaLobby(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_CharaLobby();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen(); // 스크린 그리기
	void Draw_Title(HDC _hdc);
	void Draw_Chara(HDC _hdc);
	void Draw_Equipment(HDC _hdc);
	void Draw_Status(HDC _hdc);

	void Battle();
	void Shop();
	void Equip();
	void Prev();
};

