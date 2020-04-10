#include <iostream>
#include "API_Window_Main.h"

using namespace std;


/*
	유저의 가입 & 로그인 & 로그아웃 & 탈퇴
	(이 때 정보는 실제 파일을 다루는 것으로, C던 API던 함수는 관계 없을 무)
	로그인 상태에서 유저는 캐릭터 생성이 가능, 이 과정에서 종족을 선택, 종족에 따라 기본으로 주는 아이템이 다름
	이후 아이템 구매와 착용 화면으로 넘어감
	그 뒤 주어진 게임머니로 여러 아이템을 구매해 캐릭터의 여러 능력치를 세팅할 수 있음
	아이템은 몇 가지 카테고리로 분류해서 처리(무기, 방어구, 장신구, 등등)
	캐릭터 선택, 아이템 장착까지 끝났으면 장착된 아이템에 따라 능력치를 확인할 수 있는 화면을 구성
*/

int main()
{
	// 윈도우 생성
	API_Window_Main* window = API_Window_Main::Create_Instance();

	cout << "create window..." << endl;
	window->Initialize();	// 메인 윈도우 초기화
	window->Run();			// 메인 윈도우 기동
	cout << "close window..." << endl;

	// 윈도우를 제거
	API_Window_Main::Release_Instance();
	system("pause");
	return 0;
}