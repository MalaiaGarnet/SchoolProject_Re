#include "Scene_CharaLobby.h"
#include "Bitmap_Character.h"


Scene_CharaLobby::Scene_CharaLobby(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
	m_Battle_Button = NULL;
	m_Shop_Button = NULL;
	m_Equip_Button = NULL;
	m_Prev_Button = NULL;
	m_Character = nullptr;
}


Scene_CharaLobby::~Scene_CharaLobby()
{
	DestroyWindow(m_Battle_Button);
	DestroyWindow(m_Shop_Button);
	DestroyWindow(m_Equip_Button);
	DestroyWindow(m_Prev_Button);
}

void Scene_CharaLobby::Initialize()
{
	m_Character = Manager_Data::Get_Instance()->Get_Current_User()->Get_Current_Character();

	RECT rect;
	GetClientRect(m_Hwnd, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;

	POINT battle_pos = { 10, 200 };
	POINT shop_pos = { battle_pos.x, battle_pos.y + 50 };
	POINT equip_pos = { battle_pos.x, shop_pos.y + 50 };
	POINT chara_select_pos = { battle_pos.x, rect.bottom - 45 };

	cout << "Scene_Lobby Initialized" << endl;
	m_Backbit->ClearBitMap();

	// ���� ��ư
	m_Battle_Button = CreateWindow("button", "�������� ���Ѵ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		battle_pos.x, battle_pos.y, 200, 35,
		m_Hwnd, (HMENU)S_CL_BATTLE_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���� ��ư
	m_Shop_Button = CreateWindow("button", "������ ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		shop_pos.x, shop_pos.y, 200, 35,
		m_Hwnd, (HMENU)S_CL_SHOP_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ��� ��ư
	m_Equip_Button = CreateWindow("button", "��� �����Ѵ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		equip_pos.x, equip_pos.y, 200, 35,
		m_Hwnd, (HMENU)S_CL_EQUIP_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ĳ���� ����â���� ��ư
	m_Prev_Button = CreateWindow("button", "ĳ���� ���� â����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		chara_select_pos.x, chara_select_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CL_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_CharaLobby::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		// Ŀ�ǵ�
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_CL_BATTLE_BUTTON:			// ������
			Battle();
			break;
		case S_CL_SHOP_BUTTON:				// ��������
			Shop();
			break;
		case S_CL_EQUIP_BUTTON:				// ���â����
			Equip();
			break;
		case S_CL_PREV_BUTTON:				// ĳ���� ����â����
			Prev();
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

void Scene_CharaLobby::Draw_Screen()
{
	HDC hdc;

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// Ÿ��Ʋ �׸���
	Draw_Title(hdc);
	// ĳ���� �׸���
	Draw_Chara(hdc);
	// ������ �׸���
	Draw_Equipment(hdc);
	// ���� �׸���
	Draw_Status(hdc);

	m_Backbit->DeleteBitmapDC(hdc);
}

void Scene_CharaLobby::Draw_Title(HDC _hdc)
{
	RECT rect;
	TCHAR text[] = "������ �ؾ��ϴ°�";
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

void Scene_CharaLobby::Draw_Chara(HDC _hdc)
{
	RECT rect;
	Manager_Image* mi = Manager_Image::Get_Instance();

	GetClientRect(m_Hwnd, &rect);
	int width = 96;
	int height = 96;
	int x = rect.right - width / 2 - 10;
	int y = 180;
	rect = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);
	Bitmap_Character* chara = mi->Get_CharaBitmap((TYPE_RACE)m_Character->Get_CharaIndex());
	chara->Draw_Character(_hdc, { x, y });
}

void Scene_CharaLobby::Draw_Equipment(HDC _hdc)
{
	RECT rect;
	HFONT myFont, oldFont;
	char equip_name[STRING_SIZE * 4];
	char equip_desc[STRING_SIZE * 7];

	wsprintf(equip_name, "<���ǰ>\n %s\n\n %s\n\n %s", m_Character->Get_WeaponName(), m_Character->Get_ArmorName(), m_Character->Get_AccessoryName());
	wsprintf(equip_desc, "\n\n%s\n\n%s\n\n%s", m_Character->Get_WeaponDesc(), m_Character->Get_ArmorDesc(), m_Character->Get_AccessoryDesc());

	// ��Ʈ ����
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	int width = 220;
	int height = 135;
	int x = rect.right - width / 2 - 10;
	int y = 227 + height / 2;
	rect = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

	rect = { rect.left + 10, rect.top + 10, rect.right - 10, rect.bottom - 10 };
	DrawText(_hdc, equip_name, strlen(equip_name), &rect, DT_LEFT);
	DrawText(_hdc, equip_desc, strlen(equip_desc), &rect, DT_RIGHT);

	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_CharaLobby::Draw_Status(HDC _hdc)
{
	RECT rect;
	HFONT myFont, oldFont;
	char stat_name[STRING_SIZE * 2];
	char stat_desc[STRING_SIZE * 2];

	// ��Ʈ ����
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	wsprintf(stat_name, "<�������ͽ�>\n Level:\n HP:\n ATK:\n DEF:\n DEX:\n AGI:\n ������:");
	wsprintf(stat_desc, "\n%d\n%d\n%d\n%d\n%d\n%d\n%d��", m_Character->Get_Level(), m_Character->Get_HP(), m_Character->Get_ATK(),
		m_Character->Get_DEF(), m_Character->Get_DEX(), m_Character->Get_AGI(), m_Character->Get_Currency());

	// ��Ʈ ����
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	GetClientRect(m_Hwnd, &rect);
	int width = 220;
	int height = 150;
	int x = rect.right - width / 2 - 10;
	int y = 360 + height / 2;
	rect = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

	rect = { rect.left + 10, rect.top + 10, rect.right - 10, rect.bottom - 10 };
	DrawText(_hdc, stat_name, strlen(stat_name), &rect, DT_LEFT);
	DrawText(_hdc, stat_desc, strlen(stat_desc), &rect, DT_RIGHT);


	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}


void Scene_CharaLobby::Battle()
{
	// ������ ������Ʈ�� ����
	ShellExecute(0, 0, "https://www.youtube.com/watch?v=x8rRQHtlaKc", 0, 0, SW_SHOW);
}

void Scene_CharaLobby::Shop()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Shop(m_Hwnd, m_Backbit));
}

void Scene_CharaLobby::Equip()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Equipment(m_Hwnd, m_Backbit));
}

void Scene_CharaLobby::Prev()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));
}
