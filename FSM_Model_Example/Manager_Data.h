#pragma once
#include "Global_Info.h"
#include "Template_LinkedList.h"
#include "Data_User.h"
#include "Manager_File.h"

/*
	데이터 매니저
	게임 내 유저 데이터를 관리한다
*/
class Manager_Data
{
private:
	static Manager_Data* instance;

	LinkedList<Data_User*>* m_User_List; // 가공된 유저 리스트
	Data_User* m_Current_User; // 현재 접속중인 유저

	Manager_Data();
	~Manager_Data();
public:
	// 싱글턴 함수
	static Manager_Data* Create_Instance();
	static Manager_Data* Get_Instance();
	static void Release_Instance();

	Data_User* Get_Current_User() { return m_Current_User; }

	void Create_Data(const char* _name, const char* _pass); // 유저 리스트에 새로운 유저를 등록한다
	void Remove_Data(Data_User* _user);
	void Change_User(Data_User* _user);
	Data_User* Search_Data(const char* _name); // 유저 리스트에 해당 유저가 있는지 확인한다
	bool Check_Password(Data_User* _data, const char* _pass); // 유저 데이터의 비밀번호가 맞는지 확인한다

	void Load_All_Datas();		// 파일 매니저를 통해 유저 데이터를 읽어온다
	void Save_All_Datas();		// 파일 매니저에게 유저 데이터를 저장시킨다
};

