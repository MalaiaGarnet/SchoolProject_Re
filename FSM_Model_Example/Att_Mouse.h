#pragma once
#include <Windows.h>

enum CLICK_STATE { UP = 0, DOWN };

/*
	���콺 ������ Ŭ����
	���콺�� ������ ����Ѵ�
	Window_Main�� ��������� �������� ���� ���������
*/
class Att_Mouse
{
private:
	static Att_Mouse* instance;

	POINT m_CurrentCoord;	// ���콺�� ����� ��ǥ
	POINT m_BeforeCoord;	// ���콺�� ����� ��ǥ(���� ��)
	CLICK_STATE m_Left_ClickState;	// ��Ŭ�� ����
	CLICK_STATE m_Right_ClickState;	// ��Ŭ�� ����

	Att_Mouse();
	~Att_Mouse();
public:
	// �̱��� �Լ�
	static Att_Mouse* Create_Instance();
	static Att_Mouse* Get_Instance();
	static void Release_Instance();

	// Get
	// �� HWND ���� ������ ������ ��ǥ�� ���
	POINT Get_CurrentCoord(HWND _hWnd);		// ���콺�� ����� ��ǥ�� ���
	POINT Get_BeforeCoord(HWND _hWnd);		// ���콺�� ����� ��ǥ(���� ��)�� ���
	CLICK_STATE Get_Left_ClickState();				// ���콺�� ���� Ŭ�� ���¸� ���
	CLICK_STATE Get_Right_ClickState();			// ���콺�� ������ Ŭ�� ���¸� ���

	// Set
	// �� HWND ���� ������ ��ǥ�� ������ ��ǥ�� ����
	void Set_Coord(POINT _coord, HWND _hWnd);			// ���콺�� ����� ��ǥ�� ����
	void Set_Left_ClickState(CLICK_STATE _state);			// ���콺�� ���� Ŭ�� ���¸� ����
	void Set_Right_ClickState(CLICK_STATE _state);			// ���콺�� ������ Ŭ�� ���¸� ����
};

