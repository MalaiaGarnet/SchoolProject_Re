#include "API_Window_Frame.h"

// 싱글턴
API_Window_Frame* API_Window_Frame::instance = nullptr;

API_Window_Frame* API_Window_Frame::Create_Instance()
{
	if (instance == nullptr)
		instance = new API_Window_Frame();
	return instance;
}

API_Window_Frame* API_Window_Frame::Get_Instance()
{
	return instance;
}

void API_Window_Frame::Release_Instance()
{
	delete instance;
	instance = nullptr;
}

/*
	윈도우 생성
*/
void API_Window_Frame::Initialize(HINSTANCE _inst)
{
	WNDCLASS WndClass;

	hInst = _inst;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = Process;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = _inst;	// 메인 관리자에게서 인스턴스를 받아온다
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = "나는 윈도우야";
	RegisterClass(&WndClass);
	hWnd = CreateWindow("나는 윈도우야", "난 윈도우 타이틀이야",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		480,
		640,
		NULL,
		NULL,
		_inst,
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
}

/*
	메시지 받고 처리
*/
int API_Window_Frame::Run(MSG _msg)
{
	TranslateMessage(&_msg);	// 메인이 주는 메시지를 해석
	DispatchMessage(&_msg);	// 메시지에 따른 프로시저 실행

	return (int)_msg.wParam;
}

/*
	프로시저
*/
LRESULT CALLBACK API_Window_Frame::Process(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	HWND hDlg = NULL;
	Att_Mouse* mouse = Att_Mouse::Get_Instance();
	static Att_BackBit* backbit = nullptr;
	static Att_Menu* menu = nullptr;
	static Method_Draw* draw = nullptr;

	HDC hdc;
	PAINTSTRUCT ps;
	RECT client_rect;

	Manager_Scene::Get_Instance()->Run(message, wparam, lparam);
	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &client_rect);
		backbit = new Att_BackBit(hwnd, client_rect.bottom, client_rect.right);
		menu = new Att_Menu(IDR_MENU1);
		draw = new Method_Draw(backbit, mouse, hwnd);
		ReleaseDC(hwnd, hdc);

		SetTimer(hwnd, 100, 200, NULL);  // 애니메이션 전용 타이머
		Manager_Scene::Create_Instance()->Change_Scene(new Scene_Title(hwnd, backbit));
		break;

	// 타이머
	case WM_TIMER:
		switch (wparam)
		{
		case 100:
			Get_Instance()->frame_tick++;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		break;
		/*
	// 마우스 이동
	case WM_MOUSEMOVE:
		// 좌표를 수정, 현재 윈도우의 위치를 대입해 좌표를 모니터 좌표로 바꾼다
		mouse->Set_Coord({LOWORD(lparam), HIWORD(lparam)}, hwnd);

		// 마우스 왼쪽을 클릭한 상황에서 움직이고 있다면 PAINT 한다
		if (mouse->Get_Left_ClickState() == CLICK_STATE::DOWN)
		{
			draw->Draw_Move();
		}
		break;

	// 왼쪽 마우스 클릭
	case WM_LBUTTONDOWN:
		mouse->Set_Left_ClickState(CLICK_STATE::DOWN);
		draw->Draw_Start(mouse->Get_CurrentCoord(hwnd));
		break;
	case WM_LBUTTONUP:
		mouse->Set_Left_ClickState(CLICK_STATE::UP);
		draw->Draw_End();
		break;

	// 오른쪽 마우스 클릭
	case WM_RBUTTONDOWN:
		mouse->Set_Right_ClickState(CLICK_STATE::DOWN);

		// 우클릭시 지울지 물어본다
		if (MessageBox(hwnd, "ㄹㅇ루 다 지워버려요?", "전부 지우기", MB_YESNO) == IDYES)
		{
			backbit->ClearBitMap();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_RBUTTONUP:
		mouse->Set_Right_ClickState(CLICK_STATE::UP);
		break;

	// 커맨드
	case WM_COMMAND:
		menu->Process(wparam); // 메뉴한테 커맨드 넘기기
		// draw 메소드 갱신
		if (draw != nullptr)
			delete draw;
		//draw = Create_Method(menu->Get_DrawType(), backbit, mouse, hwnd);

		return 0;

		*/
	// 그리기
	case WM_PAINT:
		// 페인팅 시작
		hdc = BeginPaint(hwnd, &ps);
		backbit->ScreenDraw(hdc, 0, 0);
		EndPaint(hwnd, &ps);
		// 페인팅 종료
		break;
	// 윈도우 뿌수기
	case WM_DESTROY:
		delete backbit;
		KillTimer(hwnd, 100);
		PostQuitMessage(0);
		break;
	}


	return DefWindowProc(hwnd, message, wparam, lparam);
}