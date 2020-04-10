#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;

#define STRING_SIZE 64
#define CHARACTER_SLOT 3
#define TITLE_TOP 35

// 차일드 윈도우
// 로그인 씬
#define S_LOGIN_BUTTON 400
#define S_REGISTER_BUTTON 401
// 로비 씬
#define S_CREATE_CHARA_BUTTON 402
#define S_LOGOUT_BUTTON 403
#define S_UNREGISTER_BUTTON 404
#define S_CHARA_NEXT_BUTTON 405
#define S_CHARA_PREV_BUTTON 406
#define S_CHARA_PLAY_BUTTON 407
#define S_CHARA_REMOVE_BUTTON 408
// 캐릭터 생성 씬
#define S_CC_CANCEL_BUTTON 409
#define S_CC_CREATE_BUTTON 410
#define S_CC_NEXT_BUTTON 411
#define S_CC_PREV_BUTTON 412
// 캐릭터 로비 씬
#define S_CL_BATTLE_BUTTON 413
#define S_CL_SHOP_BUTTON 414
#define S_CL_EQUIP_BUTTON 415
#define S_CL_PREV_BUTTON 416
// 상점 씬
#define S_S_PREV_BUTTON 418
#define S_S_WEAPON_BUTTON 419
#define S_S_ARMOR_BUTTON 420
#define S_S_ACCESSORY_BUTTON 421
#define S_S_BUY_BUTTON 422
#define S_S_SELL_BUTTON 423
#define S_S_EQUIP_BUTTON 424
// 장비 씬
#define S_CE_PREV_BUTTON 417
#define S_CE_SHOP_BUTTON 425
#define S_CE_WEAPON_BUTTON 426
#define S_CE_ARMOR_BUTTON 427
#define S_CE_ACCESSORY_BUTTON 428
#define S_CE_EQUIP_BUTTON 429

// 에디트
#define S_ID_EDIT 701
#define S_PASS_EDIT 702
#define S_CC_NAME_EDIT 703

// 리스트
#define S_S_SELL_LIST 801
#define S_S_BUY_LIST 802
#define S_CE_ITEM_LIST 803

/*
	캐릭터, 직업, 아이템 타입의 열거형
*/
// 캐릭터 타입
enum TYPE_RACE { COMSOON = 0, MOONSOON, GONGSOON };

//	타입들의 배열 갯수를 알아내는 데 쓰이는 열거형
enum TYPE_COUNT { RACE_COUNT, CLASS_COUNT, ITEM_COUNT, HUMAN_HAIR, ELF_EAR, ORC_SKIN, MATERIAL_QUALITY };

class Global_Info
{
public:
	/*
		열거형을 문자열로 치환한 것
	*/
	static const char* Race_Type_Name[]; // TYPE_CHARA, 이름
	static const char* Race_Type_Desc[];  // TYPE_CHARA, 설명

	/*
		클래스 단위 함수
	*/
	static const int Type_Size(TYPE_COUNT type);			// 문자열 배열들이 가진 배열의 크기를 알아낸다
};