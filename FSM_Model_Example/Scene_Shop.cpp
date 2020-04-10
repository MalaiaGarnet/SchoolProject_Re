#include "Scene_Shop.h"



Scene_Shop::Scene_Shop(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
	m_Prev_Button = NULL;
	m_Weapon_Button = NULL;
	m_Armor_Button = NULL;
	m_Accessory_Button = NULL;
	m_Buy_Button = NULL;
	m_Sell_Button = NULL;
	m_Equip_Button = NULL;

	m_Sell_List = NULL;
	m_Buy_List = NULL;

	m_Character = nullptr;
	m_Sell_Index = -1;
	m_Buy_Index = -1;
	m_Current_Category = -1;

	buy_list = new LinkedList<Data_Item*>();
	sell_list = new LinkedList<Data_Item*>();
}


Scene_Shop::~Scene_Shop()
{
	DestroyWindow(m_Prev_Button);
	DestroyWindow(m_Weapon_Button);
	DestroyWindow(m_Armor_Button);
	DestroyWindow(m_Accessory_Button);
	DestroyWindow(m_Buy_Button);
	DestroyWindow(m_Sell_Button);
	DestroyWindow(m_Equip_Button);

	DestroyWindow(m_Sell_List);
	DestroyWindow(m_Buy_List);

	if (buy_list != nullptr)
		delete buy_list;
	if (sell_list != nullptr)
		delete sell_list;

}

