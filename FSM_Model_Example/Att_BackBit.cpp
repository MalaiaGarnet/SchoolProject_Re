#include "Att_BackBit.h"

#include <iostream>
using namespace std;

Att_BackBit::Att_BackBit(HWND _hwnd, int _height, int _width)
{
	m_hWnd = _hwnd;
	m_Height = _height;
	m_Width = _width;

	HDC hdc = GetDC(_hwnd);
	m_hBitmap = CreateCompatibleBitmap(hdc, _width, _height);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBit = (HBITMAP)SelectObject(hMemDC, m_hBitmap);
	PatBlt(hMemDC, 0, 0, _width, _height, WHITENESS);
	SelectObject(hMemDC, hOldBit);
	DeleteDC(hMemDC);
	ReleaseDC(_hwnd, hdc);
}

Att_BackBit::~Att_BackBit()
{
	DeleteObject(m_hBitmap);
}

bool Att_BackBit::SetHeight(int _height)
{
	BITMAP bit;
	GetObject(m_hBitmap, sizeof(BITMAP), &bit);

	int y = bit.bmHeight;

	if (_height< 0 || _height> y)
	{
		return false;
	}

	m_Height = _height;
	return true;
}

bool Att_BackBit::SetWidth(int _width)
{
	BITMAP bit;
	GetObject(m_hBitmap, sizeof(BITMAP), &bit);
	int x = bit.bmWidth;

	if (_width< 0 || _width> x)
	{
		return false;
	}

	m_Width = _width;
	return true;
}

const HDC Att_BackBit::GetBitmapDC()
{
	HDC hdc = GetDC(m_hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBit = (HBITMAP)SelectObject(hMemDC, m_hBitmap);
	ReleaseDC(m_hWnd, hdc);
	return hMemDC;
}

void Att_BackBit::DeleteBitmapDC(HDC _hDc)
{
	DeleteDC(_hDc);
}

void Att_BackBit::ScreenDraw(HDC _hDc, int _x, int _y)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(_hDc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(_hDc, _x, _y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void Att_BackBit::BitmapDraw(int _x, int _y, HBITMAP _hBit)
{
	HDC MemDC1, MemDC2, hdc;
	HBITMAP OldBitmap1, OldBitmap2;
	int bx, by;
	BITMAP bit;

	hdc = GetDC(m_hWnd);
	MemDC1 = CreateCompatibleDC(hdc);
	MemDC2 = CreateCompatibleDC(hdc);

	OldBitmap1 = (HBITMAP)SelectObject(MemDC1, m_hBitmap);

	GetObject(_hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	OldBitmap2 = (HBITMAP)SelectObject(MemDC2, _hBit);
	BitBlt(MemDC1, _x, _y, bx, by, MemDC2, 0, 0, SRCCOPY);

	SelectObject(MemDC1, OldBitmap1);
	SelectObject(MemDC2, OldBitmap2);
	DeleteDC(MemDC1);
	DeleteDC(MemDC2);
}

void Att_BackBit::ClearBitMap()
{
	HDC hdc = GetDC(m_hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hOldBit = (HBITMAP)SelectObject(hMemDC, m_hBitmap);
	PatBlt(hMemDC, 0, 0, m_Width, m_Height, WHITENESS);
	SelectObject(hMemDC, hOldBit);
	DeleteDC(hMemDC);
	ReleaseDC(m_hWnd, hdc);
}