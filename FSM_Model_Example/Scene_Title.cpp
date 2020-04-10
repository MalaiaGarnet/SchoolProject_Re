#include "Scene_Title.h"
#include "Scene_Login.h"
#include "Manager_Scene.h"
Scene_Title::Scene_Title(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit)
{
	flick = false;
	title_y = -100;
}

Scene_Title::~Scene_Title()
{
}

void Scene_Title::Initialize()
{
	cout << "Scene_Title Initialized" << endl;
	InvalidateRect(m_Hwnd, NULL, TRUE);
	SetTimer(m_Hwnd, 1, 20, NULL);
}

bool Scene_Title::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	// 타이머
	case WM_TIMER:
		switch (wparam)
		{
		case 1: // 타이틀이 내려오는 타이머
			title_y += 2;
			InvalidateRect(m_Hwnd, NULL, FALSE);

			// 타이틀이 일정 위치까지 도달했다면
			if (title_y > 100)
			{
				KillTimer(m_Hwnd, 1); // 타이머 끄기
				SetTimer(m_Hwnd, 2, 750, NULL);
			}

			break;
		case 2: // 이후 깜빡임
			flick = !flick;
			InvalidateRect(m_Hwnd, NULL, FALSE);
			break;
		}
		break;

	case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_RETURN:
			KillTimer(m_Hwnd, 1);
			KillTimer(m_Hwnd, 2);
			Manager_Scene::Get_Instance()->Change_Scene(new Scene_Login(m_Hwnd, m_Backbit));
			break;
		}
		break;

	// 그리기
	case WM_PAINT:
		// 페인팅 시작
		Draw_Screen();
		// 페인팅 종료
		break;
	}
	return false;
}

void Scene_Title::Draw_Screen()
{
	HDC hdc;
	RECT rect;

	HFONT myFont, oldFont;
	TCHAR title_text[20] = "김진아의 역습";
	TCHAR desc_text[30] = "엔-타-키를 눌러서 시작하기";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// 사각형 영역 설정
	GetClientRect(m_Hwnd, &rect);
	rect.top = title_y;
	rect.bottom = 200;

	// 폰트 설정
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// 타이틀 그리기
	DrawText(hdc, title_text, strlen(title_text), &rect, DT_CENTER);

	if (flick)
	{
		// 사각형 영역 설정
		GetClientRect(m_Hwnd, &rect);
		rect.top = rect.bottom - 200;
		rect.bottom = rect.top + 100;

		// 폰트 설정
		myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
		oldFont = (HFONT)SelectObject(hdc, myFont);

		// 설명 그리기
		DrawText(hdc, desc_text, strlen(desc_text), &rect, DT_CENTER);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
	m_Backbit->DeleteBitmapDC(hdc);
}
