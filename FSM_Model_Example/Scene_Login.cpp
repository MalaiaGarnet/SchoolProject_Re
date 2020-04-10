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

	// 로그인 버튼
	m_Login_button = CreateWindow("button", "로그인", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		login_button_pos.x, login_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_LOGIN_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 회원가입 버튼
	m_Register_button = CreateWindow("button", "회원가입", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		register_button_pos.x, register_button_pos.y, 100, 35,
		m_Hwnd, (HMENU)S_REGISTER_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// ID 입력칸
	m_Id_edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		id_edit_pos.x, id_edit_pos.y, 150, 25,
		m_Hwnd, (HMENU)S_ID_EDIT, API_Window_Main::Get_Instance()->hInst, NULL);

	// PASS 입력칸
	m_Pass_edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		pass_edit_pos.x, pass_edit_pos.y, 150, 25,
		m_Hwnd, (HMENU)S_PASS_EDIT, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Login::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	// 커맨드
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_LOGIN_BUTTON:
			Process_Login(); // 로그인 시작
			break;
		case S_REGISTER_BUTTON:
			Process_Register(); // 회원가입 시작
			break;
		}
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

/*	
	화면 그리기
*/
void Scene_Login::Draw_Screen()
{
	HDC hdc;
	RECT rect;

	HFONT myFont, oldFont;
	TCHAR title_text[20] = "접속 화면";
	TCHAR id_text[20] = "식별명:";
	TCHAR pass_text[20] = "암구호:";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// 사각형 영역 설정
	GetClientRect(m_Hwnd, &rect);
	rect.top = TITLE_TOP;
	rect.bottom = rect.top + 100;

	// 폰트 설정
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// 타이틀 그리기
	DrawText(hdc, title_text, strlen(title_text), &rect, DT_CENTER);

	// 사각형 영역 설정
	GetClientRect(m_Hwnd, &rect);
	rect.top = rect.bottom / 2 - 60;
	rect.bottom = rect.top + 30;
	rect.right = rect.right / 2 - 60;

	// 폰트 설정
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// 타이틀 그리기
	DrawText(hdc, id_text, strlen(id_text), &rect, DT_RIGHT | DT_VCENTER);

	// 사각형 영역 설정
	GetClientRect(m_Hwnd, &rect);
	rect.top = rect.bottom / 2 - 30;
	rect.bottom = rect.top + 30;
	rect.right = rect.right / 2 - 60;

	// 타이틀 그리기
	DrawText(hdc, pass_text, strlen(pass_text), &rect, DT_RIGHT);

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
	m_Backbit->DeleteBitmapDC(hdc);
}

// 로그인 처리
void Scene_Login::Process_Login()
{
	TCHAR id[STRING_SIZE];
	TCHAR pass[STRING_SIZE];

	GetDlgItemText(m_Hwnd, S_ID_EDIT, id, STRING_SIZE);
	GetDlgItemText(m_Hwnd, S_PASS_EDIT, pass, STRING_SIZE);

	// 아이디나 비밀번호 에디트가 비어있는 경우
	if (strlen(id) == 0 || strlen(pass) == 0)
	{
		// 오류 출력, 실행 종료
		MessageBox(m_Hwnd, "아이디, 또는 비밀번호를 입력하지 않았어요.", "회원가입 실패", MB_OK);
		return;
	}

	// 데이터 매니저에게서 해당 유저를 취득
	Data_User* user = Manager_Data::Get_Instance()->Search_Data(id);

	// 그런 유저 없는 경우
	if (user == nullptr)
	{
		// 오류 출력, 실행 종료
		MessageBox(m_Hwnd, "그런 유저는 없어요.", "로그인 실패", MB_OK);
		return;
	}

	// 비밀번호가 틀린 경우
	if (!Manager_Data::Get_Instance()->Check_Password(user, pass))
	{
		// 오류 출력, 실행 종료
		MessageBox(m_Hwnd, "비밀번호가 틀렸어요.", "로그인 실패", MB_OK);
		return;
	}

	// 성공하면 로비 씬으로
	Manager_Data::Get_Instance()->Change_User(user);
	//if (user->Get_Prologue() == false) // 프롤로그를 보지 않은 경우
	//	Manager_Scene::Get_Instance()->Change_Scene(new Scene_Prologue(m_Hwnd, m_Backbit));
	//else
		Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));

}

// 회원가입 처리
void Scene_Login::Process_Register()
{
	TCHAR id[STRING_SIZE];
	TCHAR pass[STRING_SIZE];

	GetDlgItemText(m_Hwnd, S_ID_EDIT, id, STRING_SIZE);
	GetDlgItemText(m_Hwnd, S_PASS_EDIT, pass, STRING_SIZE);

	// 아이디나 비밀번호 에디트가 비어있는 경우
	if (strlen(id) == 0 || strlen(pass) == 0)
	{
		// 오류 출력, 실행 종료
		MessageBox(m_Hwnd, "아이디, 또는 비밀번호를 입력하지 않았어요.", "회원가입 실패", MB_OK);
		return;
	}

	// 데이터 매니저에게서 해당 유저를 취득
	Data_User* user = Manager_Data::Get_Instance()->Search_Data(id);

	// 그런 유저 '있는' 경우
	if (user != nullptr)
	{
		// 오류 출력, 실행 종료
		MessageBox(m_Hwnd, "이미 동일한 아이디가 있어요.", "회원가입 실패", MB_OK);
		return;
	}

	TCHAR str[STRING_SIZE * 4];
	wsprintf(str, "이 정보로 가입할까요?\n아이디: %s\n비번: %s", id, pass);
	
	// 마지막 확인, 만약 취소 버튼을 눌렀다면 모두 도루묵화
	if (MessageBox(m_Hwnd, str, "회원가입 확인", MB_OKCANCEL) == IDCANCEL)
	{
		MessageBox(m_Hwnd, "회원가입을 취소했어요.", "회원가입 종료", MB_OK);
		return;
	}

	// 최종 회원가입처리
	Manager_Data::Get_Instance()->Create_Data(id, pass);
	MessageBox(m_Hwnd, "회원가입에 성공했어요.\n모험은 지금부터 시작이에요.", "회원가입 실패", MB_OK);
}
