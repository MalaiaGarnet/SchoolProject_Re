#include "ItemTable.h"


// 이름, 설명, 가격, 아이콘, hp, atk, def, dex, agi

int ItemTable::Weapon_Size = 6;
// 무기류
const Data_Item_Weapon ItemTable::Weapons[] = {
	Data_Item_Weapon("키보드", "때리면 더 좋다", 500, 0, 0, 3, 0, 0, 0),
	Data_Item_Weapon("책과 볼펜", "책으로 막고 볼펜으로 찌른다", 500, 0, 0, 2, 0, 1, 0),
	Data_Item_Weapon("랜치", "아프다", 500, 0, 0, 5, 0, -1, 0),
	Data_Item_Weapon("죽음의 검", "닿으면 죽는다", 1000, 0, 0, 10, 0, 0, 4),
	Data_Item_Weapon("브레이브소드", "닿으면 고자가 된다", 1500, 0, 0, 15, 0, 0, 4),
	Data_Item_Weapon("거울", "본 사람은 대부분 죽는다", 2000, 0, 0, 99, 0, 99, 0)
};

int ItemTable::Armor_Size = 6;
// 방어구류
const Data_Item_Armor ItemTable::Armors[] = {
	Data_Item_Armor("후드티", "오버핏은 그만", 300, 0, 0, 0, 3, 0, 0),
	Data_Item_Armor("블라우스", "환상의 옷", 300, 0, 0, 0, 1, 0, 2),
	Data_Item_Armor("멜빵", "은근 소화하기 힘듬", 300, 0, 10, 0, 4, 0, -2),
	Data_Item_Armor("가디건", "나는 못 입는다", 1500, 0, 10, 0, 15, 5, 5),
	Data_Item_Armor("야상", "이쁘다", 1200, 0, 10, 0, 25, 20, -10),
	Data_Item_Armor("군복", "???", 2000, 0, 50, 0, 50, 0, 50)
};

int ItemTable::Accessories_Size = 6;
// 장신구류
const Data_Item_Accessory ItemTable::Accessories[] = {
	Data_Item_Accessory("안경", "안경 별로 안좋아함", 100, 0, 10, 0, 0, 0, 0),
	Data_Item_Accessory("아이패드", "감성패드", 200, 0, 0, 0, 0, 0, 3),
	Data_Item_Accessory("볼트", "맞으면 아프다", 500, 0, 10, 0, 0, 2, 0),
	Data_Item_Accessory("맥북", "사치 최고봉", 10000, 0, 0, 0, 0, 0, 0),
	Data_Item_Accessory("API 책", "두꺼움이 법전 수준", 1500, 0, 0, 9999, 0, 9999, 0),
	Data_Item_Accessory("공학용 계산기", "버튼이 많다", 2500, 0, 1000, 30, 30, 30, 30)
};