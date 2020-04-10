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

	// �������� �Ĵ� ���ǵ�
	m_Buy_List = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY, buy_pos.x, buy_pos.y, rect.right / 2 - 20, 150, m_Hwnd, (HMENU)S_S_BUY_LIST, API_Window_Main::Get_Instance()->hInst, NULL);

	// ������ ���� ���ǵ�
	m_Sell_List = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		LBS_NOTIFY, sell_pos.x, sell_pos.y, rect.right / 2 - 20, 150, m_Hwnd, (HMENU)S_S_SELL_LIST, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���� ī�װ�
	m_Weapon_Button = CreateWindow("button", "����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		weapon_pos.x, weapon_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_S_WEAPON_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// �� ī�װ�
	m_Armor_Button = CreateWindow("button", "��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		armor_pos.x, armor_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_S_ARMOR_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ��ű� ī�װ�
	m_Accessory_Button = CreateWindow("button", "��ű�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		accessory_pos.x, accessory_pos.y, rect.right / 3 - 20, 35,
		m_Hwnd, (HMENU)S_S_ACCESSORY_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���� ��ư
	m_Buy_Button = CreateWindow("button", "���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		buy_pos.x, rect.bottom - 90, rect.right / 2 - 20, 35,
		m_Hwnd, (HMENU)S_S_BUY_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// �Ǹ� ��ư
	m_Sell_Button = CreateWindow("button", "�Ǵ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		sell_pos.x, rect.bottom - 90, rect.right / 2 - 20, 35,
		m_Hwnd, (HMENU)S_S_SELL_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ĳ���� ����â���� ��ư
	m_Prev_Button = CreateWindow("button", "ĳ���� ���� â����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		chara_select_pos.x, chara_select_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_S_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���â���� ��ư
	m_Equip_Button = CreateWindow("button", "��� â����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		equip_pos.x, equip_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_S_EQUIP_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Shop::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		// Ŀ�ǵ�
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_S_BUY_LIST:					// �� ���� ����Ʈ
			switch (HIWORD(wparam))
			{
			case LBN_SELCHANGE:			// ������ �ٲ�
				m_Buy_Index = (int)SendMessage(m_Buy_List, LB_GETCURSEL, 0, 0);
				break;
			}
			break;
		case S_S_SELL_LIST:					// �� ���� ����Ʈ
			switch (HIWORD(wparam))
			{
			case LBN_SELCHANGE:			// ������ �ٲ�
				m_Sell_Index = (int)SendMessage(m_Sell_List, LB_GETCURSEL, 0, 0);
				break;
			}
			break;

			// ī�װ� ����
		case S_S_WEAPON_BUTTON:
			Change_Category(0);
			break;
		case S_S_ARMOR_BUTTON:
			Change_Category(1);
			break;
		case S_S_ACCESSORY_BUTTON:
			Change_Category(2);
			break;

			// ���� ��� �ȱ�
		case S_S_BUY_BUTTON:
			Buy_Item();
			break;
		case S_S_SELL_BUTTON:
			Sell_Item();
			break;

		case S_S_PREV_BUTTON:				// ĳ���� ����â����
			Prev();
			break;
		case S_S_EQUIP_BUTTON:				// ���â����
			Equip();
			break;
		}

		InvalidateRect(m_Hwnd, NULL, FALSE);
		return 0;

		// �׸���
	case WM_PAINT:
		// ������ ����
		Draw_Screen();
		// ������ ����
		break;
	}
	return false;
}

void Scene_Shop::Draw_Screen()
{
	HDC hdc;

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// Ÿ��Ʋ �׸���
	Draw_Title(hdc);
	// ���� �׸���
	Draw_Help(hdc);
	// ���� �׸���2, ī�װ� �������� ������
	if(m_Current_Category != -1)
		Draw_Item_Desc(hdc);

	m_Backbit->DeleteBitmapDC(hdc);
}

void Scene_Shop::Draw_Title(HDC _hdc)
{
	RECT rect;
	TCHAR text[] = "����";
	HFONT myFont, oldFont;

	// ��Ʈ ����
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	rect.top = TITLE_TOP;
	rect.bottom = rect.top + 100;
	DrawText(_hdc, text, strlen(text), &rect, DT_CENTER);

	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Shop::Draw_Help(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR buy[] = "����";
	TCHAR sell[] = "�Ǹ�";
	TCHAR currency[STRING_SIZE];
	HFONT myFont, oldFont;

	// ��Ʈ ����
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
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

	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);

	// ��Ʈ ����
	myFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = TITLE_TOP + 70;
	text_rect.left = rect.right / 2 - 50;
	text_rect.right = rect.right / 2 + 50;
	text_rect.bottom = text_rect.top + 50;
	wsprintf(currency, "������\n%d��", m_Character->Get_Currency());
	DrawText(_hdc, currency, strlen(currency), &text_rect, DT_CENTER);

	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Shop::Draw_Item_Desc(HDC _hdc)
{
	RECT rect, text_rect;
	TCHAR buy[STRING_SIZE * 3];
	TCHAR sell[STRING_SIZE * 3];
	HFONT myFont, oldFont;

	// ��Ʈ ����
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	text_rect = rect;
	text_rect.top = rect.bottom - 220;
	text_rect.left = 10;
	text_rect.right = rect.right / 2 - 10;
	text_rect.bottom = text_rect.top + 110;
	Rectangle(_hdc, text_rect.left, text_rect.top, text_rect.right, text_rect.bottom);
	if (m_Buy_Index != -1) // ���� �ϳ� ������ ���
	{
		ListNode<Data_Item*>* node = buy_list->Get_Head();
		for (int i = 0; i <= m_Buy_Index; i++)
			node = node->m_Next;
		wsprintf(buy, "\n%s\n%s\n%d��", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		DrawText(_hdc, buy, strlen(buy), &text_rect, DT_CENTER);
	}

	text_rect.left += rect.right / 2;
	text_rect.right += rect.right / 2;
	Rectangle(_hdc, text_rect.left, text_rect.top, text_rect.right, text_rect.bottom);
	if (m_Sell_Index != -1) // ���� �ϳ� ������ ���
	{
		ListNode<Data_Item*>* node = sell_list->Get_Head();
		for (int i = 0; i <= m_Sell_Index; i++)
			node = node->m_Next;
		wsprintf(sell, "\n%s\n%s\n%d��", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		DrawText(_hdc, sell, strlen(sell), &text_rect, DT_CENTER);
	}

	// ��Ʈ ����
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
	if (m_Buy_Index != -1) // ���� �ϳ� ������ ���
	{
		ListNode<Data_Item*>* node = buy_list->Get_Head();
		for (int i = 0; i <= m_Buy_Index; i++)
			node = node->m_Next;
		// ���� ���� ����
		char text[STRING_SIZE * 3];
		wsprintf(text, "%s\n%s\n%d��\n�� �������� ������ ����?", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		if (MessageBox(m_Hwnd, text, "����", MB_OKCANCEL) == IDOK)
		{
			if (m_Character->Sub_Currency(node->m_Data->Get_Price()))
			{
				// ���� ����
				MessageBox(m_Hwnd, "�������� ���������� �����߾��.", "���� ����", MB_OK);

				// �������� üũ
				Data_Item_Weapon* weapon = dynamic_cast<Data_Item_Weapon*>(node->m_Data);
				if (weapon != nullptr)
					m_Character->Add_Weapon(new Data_Item_Weapon(*weapon));

				// ������ üũ
				Data_Item_Armor* armor = dynamic_cast<Data_Item_Armor*>(node->m_Data);
				if (armor != nullptr)
					m_Character->Add_Armor(new Data_Item_Armor(*armor));

				// ��ű����� üũ
				Data_Item_Accessory* accessory = dynamic_cast<Data_Item_Accessory*>(node->m_Data);
				if (accessory != nullptr)
					m_Character->Add_Accessory(new Data_Item_Accessory(*accessory));
			}
			else
			{
				// ���� ����
				MessageBox(m_Hwnd, "���� �����.", "���� ����", MB_OK);
			}
		}
	}
	else
	{
		MessageBox(m_Hwnd, "�ƹ��͵� �������� �ʾҾ��.", "���� ����", MB_OK);
	}
	Refresh_List();
}

void Scene_Shop::Sell_Item()
{
	if (m_Sell_Index != -1) // ���� �ϳ� ������ ���
	{
		ListNode<Data_Item*>* node = sell_list->Get_Head();
		for (int i = 0; i <= m_Sell_Index; i++)
			node = node->m_Next;

		// �Ǹ� ���� ����
		char text[STRING_SIZE * 3];
		wsprintf(text, "%s\n%s\n%d��\n�� �������� ������ �ȱ��?", node->m_Data->Get_Name(), node->m_Data->Get_Desc(), node->m_Data->Get_Price());
		if (MessageBox(m_Hwnd, text, "�Ǹ�", MB_OKCANCEL) == IDOK)
		{
			// �Ǹ� ����
			MessageBox(m_Hwnd, "�������� ���������� �Ǹ��߾��.", "�Ǹ� ����", MB_OK);
			m_Character->Add_Currency(node->m_Data->Get_Price());
			m_Character->Remove_Item(node->m_Data);
		}
	}
	else
	{
		MessageBox(m_Hwnd, "�ƹ��͵� �������� �ʾҾ��.", "�Ǹ� ����", MB_OK);
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

	// ����Ʈ ���� ����
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
	case 0: // ����
		for (int i = 0; i < ItemTable::Weapon_Size; i++)
			buy_list->Insert(new Data_Item_Weapon(ItemTable::Weapons[i]));
		for (int i = 0; i < m_Character->Get_WeaponInv_Size(); i++)
			sell_list->Insert(m_Character->Get_Weapon_In_Inv(i));
		break;
	case 1: // ��
		for (int i = 0; i < ItemTable::Armor_Size; i++)
			buy_list->Insert(new Data_Item_Armor(ItemTable::Armors[i]));
		for (int i = 0; i < m_Character->Get_ArmorInv_Size(); i++)
			sell_list->Insert(m_Character->Get_Armor_In_Inv(i));
		break;
	case 2: // ��ű�
		for (int i = 0; i < ItemTable::Accessories_Size; i++)
			buy_list->Insert(new Data_Item_Accessory(ItemTable::Accessories[i]));
		for (int i = 0; i < m_Character->Get_AccessoryInv_Size(); i++)
			sell_list->Insert(m_Character->Get_Accessory_In_Inv(i));
		break;
	}
	if (sell_list == nullptr) return;

	// ����Ʈ�� �׸� �߰�
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
