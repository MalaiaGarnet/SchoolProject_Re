#pragma once
#include <Windows.h>

/*
	DC 버퍼 데이터 클래스
	그림 정보를 담당한다
	Window_Main의 자식 윈도우가 만들어지는 시점에서 만들어진다
*/
class Att_BackBit
{
private:
	HBITMAP m_hBitmap;		// 자료가 저장되는 비트맵
	HWND m_hWnd;				// 비트맵이 그려지는 윈도우
	int m_Height;					// 비트맵의 높이
	int m_Width;					// 비트맵의 너비

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

