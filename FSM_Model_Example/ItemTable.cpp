#include "ItemTable.h"


// �̸�, ����, ����, ������, hp, atk, def, dex, agi

int ItemTable::Weapon_Size = 6;
// �����
const Data_Item_Weapon ItemTable::Weapons[] = {
	Data_Item_Weapon("Ű����", "������ �� ����", 500, 0, 0, 3, 0, 0, 0),
	Data_Item_Weapon("å�� ����", "å���� ���� �������� ���", 500, 0, 0, 2, 0, 1, 0),
	Data_Item_Weapon("��ġ", "������", 500, 0, 0, 5, 0, -1, 0),
	Data_Item_Weapon("������ ��", "������ �״´�", 1000, 0, 0, 10, 0, 0, 4),
	Data_Item_Weapon("�극�̺�ҵ�", "������ ���ڰ� �ȴ�", 1500, 0, 0, 15, 0, 0, 4),
	Data_Item_Weapon("�ſ�", "�� ����� ��κ� �״´�", 2000, 0, 0, 99, 0, 99, 0)
};

int ItemTable::Armor_Size = 6;
// ����
const Data_Item_Armor ItemTable::Armors[] = {
	Data_Item_Armor("�ĵ�Ƽ", "�������� �׸�", 300, 0, 0, 0, 3, 0, 0),
	Data_Item_Armor("���콺", "ȯ���� ��", 300, 0, 0, 0, 1, 0, 2),
	Data_Item_Armor("�ủ", "���� ��ȭ�ϱ� ����", 300, 0, 10, 0, 4, 0, -2),
	Data_Item_Armor("�����", "���� �� �Դ´�", 1500, 0, 10, 0, 15, 5, 5),
	Data_Item_Armor("�߻�", "�̻ڴ�", 1200, 0, 10, 0, 25, 20, -10),
	Data_Item_Armor("����", "???", 2000, 0, 50, 0, 50, 0, 50)
};

int ItemTable::Accessories_Size = 6;
// ��ű���
const Data_Item_Accessory ItemTable::Accessories[] = {
	Data_Item_Accessory("�Ȱ�", "�Ȱ� ���� ��������", 100, 0, 10, 0, 0, 0, 0),
	Data_Item_Accessory("�����е�", "�����е�", 200, 0, 0, 0, 0, 0, 3),
	Data_Item_Accessory("��Ʈ", "������ ������", 500, 0, 10, 0, 0, 2, 0),
	Data_Item_Accessory("�ƺ�", "��ġ �ְ��", 10000, 0, 0, 0, 0, 0, 0),
	Data_Item_Accessory("API å", "�β����� ���� ����", 1500, 0, 0, 9999, 0, 9999, 0),
	Data_Item_Accessory("���п� ����", "��ư�� ����", 2500, 0, 1000, 30, 30, 30, 30)
};