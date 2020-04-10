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
	// Ÿ�̸�
	case WM_TIMER:
		switch (wparam)
		{
		case 1: // Ÿ��Ʋ�� �������� Ÿ�̸�
			title_y += 2;
			InvalidateRect(m_Hwnd, NULL, FALSE);

			// Ÿ��Ʋ�� ���� ��ġ���� �����ߴٸ�
			if (title_y > 100)
			{
				KillTimer(m_Hwnd, 1); // Ÿ�̸� ����
				SetTimer(m_Hwnd, 2, 750, NULL);
			}

			break;
		case 2: // ���� ������
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

	// �׸���
	case WM_PAINT:
		// ������ ����
		Draw_Screen();
		// ������ ����
		break;
	}
	return false;
}

void Scene_Title::Draw_Screen()
{
	HDC hdc;
	RECT rect;

	HFONT myFont, oldFont;
	TCHAR title_text[20] = "�������� ����";
	TCHAR desc_text[30] = "��-Ÿ-Ű�� ������ �����ϱ�";

	m_Backbit->ClearBitMap();
	hdc = m_Backbit->GetBitmapDC();

	// �簢�� ���� ����
	GetClientRect(m_Hwnd, &rect);
	rect.top = title_y;
	rect.bottom = 200;

	// ��Ʈ ����
	myFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	// Ÿ��Ʋ �׸���
	DrawText(hdc, title_text, strlen(title_text), &rect, DT_CENTER);

	if (flick)
	{
		// �簢�� ���� ����
		GetClientRect(m_Hwnd, &rect);
		rect.top = rect.bottom - 200;
		rect.bottom = rect.top + 100;

		// ��Ʈ ����
		myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "�ü�");
		oldFont = (HFONT)SelectObject(hdc, myFont);

		// ���� �׸���
		DrawText(hdc, desc_text, strlen(desc_text), &rect, DT_CENTER);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
	m_Backbit->DeleteBitmapDC(hdc);
}
