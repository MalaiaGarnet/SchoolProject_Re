#include "Global_Info.h"

/*
	캐릭터, 아이템 타입의 열거형
*/
// TYPE_CHARA
const char* Global_Info::Race_Type_Name[] = { "컴순이", "문순이", "공순이" };
const char* Global_Info::Race_Type_Desc[] = { 
	"컴순이 종족은\n엄마 뱃속에서 자료구조를 배우면서 태어납니다.\n그들은 컴퓨터 과학만을 위해 존재하며,\n만약 컴퓨터가 사라진다면 그들도 사라질 것입니다.",
	"문순이 종족은 그냥 문과입니다.\n태생이 슬픈 그들은 대부분 철학을 배우며,\n그것을 토대로...... 그냥 삽니다.",
	"공순이 종족은 공순이입니다.\n매우 희귀하게 발견되는 이 종족은,\n힘든 일을 마다하지 않으며\n항상 주머니에 랜치를 지니고 다닙니다."
};

// 문자열 배열의 크기를 반환하는 함수
const int Global_Info::Type_Size(TYPE_COUNT type)
{
	switch (type)
	{
	// 종족 타입
	case TYPE_COUNT::RACE_COUNT:
		return sizeof(Race_Type_Name) / sizeof(char*);
	}
	return 0;
}