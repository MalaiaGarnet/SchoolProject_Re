#include "API_Window_Frame.h"

// �̱���
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
	������ ����
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
	WndClass.hInstance = _inst;	// ���� �����ڿ��Լ� �ν��Ͻ��� �޾ƿ´�
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = "���� �������";
	RegisterClass(&WndClass);
	hWnd = CreateWindow("���� �������", "�� ������ Ÿ��Ʋ�̾�",
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
	�޽��� �ް� ó��
*/
int API_Window_Frame::Run(MSG _msg)
{
	TranslateMessage(&_msg);	// ������ �ִ� �޽����� �ؼ�
	DispatchMessage(&_msg);	// �޽����� ���� ���ν��� ����

	return (int)_msg.wParam;
}

/*
	���ν���
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

		SetTimer(hwnd, 100, 200, NULL);  // �ִϸ��̼� ���� Ÿ�̸�
		Manager_Scene::Create_Instance()->Change_Scene(new Scene_Title(hwnd, backbit));
		break;

	// Ÿ�̸�
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
	// ���콺 �̵�
	case WM_MOUSEMOVE:
		// ��ǥ�� ����, ���� �������� ��ġ�� ������ ��ǥ�� ����� ��ǥ�� �ٲ۴�
		mouse->Set_Coord({LOWORD(lparam), HIWORD(lparam)}, hwnd);

		// ���콺 ������ Ŭ���� ��Ȳ���� �����̰� �ִٸ� PAINT �Ѵ�
		if (mouse->Get_Left_ClickState() == CLICK_STATE::DOWN)
		{
			draw->Draw_Move();
		}
		break;

	// ���� ���콺 Ŭ��
	case WM_LBUTTONDOWN:
		mouse->Set_Left_ClickState(CLICK_STATE::DOWN);
		draw->Draw_Start(mouse->Get_CurrentCoord(hwnd));
		break;
	case WM_LBUTTONUP:
		mouse->Set_Left_ClickState(CLICK_STATE::UP);
		draw->Draw_End();
		break;

	// ������ ���콺 Ŭ��
	case WM_RBUTTONDOWN:
		mouse->Set_Right_ClickState(CLICK_STATE::DOWN);

		// ��Ŭ���� ������ �����
		if (MessageBox(hwnd, "������ �� ����������?", "���� �����", MB_YESNO) == IDYES)
		{
			backbit->ClearBitMap();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_RBUTTONUP:
		mouse->Set_Right_ClickState(CLICK_STATE::UP);
		break;

	// Ŀ�ǵ�
	case WM_COMMAND:
		menu->Process(wparam); // �޴����� Ŀ�ǵ� �ѱ��
		// draw �޼ҵ� ����
		if (draw != nullptr)
			delete draw;
		//draw = Create_Method(menu->Get_DrawType(), backbit, mouse, hwnd);

		return 0;

		*/
	// �׸���
	case WM_PAINT:
		// ������ ����
		hdc = BeginPaint(hwnd, &ps);
		backbit->ScreenDraw(hdc, 0, 0);
		EndPaint(hwnd, &ps);
		// ������ ����
		break;
	// ������ �Ѽ���
	case WM_DESTROY:
		delete backbit;
		KillTimer(hwnd, 100);
		PostQuitMessage(0);
		break;
	}


	return DefWindowProc(hwnd, message, wparam, lparam);
}