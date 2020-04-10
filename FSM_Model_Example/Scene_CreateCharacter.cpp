#include "Scene_CreateCharacter.h"


Scene_CreateCharacter::Scene_CreateCharacter(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
}

Scene_CreateCharacter::~Scene_CreateCharacter()
{

	DestroyWindow(m_Name_Edit);
	DestroyWindow(m_Cancel_Button);
	DestroyWindow(m_Create_Button);
	DestroyWindow(m_Next_Button);
	DestroyWindow(m_Prev_Button);
}

void Scene_CreateCharacter::Initialize()
{
	user = Manager_Data::Get_Instance()->Get_Current_User();

	RECT rect;
	GetClientRect(m_Hwnd, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;

	POINT name_edit_pos = { rect.right / 2 - 75, rect.bottom - 90 };
	POINT create_button_pos = { rect.right - 160, rect.bottom - 45 };
	POINT cancel_button_pos = { 10, rect.bottom - 45 };
	POINT next_button_pos = { rect.right / 2 + 50, rect.bottom / 2 - 168 };
	POINT prev_button_pos = { rect.right / 2 - 50 - 32, rect.bottom / 2 - 168 };

	cout << "Scene_CreateCharacter Initialized" << endl;
	m_Backbit->ClearBitMap();

	// �̸� �Է� ����Ʈ
	m_Name_Edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		name_edit_pos.x, name_edit_pos.y, 150, 25,
		m_Hwnd, (HMENU)S_CC_NAME_EDIT, API_Window_Main::Get_Instance()->hInst, NULL);

	// ĳ���� ����� ��ư
	m_Create_Button = CreateWindow("button", "�̴�� �����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		create_button_pos.x, create_button_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CC_CREATE_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// �ڷ� ���ư��� ��ư
	m_Cancel_Button = CreateWindow("button", "���� ���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		cancel_button_pos.x, cancel_button_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CC_CANCEL_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���� ��ư
	m_Next_Button = CreateWindow("button", ">>", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		next_button_pos.x, next_button_pos.y, 32, 96,
		m_Hwnd, (HMENU)S_CC_NEXT_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ���� ��ư
	m_Prev_Button = CreateWindow("button", "<<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		prev_button_pos.x, prev_button_pos.y, 32, 96,
		m_Hwnd, (HMENU)S_CC_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_CreateCharacter::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		// Ŀ�ǵ�
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_CC_CREATE_BUTTON:			// ĳ���� ����
			Create_Character();
			break;
		case S_CC_CANCEL_BUTTON:			// �ڷ� ����
			Cancel();
			break;
		case S_CC_NEXT_BUTTON:			// �ڷ� ����
			Next();
			break;
		case S_CC_PREV_BUTTON:			// �ڷ� ����
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

void Scene_CreateCharacter::Draw_Screen()
{
	HDC hdc;
	RECT rect, title_rect, desc_rect, text_rect;
	HFONT myFont, oldFont;
	TCHAR title[] = "���� ����";
	Manager_Image* mi = Manager_Image::Get_Instance();
	int y_offset = -120; // ĳ���� �ڽ�

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();
	GetClientRect(m_Hwnd, &rect);

	// Ÿ��Ʋ
	// ��Ʈ ����
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	// �̸� �׸���
	GetClientRect(m_Hwnd, &title_rect);
	title_rect.top = TITLE_TOP;
	title_rect.bottom = title_rect.top + 100;
	DrawText(hdc, title, strlen(title), &title_rect, DT_CENTER);
	// ��Ʈ ����
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	// ���� ���� 
	GetClientRect(m_Hwnd, &desc_rect);
	desc_rect = { desc_rect.left + 40, desc_rect.top + 170, desc_rect.right - 40, desc_rect.bottom - 130 };
	Rectangle(hdc, desc_rect.left, desc_rect.top, desc_rect.right, desc_rect.bottom);

	// ĳ���� �̹���
	// �簢��
	Rectangle(hdc, rect.right / 2 - 48, rect.bottom / 2 - 48 + y_offset, rect.right / 2 + 48, rect.bottom / 2 + 48 + y_offset);
	// �̹���
	mi->Get_CharaBitmap((TYPE_RACE)m_Current_Cursor)->Draw_Character(hdc, { rect.right / 2, rect.bottom / 2 + y_offset });

	// ����
	// ��Ʈ ����
	myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	// ������ �׸���
	text_rect = desc_rect;
	text_rect.top = text_rect.top + 64;
	text_rect.bottom = text_rect.top + 100;
	const char* racename = Global_Info::Race_Type_Name[m_Current_Cursor];
	DrawText(hdc, racename, strlen(racename), &text_rect, DT_CENTER);
	// ��Ʈ ����
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	// ��Ʈ ����
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	// ���� �׸���
	text_rect = desc_rect;
	text_rect.top = text_rect.top + 96;
	const char* text = Global_Info::Race_Type_Desc[m_Current_Cursor];
	DrawText(hdc, text, strlen(text), &text_rect, DT_CENTER);
	// ��Ʈ ����
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);


	m_Backbit->DeleteBitmapDC(hdc);
}

void Scene_CreateCharacter::Cancel()
{
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));
}

void Scene_CreateCharacter::Create_Character()
{
	// �̸� ���
	TCHAR name[STRING_SIZE];
	GetDlgItemText(m_Hwnd, S_CC_NAME_EDIT, name, STRING_SIZE);

	// �̸� ����Ʈ�� ����ִ� ���
	if (strlen(name) == 0)
	{
		// ���� ���, ���� ����
		MessageBox(m_Hwnd, "�̸��� �����.", "���� ���� ����", MB_OK);
		return;
	}

	// ��� ������ ���
	Factory_JSKMaker* jskMaker = nullptr;
	switch (m_Current_Cursor) // ������ Ŀ���� ���� ��� �����ڰ� �޶�����
	{
	case TYPE_RACE::COMSOON:
		jskMaker = new Factory_JSKMaker_Comsoon();
		break;
	case TYPE_RACE::MOONSOON:
		jskMaker = new Factory_JSKMaker_Moonsoon();
		break;
	case TYPE_RACE::GONGSOON:
		jskMaker = new Factory_JSKMaker_Gongsoon();
		break;
	}

	// �������� ĳ���͸� �߰�
	user->Add_Character(new Data_Character((TYPE_RACE)m_Current_Cursor, name, jskMaker));
	MessageBox(m_Hwnd, "ĳ���͸� ��������!", "���� ���� ����", MB_OK);
	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));
}

void Scene_CreateCharacter::Next()
{
	m_Current_Cursor++;
	if (m_Current_Cursor >= Global_Info::Type_Size(TYPE_COUNT::RACE_COUNT))
		m_Current_Cursor = 0;
}

void Scene_CreateCharacter::Prev()
{
	m_Current_Cursor--;
	if (m_Current_Cursor < 0)
		m_Current_Cursor = Global_Info::Type_Size(TYPE_COUNT::RACE_COUNT) - 1;
}
