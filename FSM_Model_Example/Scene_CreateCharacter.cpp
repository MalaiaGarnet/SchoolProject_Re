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

	// 이름 입력 에디트
	m_Name_Edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		name_edit_pos.x, name_edit_pos.y, 150, 25,
		m_Hwnd, (HMENU)S_CC_NAME_EDIT, API_Window_Main::Get_Instance()->hInst, NULL);

	// 캐릭터 만들기 버튼
	m_Create_Button = CreateWindow("button", "이대로 만든다", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		create_button_pos.x, create_button_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CC_CREATE_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 뒤로 돌아가기 버튼
	m_Cancel_Button = CreateWindow("button", "생성 취소", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		cancel_button_pos.x, cancel_button_pos.y, 150, 35,
		m_Hwnd, (HMENU)S_CC_CANCEL_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 다음 버튼
	m_Next_Button = CreateWindow("button", ">>", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		next_button_pos.x, next_button_pos.y, 32, 96,
		m_Hwnd, (HMENU)S_CC_NEXT_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	// 이전 버튼
	m_Prev_Button = CreateWindow("button", "<<", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		prev_button_pos.x, prev_button_pos.y, 32, 96,
		m_Hwnd, (HMENU)S_CC_PREV_BUTTON, API_Window_Main::Get_Instance()->hInst, NULL);

	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_CreateCharacter::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		// 커맨드
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case S_CC_CREATE_BUTTON:			// 캐릭터 생성
			Create_Character();
			break;
		case S_CC_CANCEL_BUTTON:			// 뒤로 가기
			Cancel();
			break;
		case S_CC_NEXT_BUTTON:			// 뒤로 가기
			Next();
			break;
		case S_CC_PREV_BUTTON:			// 뒤로 가기
			Prev();
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

void Scene_CreateCharacter::Draw_Screen()
{
	HDC hdc;
	RECT rect, title_rect, desc_rect, text_rect;
	HFONT myFont, oldFont;
	TCHAR title[] = "문자 생성";
	Manager_Image* mi = Manager_Image::Get_Instance();
	int y_offset = -120; // 캐릭터 박스

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();
	GetClientRect(m_Hwnd, &rect);

	// 타이틀
	// 폰트 설정
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	// 이름 그리기
	GetClientRect(m_Hwnd, &title_rect);
	title_rect.top = TITLE_TOP;
	title_rect.bottom = title_rect.top + 100;
	DrawText(hdc, title, strlen(title), &title_rect, DT_CENTER);
	// 폰트 해제
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	// 설명 상자 
	GetClientRect(m_Hwnd, &desc_rect);
	desc_rect = { desc_rect.left + 40, desc_rect.top + 170, desc_rect.right - 40, desc_rect.bottom - 130 };
	Rectangle(hdc, desc_rect.left, desc_rect.top, desc_rect.right, desc_rect.bottom);

	// 캐릭터 이미지
	// 사각형
	Rectangle(hdc, rect.right / 2 - 48, rect.bottom / 2 - 48 + y_offset, rect.right / 2 + 48, rect.bottom / 2 + 48 + y_offset);
	// 이미지
	mi->Get_CharaBitmap((TYPE_RACE)m_Current_Cursor)->Draw_Character(hdc, { rect.right / 2, rect.bottom / 2 + y_offset });

	// 설명
	// 폰트 설정
	myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	// 종족명 그리기
	text_rect = desc_rect;
	text_rect.top = text_rect.top + 64;
	text_rect.bottom = text_rect.top + 100;
	const char* racename = Global_Info::Race_Type_Name[m_Current_Cursor];
	DrawText(hdc, racename, strlen(racename), &text_rect, DT_CENTER);
	// 폰트 해제
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	// 폰트 설정
	myFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "돋움");
	oldFont = (HFONT)SelectObject(hdc, myFont);
	// 설명 그리기
	text_rect = desc_rect;
	text_rect.top = text_rect.top + 96;
	const char* text = Global_Info::Race_Type_Desc[m_Current_Cursor];
	DrawText(hdc, text, strlen(text), &text_rect, DT_CENTER);
	// 폰트 해제
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
	// 이름 취득
	TCHAR name[STRING_SIZE];
	GetDlgItemText(m_Hwnd, S_CC_NAME_EDIT, name, STRING_SIZE);

	// 이름 에디트가 비어있는 경우
	if (strlen(name) == 0)
	{
		// 오류 출력, 실행 종료
		MessageBox(m_Hwnd, "이름이 없어요.", "문자 생성 실패", MB_OK);
		return;
	}

	// 장비 제공자 취득
	Factory_JSKMaker* jskMaker = nullptr;
	switch (m_Current_Cursor) // 선택한 커서에 따라 장비 제공자가 달라진다
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

	// 유저에게 캐릭터를 추가
	user->Add_Character(new Data_Character((TYPE_RACE)m_Current_Cursor, name, jskMaker));
	MessageBox(m_Hwnd, "캐릭터를 만들었어요!", "문자 생성 성공", MB_OK);
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
