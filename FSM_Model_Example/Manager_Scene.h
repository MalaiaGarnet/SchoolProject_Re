#pragma once
#include "Scene.h"

/*
	씬 매니저
	게임 내 씬을 관리한다
*/
class Manager_Scene
{
private:
	static Manager_Scene* instance;

	Scene* m_Current_Scene;

	Manager_Scene();
	~Manager_Scene();
public:
	// 싱글턴 함수
	static Manager_Scene* Create_Instance();
	static Manager_Scene* Get_Instance();
	static void Release_Instance();

	void Change_Scene(Scene* _scene);
	void Run(UINT message, WPARAM wparam, LPARAM lparam);
};

