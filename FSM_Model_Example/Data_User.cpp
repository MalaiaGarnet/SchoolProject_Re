#include "Data_User.h"


Data_User::Data_User(const char* _id, const char* _pass)
{
	strcpy_s(m_Id, STRING_SIZE, _id);
	strcpy_s(m_Password, STRING_SIZE, _pass);
	m_Prologue = false;
	m_Character_List = new LinkedList<Data_Character*>();
	m_Current_Character = nullptr;
}

Data_User::~Data_User()
{
}

Data_Character* Data_User::Get_Character(int index)
{
	if (index < 0) return nullptr;

	ListNode<Data_Character*>* node = m_Character_List->Get_Head();

	for (int i = 0; i <= index; i++)
	{
		node = node->m_Next;
		if (node == nullptr)
			return nullptr;
	}
	return node->m_Data;
}


void Data_User::Set_Character_List(LinkedList<Data_Character*>* _list)
{
	if (m_Character_List != nullptr)
		delete m_Character_List;

	m_Character_List = _list;
}


void Data_User::Add_Character(Data_Character* _chara)
{
	if (m_Character_List->Insert(_chara))
		cout << "chara create success" << endl;
	else
		cout << "chara create failed" << endl;
}

void Data_User::Remove_Character(Data_Character* _chara)
{
	if (m_Character_List->Delete(_chara))
		cout << "chara delete success" << endl;
	else
		cout << "chara delete failed" << endl;
}

void Data_User::Change_Current_Character(int _index)
{
	m_Current_Character = Get_Character(_index);
}
