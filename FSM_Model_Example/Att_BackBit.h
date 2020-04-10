#pragma once
#include <Windows.h>

/*
	DC ���� ������ Ŭ����
	�׸� ������ ����Ѵ�
	Window_Main�� �ڽ� �����찡 ��������� �������� ���������
*/
class Att_BackBit
{
private:
	HBITMAP m_hBitmap;		// �ڷᰡ ����Ǵ� ��Ʈ��
	HWND m_hWnd;				// ��Ʈ���� �׷����� ������
	int m_Height;					// ��Ʈ���� ����
	int m_Width;					// ��Ʈ���� �ʺ�

public:
	Att_BackBit(HWND _hwnd, int _height, int _width);
	~Att_BackBit();

	bool SetHeight(int _height);
	bool SetWidth(int _width);
	void SetBitmap(HBITMAP _hBit)
	{ m_hBitmap = _hBit; }
	void SethWnd(HWND _hWnd)
	{ m_hWnd = _hWnd; }

	const HBITMAP Get_BitMap() 
	{ return m_hBitmap; }
	const HWND Get_hWnd()
	{ return m_hWnd; }
	const int Get_Height()
	{ return m_Height; }
	const int Get_Width()
	{ return m_Width; }

	const HDC GetBitmapDC();
	void DeleteBitmapDC(HDC _hDc);

	void ScreenDraw(HDC _hDc, int _x, int _y);
	void BitmapDraw(int _x, int _y, HBITMAP _hBit);
	void ClearBitMap();
};

