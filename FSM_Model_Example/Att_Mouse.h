#pragma once
#include <Windows.h>

enum CLICK_STATE { UP = 0, DOWN };

/*
	마우스 데이터 클래스
	마우스의 정보를 담당한다
	Window_Main이 만들어지는 시점에서 같이 만들어진다
*/
class Att_Mouse
{
private:
	static Att_Mouse* instance;

	POINT m_CurrentCoord;	// 마우스의 모니터 좌표
	POINT m_BeforeCoord;	// 마우스의 모니터 좌표(였던 것)
	CLICK_STATE m_Left_ClickState;	// 좌클릭 상태
	CLICK_STATE m_Right_ClickState;	// 우클릭 상태

	Att_Mouse();
	~Att_Mouse();
public:
	// 싱글턴 함수
	static Att_Mouse* Create_Instance();
	static Att_Mouse* Get_Instance();
	static void Release_Instance();

	// Get
	// ※ HWND 값을 넣으면 윈도우 좌표를 취득
	POINT Get_CurrentCoord(HWND _hWnd);		// 마우스의 모니터 좌표를 취득
	POINT Get_BeforeCoord(HWND _hWnd);		// 마우스의 모니터 좌표(였던 것)를 취득
	CLICK_STATE Get_Left_ClickState();				// 마우스의 왼쪽 클릭 상태를 취득
	CLICK_STATE Get_Right_ClickState();			// 마우스의 오른쪽 클릭 상태를 취득

	// Set
	// ※ HWND 값을 넣으면 좌표에 윈도우 좌표를 더함
	void Set_Coord(POINT _coord, HWND _hWnd);			// 마우스의 모니터 좌표를 수정
	void Set_Left_ClickState(CLICK_STATE _state);			// 마우스의 왼쪽 클릭 상태를 수정
	void Set_Right_ClickState(CLICK_STATE _state);			// 마우스의 오른쪽 클릭 상태를 수정
};

