#include "Global_Info.h"

/*
	ĳ����, ������ Ÿ���� ������
*/
// TYPE_CHARA
const char* Global_Info::Race_Type_Name[] = { "�ļ���", "������", "������" };
const char* Global_Info::Race_Type_Desc[] = { 
	"�ļ��� ������\n���� ��ӿ��� �ڷᱸ���� ���鼭 �¾�ϴ�.\n�׵��� ��ǻ�� ���и��� ���� �����ϸ�,\n���� ��ǻ�Ͱ� ������ٸ� �׵鵵 ����� ���Դϴ�.",
	"������ ������ �׳� �����Դϴ�.\n�»��� ���� �׵��� ��κ� ö���� ����,\n�װ��� ����...... �׳� ��ϴ�.",
	"������ ������ �������Դϴ�.\n�ſ� ����ϰ� �߰ߵǴ� �� ������,\n���� ���� �������� ������\n�׻� �ָӴϿ� ��ġ�� ���ϰ� �ٴմϴ�."
};

// ���ڿ� �迭�� ũ�⸦ ��ȯ�ϴ� �Լ�
const int Global_Info::Type_Size(TYPE_COUNT type)
{
	switch (type)
	{
	// ���� Ÿ��
	case TYPE_COUNT::RACE_COUNT:
		return sizeof(Race_Type_Name) / sizeof(char*);
	}
	return 0;
}