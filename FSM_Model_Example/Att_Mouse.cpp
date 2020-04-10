#include <iostream>
#include "Att_Mouse.h"

using namespace std;

Att_Mouse::Att_Mouse()
{
	m_CurrentCoord = { 0, 0 };
	m_BeforeCoord = { 0, 0 };
	m_Left_ClickState = CLICK_STATE::UP;
	m_Right_ClickState = CLICK_STATE::UP;
}

Att_Mouse::~Att_Mouse()
{
}

// 싱글턴
#pragma region SINGLETONE

Att_Mouse* Att_Mouse::instance = nullptr;

Att_Mouse* Att_Mouse::Create_Instance()
{
	if (instance == nullptr)
		instance = new Att_Mouse();
	return instance;
}

Att_Mouse* Att_Mouse::Get_Instance()
{
	return instance;
}

void Att_Mouse::Release_Instance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

#pragma endregion

POINT Att_Mouse::Get_CurrentCoord(HWND _hWnd = NULL)
{
	POINT point = m_CurrentCoord;

	// hWnd값을 받았다면 마우스 좌표에서 윈도우 좌표를 뺀다
	RECT rect = {0, 0, 0, 0};
	if (_hWnd != NULL)
		GetWindowRect(_hWnd, &rect);
	point.x -= rect.left;
	point.y -= rect.top;

	return point;
}

POINT Att_Mouse::Get_BeforeCoord(HWND _hWnd = NULL)
{
	POINT point = m_BeforeCoord;

	// hWnd값을 받았다면 마우스 좌표에서 윈도우 좌표를 뺀다
	RECT rect = { 0, 0, 0, 0 };
	if (_hWnd != NULL)
		GetWindowRect(_hWnd, &rect);
	point.x -= rect.left;
	point.y -= rect.top;

	return point;
}

CLICK_STATE Att_Mouse::Get_Left_ClickState()
{
	return m_Left_ClickState;
}

CLICK_STATE Att_Mouse::Get_Right_ClickState()
{
	return m_Right_ClickState;
}

void Att_Mouse::Set_Coord(POINT _coord, HWND _hWnd = NULL)
{
	POINT point = _coord;

	// hWnd 값을 받았다면 윈도우 좌표를 더한다
	RECT rect = { 0, 0, 0, 0 };
	if (_hWnd != NULL)
		GetWindowRect(_hWnd, &rect);
	point.x += rect.left;
	point.y += rect.top;

	// 좌표 변경
	m_BeforeCoord = m_CurrentCoord;
	m_CurrentCoord = point;
}

void Att_Mouse::Set_Left_ClickState(CLICK_STATE _state)
{
	if (_state == CLICK_STATE::DOWN)
	{
		Set_Coord(m_CurrentCoord);
		// cout << "mouse left click = down" << endl;
	}
	else
	{
		// cout << "mouse left click = up" << endl;
	}

	m_Left_ClickState = _state;
}

void Att_Mouse::Set_Right_ClickState(CLICK_STATE _state)
{
	if (_state == CLICK_STATE::DOWN)
	{
		Set_Coord(m_CurrentCoord);
		// cout << "mouse right click = down" << endl;
	}
	else
	{
		// cout << "mouse right click = up" << endl;
	}

	m_Right_ClickState = _state;
}
