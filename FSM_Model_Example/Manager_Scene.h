#pragma once
#include "Scene.h"

/*
	�� �Ŵ���
	���� �� ���� �����Ѵ�
*/
class Manager_Scene
{
private:
	static Manager_Scene* instance;

	Scene* m_Current_Scene;

	Manager_Scene();
	~Manager_Scene();
public:
	// �̱��� �Լ�
	static Manager_Scene* Create_Instance();
	static Manager_Scene* Get_Instance();
	static void Release_Instance();

	void Change_Scene(Scene* _scene);
	void Run(UINT message, WPARAM wparam, LPARAM lparam);
};

