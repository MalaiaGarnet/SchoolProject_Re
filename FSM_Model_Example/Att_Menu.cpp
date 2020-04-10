#include "Att_Menu.h"

Att_Menu::Att_Menu(int _index)
{
	m_MenuIndex = _index;
	m_DrawType = DRAW_TYPE::NONE;
}


Att_Menu::~Att_Menu()
{
}

void Att_Menu::Process(WPARAM _wparam)
{
	switch (LOWORD(_wparam))
	{
	case ID_MENU_FREELINE: // ������
		m_DrawType = DRAW_TYPE::FREELINE;
		break;
	case ID_MENU_LINE: // ����
		m_DrawType = DRAW_TYPE::LINE;
		break;
	case ID_MENU_SQUARE: // �簢��
		m_DrawType = DRAW_TYPE::SQUARE;
		break;
	case ID_MENU_CIRCLE: // ��
		m_DrawType = DRAW_TYPE::CIRCLE;
		break;
	case ID_MENU_EXIT: // ������
		PostQuitMessage(0);
		break;
	}
}