void Scene_Shop::Initialize()
{
	m_Character = Manager_Data::Get_Instance()->Get_Current_User()->Get_Current_Character();

	RECT rect;
	GetClientRect(m_Hwnd, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;

	POINT buy_pos = { 10, 150 };
	POINT sell_pos = { rect.right / 2 + 10, buy_pos.y };
	POINT weapon_pos = { 10, rect.bottom - 275 };
	POINT armor_pos = { weapon_pos.x + rect.right / 3, weapon_pos.y };
	POINT accessory_pos = { armor_pos.x + rect.right / 3, weapon_pos.y };

	POINT chara_select_pos = { buy_pos.x, rect.bottom - 45 };
	POINT equip_pos = { rect.right - 160, chara_select_pos.y };

	cout << "Scene_Shop Initialized" << endl;
	m_Backbit->ClearBitMap();

	// 상점에서 파는 물건들
	m_Buy_List = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY, buy_pos.x, buy_pos.y, rect.right / 2 - 20, 150, m_Hwnd, (HMENU)S_S_BUY_LIST, API_Window_Main::Get_Instance()->hInst, NULL);

	// 유저가 가진 물건들
	m_Sell_List = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY, sell_pos.x, sell_pos.y, rect.right / 2 - 20, 150, m_Hwnd, (HMENU)S_S_SELL_LIST, API_Window_Main::Get_Instance()->hInst, NULL);

	// 무기 카테고리
	m_Weapon_Button = CreateWindow("button", "무기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		weapon_pos.x, weapon_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_S_WEAPON_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 방어구 카테고리
	m_Armor_Button = CreateWindow("button", "방어구", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		armor_pos.x, armor_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_S_ARMOR_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 장신구 카테고리
	m_Accessory_Button = CreateWindow("button", "장신구", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		accessory_pos.x, accessory_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_S_ACCESSORY_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 구매 버튼
	m_Buy_Button = CreateWindow("button", "산다", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		buy_pos.x, rect.bottom - 90, rect.right / 2 - 20, 35,
		m_Hwnd, (HMENU)S_S_BUY_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 판매 버튼
	m_Sell_Button = CreateWindow("button", "판다", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		sell_pos.x, rect.bottom - 90, rect.right / 2 - 20, 35,
		m_Hwnd, (HMENU)S_S_SELL_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 캐릭터 선택창으로 버튼
	m_Prev_Button = CreateWindow("button", "캐릭터 선택 창으로", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		chara_select_pos.x, chara_select_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_S_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 장비창으로 버튼
	m_Equip_Button = CreateWindow("button", "장비 창으로", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		equip_pos.x, equip_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_S_EQUIP_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Shop::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		// 커맨드
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_S_BUY_LIST:					// 쟤 물건 리스트
			switch (HIWORD(wparam))
			{
			case LBN_SELCHANGE:			// 선택이 바뀜
				m_Buy_Index = (int)SendMessage(m_Buy_List, LB_GETCURSEL, 0, 0);
				break;
			}
			break;
		case S_S_SELL_LIST:					// 내 물건 리스트
			switch (HIWORD(wparam))
			{
			case LBN_SELCHANGE:			// 선택이 바뀜
				m_Sell_Index = (int)SendMessage(m_Sell_List, LB_GETCURSEL, 0, 0);
				break;
			}
			break;

			// 카테고리 변경
		case S_S_WEAPON_BUTTON:
			Change_Category(0);
			break;
		case S_S_ARMOR_BUTTON:
			Change_Category(1);
			break;
		case S_S_ACCESSORY_BUTTON:
			Change_Category(2);
			break;

			// 물건 사고 팔기
		case S_S_BUY_BUTTON:
			Buy_Item();
			break;
		case S_S_SELL_BUTTON:
			Sell_Item();
			break;

		case S_S_PREV_BUTTON:				// 캐릭터 선택창으로
			Prev();
			break;
		case S_S_EQUIP_BUTTON:				// 장비창으로
			Equip();
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

void Scene_Shop::Draw_Screen()
{
	HDC hdc;

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// 타이틀 그리기
	Draw_Title(hdc);
	// 도움말 그리기
	Draw_Help(hdc);
	// 도움말 그리기2, 카테고리 선택했을 때부터
	if(m_Current_Category != -1)
		Draw_Item_Desc(hdc);

	m_Backbit->DeleteBitmapDC(hdc);
}

void Scene_Shop::Draw_Title(HDC _hdc)
{
	RECT rect;
	TCHAR text[] = "상점";
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

void Scene_Shop::Draw_Help(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR buy[] = "구매";
	TCHAR sell[] = "판매";
	TCHAR currency[STRING_SIZE];
	HFONT myFont, oldFont;

	// 폰트 설정
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = TITLE_TOP + 80;
	text_rect.left = 10;
	text_rect.right = rect.right / 2;
	text_rect.bottom = text_rect.top + 40;
	DrawText(_hdc, buy, strlen(buy), &text_rect, DT_CENTER);

	text_rect.left += rect.right / 2;
	text_rect.right += rect.right / 2;
	DrawText(_hdc, sell, strlen(sell), &text_rect, DT_CENTER);

	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);

	// 폰트 설정
	myFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "돋움");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = TITLE_TOP + 70;
	text_rect.left = rect.right / 2 - 50;
	text_rect.right = rect.right / 2 + 50;
	text_rect.bottom = text_rect.top + 50;
	wsprintf(currency, "소지금\n%d원", m_Character->Get_Currency());
	DrawText(_hdc, currency, strlen(currency), &text_rect, DT_CENTER);

	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Shop::Draw_Item_Desc(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR buy[STRING_SIZE * 3];
	TCHAR sell[STRING_SIZE * 3];
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
	if (m_Buy_Index != -1) // 뭐라도 하나 선택한 경우
	{
		ListNode<Data_Item*>* node = buy_list->Get_Head();
		for (int i = 0; i <= m_Buy_Index; i++)
			node = node->m_Next;
		wsprintf(buy, "\n%s\n%s\n%d원", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		DrawText(_hdc, buy, strlen(buy), &text_rect, DT_CENTER);
	}

	text_rect.left += rect.right / 2;
	text_rect.right += rect.right / 2;
	Rectangle(_hdc, text_rect.left, text_rect.top, text_rect.right, text_rect.bottom);
	if (m_Sell_Index != -1) // 뭐라도 하나 선택한 경우
	{
		ListNode<Data_Item*>* node = sell_list->Get_Head();
		for (int i = 0; i <= m_Sell_Index; i++)
			node = node->m_Next;
		wsprintf(sell, "\n%s\n%s\n%d원", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		DrawText(_hdc, sell, strlen(sell), &text_rect, DT_CENTER);
	}

	// 폰트 해제
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}


void Scene_Shop::Change_Category(int _index)
{
	m_Current_Category = _index;
	Refresh_List();
}

void Scene_Shop::Buy_Item()
{
	if (m_Buy_Index != -1) // 뭐라도 하나 선택한 경우
	{
		ListNode<Data_Item*>* node = buy_list->Get_Head();
		for (int i = 0; i <= m_Buy_Index; i++)
			node = node->m_Next;
		// 구매 동의 묻기
		char text[STRING_SIZE * 3];
		wsprintf(text, "%s\n%s\n%d원\n이 아이템을 정말로 살까요?", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		if (MessageBox(m_Hwnd, text, "구매", MB_OKCANCEL) == IDOK)
		{
			if (m_Character->Sub_Currency(node->m_Data->Get_Price()))
			{
				// 구매 성공
				MessageBox(m_Hwnd, "아이템을 성공적으로 구매했어요.", "구매 성공", MB_OK);

				// 무기인지 체크
				Data_Item_Weapon* weapon = dynamic_cast<Data_Item_Weapon*>(node->m_Data);
				if (weapon != nullptr)
					m_Character->Add_Weapon(new Data_Item_Weapon(*weapon));

				// 방어구인지 체크
				Data_Item_Armor* armor = dynamic_cast<Data_Item_Armor*>(node->m_Data);
				if (armor != nullptr)
					m_Character->Add_Armor(new Data_Item_Armor(*armor));

				// 장신구인지 체크
				Data_Item_Accessory* accessory = dynamic_cast<Data_Item_Accessory*>(node->m_Data);
				if (accessory != nullptr)
					m_Character->Add_Accessory(new Data_Item_Accessory(*accessory));
			}
			else
			{
				// 구매 실패
				MessageBox(m_Hwnd, "돈이 없어요.", "구매 오류", MB_OK);
			}
		}
	}
	else
	{
		MessageBox(m_Hwnd, "아무것도 선택하지 않았어요.", "구매 오류", MB_OK);
	}
	Refresh_List();
}

void Scene_Shop::Sell_Item()
{
	if (m_Sell_Index != -1) // 뭐라도 하나 선택한 경우
	{
		ListNode<Data_Item*>* node = sell_list->Get_Head();
		for (int i = 0; i <= m_Sell_Index; i++)
			node = node->m_Next;

		// 판매 동의 묻기
		char text[STRING_SIZE * 3];
		wsprintf(text, "%s\n%s\n%d원\n이 아이템을 정말로 팔까요?", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		if (MessageBox(m_Hwnd, text, "판매", MB_OKCANCEL) == IDOK)
		{
			// 판매 성공
			MessageBox(m_Hwnd, "아이템을 성공적으로 판매했어요.", "판매 성공", MB_OK);
			m_Character->Add_Currency(node->m_Data->Get_Price());
			m_Character->Remove_Item(node->m_Data);
		}
	}
	else
	{
		MessageBox(m_Hwnd, "아무것도 선택하지 않았어요.", "판매 오류", MB_OK);
	}
	Refresh_List();
}

void Scene_Shop::Prev()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_CharaLobby(m_Hwnd, m_Backbit));
}

void Scene_Shop::Equip()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Equipment(m_Hwnd, m_Backbit));
}

void Scene_Shop::Refresh_List()
{
	m_Buy_Index = -1;
	m_Sell_Index = -1;

	// 리스트 상자 비우기
	SendMessage(m_Buy_List, LB_RESETCONTENT, 0, 0);
	SendMessage(m_Sell_List, LB_RESETCONTENT, 0, 0);

	if (buy_list != nullptr)
		delete buy_list;
	if (sell_list != nullptr)
		delete sell_list;

	buy_list = new LinkedList<Data_Item*>();
	sell_list = new LinkedList<Data_Item*>();

	switch (m_Current_Category)
	{
	case 0: // 무기
		for (int i = 0; i < ItemTable::Weapon_Size; i++)
			buy_list->Insert(new Data_Item_Weapon(ItemTable::Weapons[i]));
		for (int i = 0; i < m_Character->Get_WeaponInv_Size(); i++)
			sell_list->Insert(m_Character->Get_Weapon_In_Inv(i));
		break;
	case 1: // 방어구
		for (int i = 0; i < ItemTable::Armor_Size; i++)
			buy_list->Insert(new Data_Item_Armor(ItemTable::Armors[i]));
		for (int i = 0; i < m_Character->Get_ArmorInv_Size(); i++)
			sell_list->Insert(m_Character->Get_Armor_In_Inv(i));
		break;
	case 2: // 장신구
		for (int i = 0; i < ItemTable::Accessories_Size; i++)
			buy_list->Insert(new Data_Item_Accessory(ItemTable::Accessories[i]));
		for (int i = 0; i < m_Character->Get_AccessoryInv_Size(); i++)
			sell_list->Insert(m_Character->Get_Accessory_In_Inv(i));
		break;
	}
	if (sell_list == nullptr) return;

	// 리스트에 항목 추가
	ListNode<Data_Item*> * node = buy_list->Get_Head();
	for (int i = 0; i < buy_list->Size(); i++)
	{
		node = node->m_Next;
		SendMessage(m_Buy_List, LB_ADDSTRING, 0, (LPARAM)node->m_Data->Get_Name());
	}
	node = sell_list->Get_Head();
	for (int i = 0; i < sell_list->Size(); i++)
	{
		node = node->m_Next;
		SendMessage(m_Sell_List, LB_ADDSTRING, 0, (LPARAM)node->m_Data->Get_Name());
	}
}
