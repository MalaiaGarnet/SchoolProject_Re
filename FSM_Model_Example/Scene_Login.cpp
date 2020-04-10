#include "Scene_Login.h"
#include "API_Window_Main.h"
#include "Manager_Data.h"

#include "Scene_Lobby.h"
#include "Scene_Prologue.h"

Scene_Login::Scene_Login(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
}

Scene_Login::~Scene_Login()
{
	DestroyWindow(m_Login_button);
	DestroyWindow(m_Register_button);
	DestroyWindow(m_Id_edit);
	DestroyWindow(m_Pass_edit);
}

void Scene_Login::Initialize()
{
	RECT rect;
	GetClientRect(m_Hwnd, &rect);
	int center_x = rect.right / 2;
	int center_y = rect.bottom / 2;

	POINT id_edit_pos = { center_x - 50, center_y - 60 };
	POINT pass_edit_pos = { center_x - 50, center_y - 30 };
	POINT login_button_pos = { center_x + 20, center_y + 10 };
	POINT register_button_pos = { center_x - 120, center_y + 10 };

	cout << "Scene_Login Initialized" << endl;
	m_Backbit->ClearBitMap();

	// �α��� ��ư
	m_Login_button = CreateWindow("button", "�α���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		login_button_pos.x, login_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_LOGIN_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ȸ������ ��ư
	m_Register_button = CreateWindow("button", "ȸ������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		register_button_pos.x, register_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_REGISTER_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ID �Է�ĭ
	m_Id_edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		id_edit_pos.x, id_edit_pos.y, 150, 25,
		m_Hwnd, (HMENU)S_ID_EDIT, API_Window_Main::Get_Instance()->hInst, NULL);

	// PASS �Է�ĭ
	m_Pass_edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		pass_edit_pos.x, pass_edit_pos.y, 150, 25,
		m_Hwnd, (HMENU)S_PASS_EDIT, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Login::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	// Ŀ�ǵ�
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_LOGIN_BUTTON:
			Process_Login(); // �α��� ����
			break;
		case S_REGISTER_BUTTON:
			Process_Register(); // ȸ������ ����
			break;
		}
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

/*	
	ȭ�� �׸���
*/
void Scene_Login::Draw_Screen()
{
	HDC hdc;
	RECT rect;

	HFONT myFont, oldFont;
	TCHAR title_text[20] = "���� ȭ��";
	TCHAR id_text[20] = "�ĺ���:";
	TCHAR pass_text[20] = "�ϱ�ȣ:";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// �簢�� ���� ����
	GetClientRect(m_Hwnd, &rect);
	rect.top = TITLE_TOP;
	rect.bottom = rect.top + 100;

	// ��Ʈ ����
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// Ÿ��Ʋ �׸���
	DrawText(hdc, title_text, strlen(title_text), &rect, DT_CENTER);

	// �簢�� ���� ����
	GetClientRect(m_Hwnd, &rect);
	rect.top = rect.bottom / 2 - 60;
	rect.bottom = rect.top + 30;
	rect.right = rect.right / 2 - 60;

	// ��Ʈ ����
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// Ÿ��Ʋ �׸���
	DrawText(hdc, id_text, strlen(id_text), &rect, DT_RIGHT | DT_VCENTER);

	// �簢�� ���� ����
	GetClientRect(m_Hwnd, &rect);
	rect.top = rect.bottom / 2 - 30;
	rect.bottom = rect.top + 30;
	rect.right = rect.right / 2 - 60;

	// Ÿ��Ʋ �׸���
	DrawText(hdc, pass_text, strlen(pass_text), &rect, DT_RIGHT);

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
	m_Backbit->DeleteBitmapDC(hdc);
}

// �α��� ó��
void Scene_Login::Process_Login()
{
	TCHAR id[STRING_SIZE];
	TCHAR pass[STRING_SIZE];

	GetDlgItemText(m_Hwnd, S_ID_EDIT, id, STRING_SIZE);
	GetDlgItemText(m_Hwnd, S_PASS_EDIT, pass, STRING_SIZE);

	// ���̵� ��й�ȣ ����Ʈ�� ����ִ� ���
	if (strlen(id) == 0 || strlen(pass) == 0)
	{
		// ���� ���, ���� ����
		MessageBox(m_Hwnd, "���̵�, �Ǵ� ��й�ȣ�� �Է����� �ʾҾ��.", "ȸ������ ����", MB_OK);
		return;
	}

	// ������ �Ŵ������Լ� �ش� ������ ���
	Data_User* user = Manager_Data::Get_Instance()->Search_Data(id);

	// �׷� ���� ���� ���
	if (user == nullptr)
	{
		// ���� ���, ���� ����
		MessageBox(m_Hwnd, "�׷� ������ �����.", "�α��� ����", MB_OK);
		return;
	}

	// ��й�ȣ�� Ʋ�� ���
	if (!Manager_Data::Get_Instance()->Check_Password(user, pass))
	{
		// ���� ���, ���� ����
		MessageBox(m_Hwnd, "��й�ȣ�� Ʋ�Ⱦ��.", "�α��� ����", MB_OK);
		return;
	}

	// �����ϸ� �κ� ������
	Manager_Data::Get_Instance()->Change_User(user);
	//if (user->Get_Prologue() == false) // ���ѷα׸� ���� ���� ���
	//	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Prologue(m_Hwnd, m_Backbit));
	//else
		Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));

}

// ȸ������ ó��
void Scene_Login::Process_Register()
{
	TCHAR id[STRING_SIZE];
	TCHAR pass[STRING_SIZE];

	GetDlgItemText(m_Hwnd, S_ID_EDIT, id, STRING_SIZE);
	GetDlgItemText(m_Hwnd, S_PASS_EDIT, pass, STRING_SIZE);

	// ���̵� ��й�ȣ ����Ʈ�� ����ִ� ���
	if (strlen(id) == 0 || strlen(pass) == 0)
	{
		// ���� ���, ���� ����
		MessageBox(m_Hwnd, "���̵�, �Ǵ� ��й�ȣ�� �Է����� �ʾҾ��.", "ȸ������ ����", MB_OK);
		return;
	}

	// ������ �Ŵ������Լ� �ش� ������ ���
	Data_User* user = Manager_Data::Get_Instance()->Search_Data(id);

	// �׷� ���� '�ִ�' ���
	if (user != nullptr)
	{
		// ���� ���, ���� ����
		MessageBox(m_Hwnd, "�̹� ������ ���̵� �־��.", "ȸ������ ����", MB_OK);
		return;
	}

	TCHAR str[STRING_SIZE * 4];
	wsprintf(str, "�� ������ �����ұ��?\n���̵�: %s\n���: %s", id, pass);
	
	// ������ Ȯ��, ���� ��� ��ư�� �����ٸ� ��� ���繬ȭ
	if (MessageBox(m_Hwnd, str, "ȸ������ Ȯ��", MB_OKCANCEL) == IDCANCEL)
	{
		MessageBox(m_Hwnd, "ȸ�������� ����߾��.", "ȸ������ ����", MB_OK);
		return;
	}

	// ���� ȸ������ó��
	Manager_Data::Get_Instance()->Create_Data(id, pass);
	MessageBox(m_Hwnd, "ȸ�����Կ� �����߾��.\n������ ���ݺ��� �����̿���.", "ȸ������ ����", MB_OK);
}
