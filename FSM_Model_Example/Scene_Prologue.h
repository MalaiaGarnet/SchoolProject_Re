#pragma once
#include "Scene.h"

/*
	프롤로그 씬
	프롤로그 화면을 담당하고 있다
	라고 해도 그냥 스크롤되는 텍스트가 다다
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

