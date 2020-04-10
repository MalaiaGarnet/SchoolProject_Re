#include "Scene_Prologue.h"
#include "Manager_Scene.h"
#include "Scene_Lobby.h"

void Scene_Prologue::Initialize()
{
	RECT rect;
	GetClientRect(m_Hwnd, &rect);

	cout << "Scene_Prologue Initialized" << endl;
	m_Backbit->ClearBitMap();
	text_y = rect.bottom + 50;	// 대서사시 텍스트의 위치를 지정

	SetTimer(m_Hwnd, 1, 20, NULL);
	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Prologue::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	// 타이머
	case WM_TIMER:
		switch (wparam)
		{
		case 1:
			text_y -= 2;
			InvalidateRect(m_Hwnd, NULL, FALSE);

			// 텍스트가 다 올라갔으면
			if (text_y < -200)
			{
				KillTimer(m_Hwnd, 1); // 타이머 죽이기
				Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));
			}

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

void Scene_Prologue::Draw_Screen()
{
	HDC hdc;
	RECT rect;

	HFONT myFont, oldFont;
	TCHAR text[] = "때는 바야흐로 2019년...\n\n세상은 유니티로 물들어가고 있었다...\n\n사람들이 모두 유니티에 빠져 과제를 안하기 시작하자...\n\nQueen Zinnas는\n 영웅을 모아 그 해로운 엔진을 물리치기로 한다...\n\n난세를 구할 영웅은 누가 될 것인가...";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// 사각형 영역 설정
	GetClientRect(m_Hwnd, &rect);
	rect.top = text_y;
	rect.bottom = rect.top + 600;

	// 폰트 설정
	myFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "궁서");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// 타이틀 그리기
	DrawText(hdc, text, strlen(text), &rect, DT_CENTER);


	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
	m_Backbit->DeleteBitmapDC(hdc);
}
