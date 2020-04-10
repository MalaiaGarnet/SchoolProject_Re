#pragma once
#include "Data_User.h"
#include "Template_LinkedList.h"

/*
	���� �Ŵ���
	�ܺο��� ������ �а�, ����
*/
class Manager_File
{
private:
	static Manager_File* instance;

	Manager_File();
	~Manager_File();
public:
	// �̱��� �Լ�
	static Manager_File* Create_Instance();
	static Manager_File* Get_Instance();
	static void Release_Instance();

	LinkedList<Data_User*>* Load_Data();
	void Save_Data(LinkedList<Data_User*>* _user_list);

	void Write_Weapon(Data_Item_Weapon* weapon, FILE* fp);
	void Write_Armor(Data_Item_Armor* armor, FILE* fp);
	void Write_Accessory(Data_Item_Accessory* accessory, FILE* fp);

	Data_Item_Weapon* Read_Weapon(FILE* fp);
	Data_Item_Armor* Read_Armor(FILE* fp);
	Data_Item_Accessory* Read_Accessory(FILE* fp);
};

