#pragma once
#include "Global_Info.h"
#include "Template_LinkedList.h"
#include "Data_Character.h"
#include "Data_Item_Weapon.h"
#include "Data_Item_Armor.h"
#include "Data_Item_Accessory.h"

class Data_User
{
private:
	char m_Id[256];
	char m_Password[256];
	bool m_Prologue; // 프롤로그 봤는지 여부

	Data_Character* m_Current_Character;
	
	LinkedList<Data_Character*>* m_Character_List;

public:
	Data_User(const char* _id, const char* _pass);
	~Data_User();

	// Get
	const char* Get_ID() { return m_Id; }
	const char* Get_Password() { return m_Password; }
	bool Get_Prologue() { return m_Prologue; }
	Data_Character* Get_Current_Character() { return m_Current_Character; }
	int Get_Character_Size() { return m_Character_List->Size(); }
	Data_Character* Get_Character(int index);

	// Set
	void Set_Prologue(bool _active) { m_Prologue = _active; }
	void Set_Character_List(LinkedList<Data_Character*>* _list);

	// 파일 저장용 버퍼 Get
	bool* Get_Prologue_Buffer() { return &m_Prologue; }

	// 함수
	void Add_Character(Data_Character* _chara);
	void Remove_Character(Data_Character* _chara);
	void Change_Current_Character(int _index);
};