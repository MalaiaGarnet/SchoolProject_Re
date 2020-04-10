#pragma once
#include "Scene.h"
#include "Scene_CharaLobby.h"
#include "Scene_Equipment.h"
#include "API_Window_Main.h"

class Scene_Shop : public Scene
{
private:
	HWND m_Prev_Button, m_Weapon_Button, m_Armor_Button, m_Accessory_Button, m_Buy_Button, m_Sell_Button, m_Equip_Button;
	HWND m_Sell_List, m_Buy_List;
	Data_Character* m_Character;
	int m_Sell_Index, m_Buy_Index;
	int m_Current_Category;
	LinkedList<Data_Item*>* buy_list;
	LinkedList<Data_Item*>* sell_list;

public:
	Scene_Shop(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_Shop();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen(); // 스크린 그리기
	void Draw_Title(HDC _hdc);
	void Draw_Help(HDC _hdc);
	void Draw_Item_Desc(HDC _hdc);

	void Change_Category(int _index);
	void Buy_Item();
	void Sell_Item();
	void Prev();
	void Equip();

	void Refresh_List();
};

