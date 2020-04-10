#include "Scene_Lobby.h"
#include "API_Window_Main.h"


Scene_Lobby::Scene_Lobby(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
	m_Create_Chara_Button = NULL;
	m_Logout_Button = NULL;
	m_Unregister_Button = NULL;
	m_Play_Button = NULL;
	m_Remove_Chara_Button = NULL;
	m_Next_Button = NULL;
	m_Prev_Button = NULL;
	user = nullptr;
	m_Current_Cursor = 0;
}

Scene_Lobby::~Scene_Lobby()
{
	DestroyWindow(m_Create_Chara_Button);
	DestroyWindow(m_Logout_Button);
	DestroyWindow(m_Unregister_Button);
	
	DestroyWindow(m_Play_Button);
	DestroyWindow(m_Remove_Chara_Button);
	DestroyWindow(m_Next_Button);
	DestroyWindow(m_Prev_Button);
}

void Scene_Lobby::Initialize()
{
	user = Manager_Data::Get_Instance()->Get_Current_User();
	user->Set_Prologue(true);

	RECT rect;
	GetClientRect(m_Hwnd, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;

	POINT create_chara_button_pos = { 10, rect.bottom - 90 };
	POINT logout_button_pos = { 10, rect.bottom - 45 };
	POINT unregister_button_pos = { 120, rect.bottom - 45 };

	POINT play_button_pos = { rect.right / 2 - 60, rect.bottom - 135 };
	POINT remove_button_pos = { rect.right / 2 - 60, rect.bottom - 95 };
	POINT next_button_pos = { rect.right / 2 + 65, rect.bottom - 135 };
	POINT prev_button_pos = { rect.right / 2 - 60 - 45, rect.bottom - 135 };

	cout << "Scene_Lobby Initialized" << endl;
	m_Backbit->ClearBitMap();


	// ĳ���� ���� ��ư
	m_Create_Chara_Button = CreateWindow("button", "���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		create_chara_button_pos.x, create_chara_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_CREATE_CHARA_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// �α׾ƿ� ��ư
	m_Logout_Button = CreateWindow("button", "���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		logout_button_pos.x, logout_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_LOGOUT_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ȸ��Ż�� ��ư
	m_Unregister_Button = CreateWindow("button", "ȸ�� Ż��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		unregister_button_pos.x, unregister_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_UNREGISTER_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���� ���� ��ư
	m_Play_Button = CreateWindow("button", "���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		play_button_pos.x, play_button_pos.y, 120, 35,
		m_Hwnd, (HMENU)S_CHARA_PLAY_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ĳ���� ���� ��ư
	m_Remove_Chara_Button = CreateWindow("button", "���� ����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		remove_button_pos.x, remove_button_pos.y, 120, 35,
		m_Hwnd, (HMENU)S_CHARA_REMOVE_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ������ ��ư
	m_Next_Button = CreateWindow("button", ">>", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		next_button_pos.x, next_button_pos.y, 40, 75,
		m_Hwnd, (HMENU)S_CHARA_NEXT_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// �ڷ� ��ư
	m_Prev_Button = CreateWindow("button", "<<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		prev_button_pos.x, prev_button_pos.y, 40, 75,
		m_Hwnd, (HMENU)S_CHARA_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Lobby::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	// Ŀ�ǵ�
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_CREATE_CHARA_BUTTON:			// ĳ���� ����
			Create_Character();
			break;
		case S_LOGOUT_BUTTON:					// �α׾ƿ�
			Logout();
			break;
		case S_UNREGISTER_BUTTON:				// ȸ��Ż��
			Unregister();
			break;
		case S_CHARA_PLAY_BUTTON:				// ĳ���ͷ� �÷���
			Play();
			break;
		case S_CHARA_REMOVE_BUTTON:		// ĳ���� �����
			Remove_Character();
			break;
		case S_CHARA_NEXT_BUTTON:			// ���� ĳ����
			Next();
			break;
		case S_CHARA_PREV_BUTTON:			// ���� ĳ����
			Prev();
			break;
		}

		InvalidateRect(m_Hwnd, NULL, FALSE);
		return 0;

	// �׸���
	case WM_PAINT:
		// ������ ����
		Draw_Screen();
		Update_Buttons();
		// ������ ����
		break;
	}
	return false;
}

void Scene_Lobby::Draw_Screen()
{
	HDC hdc;
	RECT rect;
	HFONT myFont, oldFont;
	TCHAR text[] = "���� ����";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// ��Ʈ ����
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// Ÿ��Ʋ �׸���
	GetClientRect(m_Hwnd, &rect);
	rect.top = TITLE_TOP;
	rect.bottom = rect.top + 100;
	DrawText(hdc, text, strlen(text), &rect, DT_CENTER);

	// ��Ʈ ����
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	// ���� �簢�� ���� �����
	GetClientRect(m_Hwnd, &rect);
	int width = 200;
	int height = 280;
	rect.left = rect.right / 2 - width / 2;
	rect.right = rect.right / 2 + width / 2;
	rect.top = rect.bottom / 2 - height / 2;
	rect.bottom = rect.bottom / 2 + height / 2;

	// ĳ���� ���� �׸���
	Draw_Slot(user->Get_Character(m_Current_Cursor - 1), hdc, rect, { -20 - width, 50 });
	Draw_Slot(user->Get_Character(m_Current_Cursor), hdc, rect, { 0, 10 });
	Draw_Slot(user->Get_Character(m_Current_Cursor + 1), hdc, rect, { 20 + width, 50 });

	m_Backbit->DeleteBitmapDC(hdc);

}

// ĳ���� ���� �׸���
void Scene_Lobby::Draw_Slot(Data_Character* _chara, HDC _hdc, RECT _rect, POINT _offset)
{
	HFONT myFont, oldFont;
	RECT rect = { _rect.left + _offset.x, _rect.top + _offset.y, _rect.right + _offset.x, _rect.bottom + _offset.y };
	Manager_Image* mi = Manager_Image::Get_Instance();
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (_chara == nullptr) // ĳ���Ͱ� ���� ���
		return;

	Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom); // ���� ��ü
	Rectangle(_hdc, rect.left, rect.bottom - 30, rect.right, rect.bottom); // �̸� �� ��

	// ĳ���� �̹���
	RECT image_rect = { rect.left + width / 2 - 46, rect.top - 46, rect.left + width / 2 + 46, rect.top + 46 };
	Rectangle(_hdc, image_rect.left, image_rect.top, image_rect.right, image_rect.bottom); // �̹��� �� ��
	mi->Get_CharaBitmap(_chara->Get_CharaIndex())->Draw_Character(_hdc, { image_rect.left + 46, image_rect.top + 46 });

	// ĳ���� ����
	// ��Ʈ ����
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(_hdc, myFont);
	// �̸� �׸���
	char name[STRING_SIZE * 2];
	wsprintf(name, "%s %s", Global_Info::Race_Type_Name[_chara->Get_CharaIndex()], _chara->Get_Name());
	RECT name_rect = { rect.left, rect.bottom - 25, rect.right, rect.bottom - 5 };
	DrawText(_hdc, name, strlen(name), &name_rect, DT_CENTER);
	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);

	// ��Ʈ ����
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	oldFont = (HFONT)SelectObject(_hdc, myFont);

	// ���� �׸���
	RECT stat_rect = { rect.left + 10, rect.top + 50, rect.right - 10, rect.bottom - 10 };
	char stat_text[STRING_SIZE * 4] = "";
	wsprintf(stat_text, "Level:\nHP:\nATK:\nDEF:\nDEX:\nAGI:\n����:\n\n��:\n\n��ű�:");
	DrawText(_hdc, stat_text, strlen(stat_text), &stat_rect, DT_LEFT);
	
	wsprintf(stat_text, "%d\n%d\n%d\n%d\n%d\n%d\n\n%s\n\n%s\n\n%s", _chara->Get_Level(), _chara->Get_HP(), _chara->Get_ATK(), _chara->Get_DEF(), _chara->Get_DEX(), _chara->Get_AGI(),
		_chara->Get_WeaponName(), _chara->Get_ArmorName(), _chara->Get_AccessoryName());
	DrawText(_hdc, stat_text, strlen(stat_text), &stat_rect, DT_RIGHT);

	// ��Ʈ ����
	SelectObject(_hdc, oldFont);
	DeleteObject(myFont);
}

void Scene_Lobby::Update_Buttons()
{
	// ������ ��ư ����
	if (m_Current_Cursor <= 0)
		ShowWindow(m_Prev_Button, SW_HIDE);
	else
		ShowWindow(m_Prev_Button, SW_SHOW);
	if (m_Current_Cursor >= user->Get_Character_Size() - 1)
		ShowWindow(m_Next_Button, SW_HIDE);
	else
		ShowWindow(m_Next_Button, SW_SHOW);
	if (user->Get_Character_Size() == 0)
	{
		ShowWindow(m_Play_Button, SW_HIDE);
		ShowWindow(m_Remove_Chara_Button, SW_HIDE);
	}
	else
	{
		ShowWindow(m_Play_Button, SW_SHOW);
		ShowWindow(m_Remove_Chara_Button, SW_SHOW);
	}
}

void Scene_Lobby::Logout()
{
	// �α׾ƿ�
	if (MessageBox(m_Hwnd, "������ ���⼭ �׸��ұ��?", "���� ����", MB_OKCANCEL) == IDOK)
	{
		MessageBox(m_Hwnd, "�ȳ�~", "���� ����", MB_OK);
		Manager_Scene::Get_Instance()->Change_Scene(new Scene_Login(m_Hwnd, m_Backbit));
	}
}

void Scene_Lobby::Unregister()
{
	// ȸ�� Ż��
	if (MessageBox(m_Hwnd, "������ Ż���ұ��?\nQueen Zinna���� �����Ͻǰſ���.", "ȸ�� Ż��", MB_OKCANCEL) == IDOK)
	{
		Manager_Data::Get_Instance()->Remove_Data(user);
		MessageBox(m_Hwnd, "��ư �� �濡 ����� ����� ��������.", "ȸ�� Ż��", MB_OK);
		MessageBox(m_Hwnd, "�ȳ�~", "ȸ�� Ż��", MB_OK);
		Manager_Scene::Get_Instance()->Change_Scene(new Scene_Login(m_Hwnd, m_Backbit));
	}
}

void Scene_Lobby::Play()
{
	// ĳ���Ͱ� �ϳ��� ���� ���
	if (user->Get_Character_Size() == 0)
	{
		MessageBox(m_Hwnd, "�ϴ� ĳ���ͺ��� ���弼��.", "���� ���� ����", MB_OK);
		return;
	}
	// ���õ� ĳ���͸� ��ü
	user->Change_Current_Character(m_Current_Cursor);
	// ĳ���� �κ� ������
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_CharaLobby(m_Hwnd, m_Backbit));
}

void Scene_Lobby::Create_Character()
{
	// ĳ���� ���� ������
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_CreateCharacter(m_Hwnd, m_Backbit));
}

void Scene_Lobby::Remove_Character()
{
	// ĳ���Ͱ� �ϳ��� ���� ���
	if (user->Get_Character_Size() == 0)
	{
		MessageBox(m_Hwnd, "���� ĳ���Ͱ� ������.", "���� ���� ����", MB_OK);
		return;
	}

	if (MessageBox(m_Hwnd, "�� ĳ���͸� ������ ������?\n����ų �� �����.", "���� ����", MB_OKCANCEL) == IDOK)
	{
		// ĳ���� ����
		user->Remove_Character(user->Get_Character(m_Current_Cursor));
		MessageBox(m_Hwnd, "��ư �� �濡 ĳ������ �λ��� ��������.", "���� ����", MB_OK);
		MessageBox(m_Hwnd, "���� ���!", "���� ����", MB_OK);
		m_Current_Cursor -= 1;
		if (m_Current_Cursor < 0) m_Current_Cursor = 0;
	}
	else
	{
		// ���� ���
		MessageBox(m_Hwnd, "���� �����̿���.\n������ �������� ���� �� �־��.", "���� ����", MB_OK);
	}
}

void Scene_Lobby::Next()
{
	if(m_Current_Cursor < user->Get_Character_Size() - 1)
		m_Current_Cursor++;
}

void Scene_Lobby::Prev()
{
	if (m_Current_Cursor > 0)
		m_Current_Cursor--;
}
