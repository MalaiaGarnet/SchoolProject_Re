#pragma once
#include "Global_Info.h"
#include "Template_LinkedList.h"
#include "Data_User.h"
#include "Manager_File.h"

/*
	������ �Ŵ���
	���� �� ���� �����͸� �����Ѵ�
*/
class Manager_Data
{
private:
	static Manager_Data* instance;

	LinkedList<Data_User*>* m_User_List; // ������ ���� ����Ʈ
	Data_User* m_Current_User; // ���� �������� ����

	Manager_Data();
	~Manager_Data();
public:
	// �̱��� �Լ�
	static Manager_Data* Create_Instance();
	static Manager_Data* Get_Instance();
	static void Release_Instance();

	Data_User* Get_Current_User() { return m_Current_User; }

	void Create_Data(const char* _name, const char* _pass); // ���� ����Ʈ�� ���ο� ������ ����Ѵ�
	void Remove_Data(Data_User* _user);
	void Change_User(Data_User* _user);
	Data_User* Search_Data(const char* _name); // ���� ����Ʈ�� �ش� ������ �ִ��� Ȯ���Ѵ�
	bool Check_Password(Data_User* _data, const char* _pass); // ���� �������� ��й�ȣ�� �´��� Ȯ���Ѵ�

	void Load_All_Datas();		// ���� �Ŵ����� ���� ���� �����͸� �о�´�
	void Save_All_Datas();		// ���� �Ŵ������� ���� �����͸� �����Ų��
};

