#pragma once
#include "Scene.h"

/*
	Ÿ��Ʋ ��
	Ÿ��Ʋ ȭ���� ��� �ִ�
*/
class Scene_Title : public Scene
{
private:
	bool flick = false;
	int title_y = -100;

public:
	Scene_Title(HWND hwnd, Att_BackBit* backbit);
	virtual ~Scene_Title();

	virtual void Initialize();
	virtual bool Run(UINT message, WPARAM wparam, LPARAM lparam);

	void Draw_Screen();
};

