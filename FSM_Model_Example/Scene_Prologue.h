#pragma once
#include "Scene.h"

/*
	���ѷα� ��
	���ѷα� ȭ���� ����ϰ� �ִ�
	��� �ص� �׳� ��ũ�ѵǴ� �ؽ�Ʈ�� �ٴ�
*/
class Scene_Prologue : public Scene
{
private:
	int text_y;

public:
	Scene_Prologue(HWND hwnd, Att_BackBit* backbit) : Scene(hwnd, backbit) {}
	virtual ~Scene_Prologue() {}

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen();
};

