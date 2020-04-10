#include "Scene_Equipment.h"



Scene_Equipment::Scene_Equipment(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
	m_Prev_Button = NULL;
	m_Shop_Button = NULL;
	m_Weapon_Button = NULL; 
	m_Armor_Button = NULL; 
	m_Accessory_Button = NULL;
	m_Equip_Button = NULL;
	m_Item_List = NULL;
	m_Character = nullptr;
	m_Item_Index = -1;
	m_Current_Category = -1;
	item_list = new LinkedList<Data_Item*>();
}


Scene_Equipment::~Scene_Equipment()
{
	DestroyWindow(m_Prev_Button);
	DestroyWindow(m_Shop_Button);
	DestroyWindow(m_Weapon_Button);
	DestroyWindow(m_Armor_Button);
	DestroyWindow(m_Accessory_Button);
	DestroyWindow(m_Equip_Button);

	DestroyWindow(m_Item_List);

	if (item_list != nullptr)
		delete item_list;
}

void Scene_Equipment::Initialize()
{
	m_Character = Manager_Data::Get_Instance()->Get_Current_User()->Get_Current_Character();

	RECT rect;
	GetClientRect(m_Hwnd, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;

	POINT list_pos = { rect.right / 2 + 10, 150 };
	POINT weapon_pos = { 10, rect.top + 105 };
	POINT armor_pos = { weapon_pos.x + rect.right / 3, weapon_pos.y };
	POINT accessory_pos = { armor_pos.x + rect.right / 3, weapon_pos.y };

	POINT equip_pos = { rect.right - 140, rect.bottom - 90 };
	POINT chara_select_pos = { 10, rect.bottom - 45 };
	POINT shop_pos = { rect.right - 160, chara_select_pos.y };

	cout << "Scene_Equipment Initialized" << endl;
	m_Backbit->ClearBitMap();

	// 유저가 가진 물건들
	m_Item_List = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY, list_pos.x, list_pos.y, rect.right / 2 - 20, 200, m_Hwnd, (HMENU)S_CE_ITEM_LIST, API_Window_Main::Get_Instance()->hInst, NULL);

	// 무기 카테고리
	m_Weapon_Button = CreateWindow("button", "무기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		weapon_pos.x, weapon_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_CE_WEAPON_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 방어구 카테고리
	m_Armor_Button = CreateWindow("button", "방어구", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		armor_pos.x, armor_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_CE_ARMOR_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 장신구 카테고리
	m_Accessory_Button = CreateWindow("button", "장신구", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		accessory_pos.x, accessory_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_CE_ACCESSORY_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 장착 버튼
	m_Equip_Button = CreateWindow("button", "장착", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		equip_pos.x, equip_pos.y, 130, 35,
		m_Hwnd, (HMENU)S_CE_EQUIP_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 캐릭터 선택창으로 버튼
	m_Prev_Button = CreateWindow("button", "캐릭터 선택 창으로", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		chara_select_pos.x, chara_select_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CE_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 상점창으로 버튼
	m_Shop_Button = CreateWindow("button", "상점으로", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		shop_pos.x, shop_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CE_SHOP_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Equipment::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		// 커맨드
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_CE_ITEM_LIST:					// 쟤 물건 리스트
			switch (HIWORD(wparam))
			{
			case LBN_SELCHANGE:			// 선택이 바뀜
				m_Item_Index = (int)SendMessage(m_Item_List, LB_GETCURSEL, 0, 0);
				break;
			}
			break;

		// 카테고리 변경
		case S_CE_WEAPON_BUTTON:
			Change_Category(0);
			break;
		case S_CE_ARMOR_BUTTON:
			Change_Category(1);
			break;
		case S_CE_ACCESSORY_BUTTON:
			Change_Category(2);
			break;

		case S_CE_EQUIP_BUTTON:				// 장비 교체
			Equip();
			break;
		case S_CE_PREV_BUTTON:				// 캐릭터 선택창으로
			Prev();
			break;
		case S_CE_SHOP_BUTTON:				// 상점 창으로
			Shop();
			break;
		}

		InvalidateRect(m_Hwnd, NULL, FALSE);
		return 0;

		// 그리기
	case WM_PAINT:
		// 페인팅 시작
		Draw_Screen();
		// 페인팅 종료
		break;
	}
	return false;
}

void Scene_Equipment::Draw_Screen()
{
	HDC hdc;

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// 타이틀 그리기
	Draw_Title(hdc);
	Draw_Equip(hdc);
	Draw_Status(hdc);
	// 설명
	if (m_Current_Category != -1)
		Draw_Item_Desc(hdc);

	m_Backbit->DeleteBitmapDC(hdc);
}

void Scene_Equipment::Draw_Title(HDC _hdc)
{
	RECT rect;
	TCHAR text[] = "장비";
	HFONT myFont, oldFont;

	// 폰트 설정
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	rect.top = TITLE_TOP;
	rect.bottom = rect.top + 100;
	DrawText(_hdc, text, strlen(text), &rect, DT_CENTER);

	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Equipment::Draw_Equip(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR desc[STRING_SIZE * 4];
	TCHAR desc_2[STRING_SIZE * 16];
	HFONT myFont, oldFont;

	// 폰트 설정
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "돋움");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = 150;
	text_rect.left = 10;
	text_rect.right = rect.right / 2 - 10;
	text_rect.bottom = text_rect.top + 200;
	Rectangle(_hdc, text_rect.left, text_rect.top, text_rect.right, text_rect.bottom);

	text_rect.top += 10;
	text_rect.left += 10;
	text_rect.right -= 10;
	text_rect.bottom -= 10;
	wsprintf(desc, "무기\n\n\n방어구\n\n\n장신구");
	wsprintf(desc_2, "\n%s\n%s\n\n%s\n%s\n\n%s\n%s", m_Character->Get_Weapon()->Get_Name(), m_Character->Get_Weapon()->Get_Desc(),
		m_Character->Get_Armor()->Get_Name(), m_Character->Get_Armor()->Get_Desc(),
		m_Character->Get_Accessory()->Get_Name(), m_Character->Get_Accessory()->Get_Desc());
	DrawText(_hdc, desc, strlen(desc), &text_rect, DT_LEFT);
	DrawText(_hdc, desc_2, strlen(desc_2), &text_rect, DT_RIGHT);
	
	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Equipment::Draw_Status(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR desc[STRING_SIZE * 3];
	TCHAR desc_2[STRING_SIZE * 3];
	HFONT myFont, oldFont;

	// 폰트 설정
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "돋움");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = rect.bottom - 220;
	text_rect.left = 10;
	text_rect.right = rect.right / 2 - 10;
	text_rect.bottom = text_rect.top + 110;
	Rectangle(_hdc, text_rect.left, text_rect.top, text_rect.right, text_rect.bottom);

	text_rect.top += 10;
	text_rect.left += 10;
	text_rect.right -= 10;
	text_rect.bottom -= 10;
	wsprintf(desc, "HP:\nATK:\nDEF:\nDEX:\nAGI:");
	wsprintf(desc_2, "%d\n%d\n%d\n%d\n%d", m_Character->Get_HP(), m_Character->Get_ATK(),
		m_Character->Get_DEF(), m_Character->Get_DEX(), m_Character->Get_AGI());
	DrawText(_hdc, desc, strlen(desc), &text_rect, DT_LEFT);
	DrawText(_hdc, desc_2, strlen(desc_2), &text_rect, DT_RIGHT);

	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Equipment::Draw_Item_Desc(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR desc[STRING_SIZE * 3];
	HFONT myFont, oldFont;

	// 폰트 설정
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "돋움");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = rect.bottom - 220;
	text_rect.left = rect.right / 2 + 10;
	text_rect.right = rect.right - 10;
	text_rect.bottom = text_rect.top + 110;
	Rectangle(_hdc, text_rect.left, text_rect.top, text_rect.right, text_rect.bottom);
	if (m_Item_Index != -1) // 뭐라도 하나 선택한 경우
	{
		text_rect.top += 10;
		text_rect.left += 10;
		text_rect.right -= 10;
		text_rect.bottom -= 10;
		ListNode<Data_Item*>* node = item_list->Get_Head();
		for (int i = 0; i <= m_Item_Index; i++)
			node = node->m_Next;
		wsprintf(desc, "\n%s\n%s\n%d원", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		DrawText(_hdc, desc, strlen(desc), &text_rect, DT_CENTER);
	}

	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Equipment::Change_Category(int _index)
{
	m_Current_Category = _index;
	Refresh_List();
}

void Scene_Equipment::Equip()
{
	if (m_Current_Category == -1 || m_Item_Index == -1)
	{
		MessageBox(m_Hwnd, "선택된 아이템이 없어요.", "장착 실패", MB_OK);
		return;
	}
	ListNode<Data_Item*>* node = item_list->Get_Head();
	for (int i = 0; i <= m_Item_Index; i++)
		node = node->m_Next;
	m_Character->Remove_Item(node->m_Data);
	m_Character->Change_Equipment(node->m_Data);
	Refresh_List();
}

void Scene_Equipment::Prev()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_CharaLobby(m_Hwnd, m_Backbit));
}

void Scene_Equipment::Shop()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Shop(m_Hwnd, m_Backbit));
}

void Scene_Equipment::Refresh_List()
{
	m_Item_Index = -1;

	// 리스트 상자 비우기
	SendMessage(m_Item_List, LB_RESETCONTENT, 0, 0);

	if (item_list != nullptr)
		delete item_list;

	item_list = new LinkedList<Data_Item*>();

	switch (m_Current_Category)
	{
	case 0: // 무기
		for (int i = 0; i < m_Character->Get_WeaponInv_Size(); i++)
			item_list->Insert(m_Character->Get_Weapon_In_Inv(i));
		break;
	case 1: // 방어구
		for (int i = 0; i < m_Character->Get_ArmorInv_Size(); i++)
			item_list->Insert(m_Character->Get_Armor_In_Inv(i));
		break;
	case 2: // 장신구
		for (int i = 0; i < m_Character->Get_AccessoryInv_Size(); i++)
			item_list->Insert(m_Character->Get_Accessory_In_Inv(i));
		break;
	}
	if (item_list == nullptr) return;

	// 리스트에 항목 추가
	ListNode<Data_Item*> * node = item_list->Get_Head();
	node = item_list->Get_Head();
	for (int i = 0; i < item_list->Size(); i++)
	{
		node = node->m_Next;
		SendMessage(m_Item_List, LB_ADDSTRING, 0, (LPARAM)node->m_Data->Get_Name());
	}
}
