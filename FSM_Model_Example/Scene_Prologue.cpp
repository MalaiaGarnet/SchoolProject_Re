#include "Scene_Prologue.h"
#include "Manager_Scene.h"
#include "Scene_Lobby.h"

void Scene_Prologue::Initialize()
{
	RECT rect;
	GetClientRect(m_Hwnd, &rect);

	cout << "Scene_Prologue Initialized" << endl;
	m_Backbit->ClearBitMap();
	text_y = rect.bottom + 50;	// �뼭��� �ؽ�Ʈ�� ��ġ�� ����

	SetTimer(m_Hwnd, 1, 20, NULL);
	InvalidateRect(m_Hwnd, NULL, TRUE);
}

bool Scene_Prologue::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	// Ÿ�̸�
	case WM_TIMER:
		switch (wparam)
		{
		case 1:
			text_y -= 2;
			InvalidateRect(m_Hwnd, NULL, FALSE);

			// �ؽ�Ʈ�� �� �ö�����
			if (text_y < -200)
			{
				KillTimer(m_Hwnd, 1); // Ÿ�̸� ���̱�
				Manager_Scene::Get_Instance()->Change_Scene(new Scene_Lobby(m_Hwnd, m_Backbit));
			}

			break;
		}
		break;

	// �׸���
	case WM_PAINT:
		// ������ ����
		Draw_Screen();
		// ������ ����
		break;
	}
	return false;
}

void Scene_Prologue::Draw_Screen()
{
	HDC hdc;
	RECT rect;

	HFONT myFont, oldFont;
	TCHAR text[] = "���� �پ���� 2019��...\n\n������ ����Ƽ�� ������ �־���...\n\n������� ��� ����Ƽ�� ���� ������ ���ϱ� ��������...\n\nQueen Zinnas��\n ������ ��� �� �طο� ������ ����ġ��� �Ѵ�...\n\n������ ���� ������ ���� �� ���ΰ�...";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// �簢�� ���� ����
	GetClientRect(m_Hwnd, &rect);
	rect.top = text_y;
	rect.bottom = rect.top + 600;

	// ��Ʈ ����
	myFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// Ÿ��Ʋ �׸���
	DrawText(hdc, text, strlen(text), &rect, DT_CENTER);


	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
	m_Backbit->DeleteBitmapDC(hdc);
}
