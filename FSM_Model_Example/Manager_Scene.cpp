#include "Manager_Scene.h"


// �̱���
#pragma region SINGLETONE

Manager_Scene* Manager_Scene::instance = nullptr;

Manager_Scene* Manager_Scene::Create_Instance()
{
	if (instance == nullptr)
		instance = new Manager_Scene();
	return instance;
}

Manager_Scene* Manager_Scene::Get_Instance()
{
	return instance;
}

void Manager_Scene::Release_Instance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

#pragma endregion


Manager_Scene::Manager_Scene()
{
	m_Current_Scene = nullptr;
}


Manager_Scene::~Manager_Scene()
{
}

void Manager_Scene::Change_Scene(Scene* _scene)
{
	if(m_Current_Scene != nullptr)
		delete m_Current_Scene; // ���� ���� ����������
	m_Current_Scene = _scene;
	m_Current_Scene->Initialize(); // ���� �ʱ�ȭ
}

void Manager_Scene::Run(UINT message, WPARAM wparam, LPARAM lparam)
{
	if(m_Current_Scene != nullptr)
		m_Current_Scene->Run(message, wparam, lparam);
}
