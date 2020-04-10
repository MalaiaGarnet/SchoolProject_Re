#include "Manager_Data.h"

// 싱글턴
#pragma region SINGLETONE

Manager_Data* Manager_Data::instance = nullptr;

Manager_Data* Manager_Data::Create_Instance()
{
	if (instance == nullptr)
		instance = new Manager_Data();
	return instance;
}

Manager_Data* Manager_Data::Get_Instance()
{
	return instance;
}

void Manager_Data::Release_Instance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

#pragma endregion


Manager_Data::Manager_Data()
{
	m_User_List = new LinkedList<Data_User*>();
}


Manager_Data::~Manager_Data()
{
}

void Manager_Data::Create_Data(const char* _name, const char* _pass)
{
	Data_User* data = new Data_User(_name, _pass);
	m_User_List->Insert(data);
	cout << "User Created: " << _name << " // " << _pass << endl;
	cout << "Now ListSize : " << m_User_List->Size() << endl;
}

void Manager_Data::Remove_Data(Data_User* _user)
{
	if(m_User_List->Delete(_user))
		cout << "User Removed" << endl;
}

void Manager_Data::Change_User(Data_User* _user)
{
	m_Current_User = _user;
}

// 유저 데이터 취득
Data_User* Manager_Data::Search_Data(const char* _name)
{
	// 리스트의 머리의 다음 노드부터 시작, 노드가 nullptr이 될때까지 다음 것으로 나아가면서 반복
	for (ListNode<Data_User*>* node = m_User_List->Get_Head()->m_Next; node != nullptr; node = node->m_Next)
	{
		// 노드의 데이터의 아이디와 입력한 아이디가 같다면 데이터를 반환
		if (!strcmp(node->m_Data->Get_ID(), _name))
			return node->m_Data;
	}
	// 아무것도 못 찾았으면 nullptr 반환
	return nullptr;
}

// 유저 데이터와 비밀번호 비교
bool Manager_Data::Check_Password(Data_User* _data, const char* _pass)
{
	return !strcmp(_data->Get_Password(), _pass);
}

void Manager_Data::Load_All_Datas()
{
	cout << "load datas..." << endl;

	// 기존 리스트를 지우고 새로 불러온다
	if(m_User_List != nullptr)
		delete m_User_List;
	m_User_List = Manager_File::Get_Instance()->Load_Data();

	// 유저 데이터 디버그
	ListNode<Data_User*>* node = m_User_List->Get_Head()->m_Next;
	cout << "user count : " << m_User_List->Size() << endl;
	for (int i = 0; i < m_User_List->Size(); i++)
	{
		cout << "  name : " << node->m_Data->Get_ID() << endl;
		node = node->m_Next;
	}

	cout << "loaded." << endl;
}

void Manager_Data::Save_All_Datas()
{
	cout << "save datas..." << endl;

	// 유저 데이터 디버그
	ListNode<Data_User*>* node = m_User_List->Get_Head()->m_Next;
	cout << "user count : " << m_User_List->Size() << endl;
	for (int i = 0; i < m_User_List->Size(); i++)
	{
		cout << "  name : " << node->m_Data->Get_ID() << endl;
		node = node->m_Next;
	}

	// 유저 데이터 저장
	Manager_File::Get_Instance()->Save_Data(m_User_List);

	cout << "saved." << endl;
}