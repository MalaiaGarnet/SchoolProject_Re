#include "Manager_Data.h"

// �̱���
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

// ���� ������ ���
Data_User* Manager_Data::Search_Data(const char* _name)
{
	// ����Ʈ�� �Ӹ��� ���� ������ ����, ��尡 nullptr�� �ɶ����� ���� ������ ���ư��鼭 �ݺ�
	for (ListNode<Data_User*>* node = m_User_List->Get_Head()->m_Next; node != nullptr; node = node->m_Next)
	{
		// ����� �������� ���̵�� �Է��� ���̵� ���ٸ� �����͸� ��ȯ
		if (!strcmp(node->m_Data->Get_ID(), _name))
			return node->m_Data;
	}
	// �ƹ��͵� �� ã������ nullptr ��ȯ
	return nullptr;
}

// ���� �����Ϳ� ��й�ȣ ��
bool Manager_Data::Check_Password(Data_User* _data, const char* _pass)
{
	return !strcmp(_data->Get_Password(), _pass);
}

void Manager_Data::Load_All_Datas()
{
	cout << "load datas..." << endl;

	// ���� ����Ʈ�� ����� ���� �ҷ��´�
	if(m_User_List != nullptr)
		delete m_User_List;
	m_User_List = Manager_File::Get_Instance()->Load_Data();

	// ���� ������ �����
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

	// ���� ������ �����
	ListNode<Data_User*>* node = m_User_List->Get_Head()->m_Next;
	cout << "user count : " << m_User_List->Size() << endl;
	for (int i = 0; i < m_User_List->Size(); i++)
	{
		cout << "  name : " << node->m_Data->Get_ID() << endl;
		node = node->m_Next;
	}

	// ���� ������ ����
	Manager_File::Get_Instance()->Save_Data(m_User_List);

	cout << "saved." << endl;
}