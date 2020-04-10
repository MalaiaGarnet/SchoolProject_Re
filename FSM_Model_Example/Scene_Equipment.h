#pragma once
#include "Scene.h"
#include "Scene_CharaLobby.h"
#include "Scene_Shop.h"
#include "API_Window_Main.h"

class Scene_Equipment : public Scene
{
private:
	HWND m_Prev_Button, m_Shop_Button, m_Weapon_Button, m_Armor_Button, m_Accessory_Button, m_Equip_Button;
	HWND m_Item_List;
	Data_Character* m_Character;
	int m_Item_Index;
	int m_Current_Category;
	LinkedList<Data_Item*>* item_list;
public:
	Scene_Equipment(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_Equipment();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen(); // 스크린 그리기
	void Draw_Title(HDC _hdc);
	void Draw_Equip(HDC _hdc);
	void Draw_Status(HDC _hdc);
	void Draw_Item_Desc(HDC _hdc);

	void Change_Category(int _index);

	void Equip();
	void Prev();
	void Shop();

	void Refresh_List();
};

