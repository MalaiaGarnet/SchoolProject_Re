#include <iostream>
#include "API_Window_Main.h"

using namespace std;


/*
	������ ���� & �α��� & �α׾ƿ� & Ż��
	(�� �� ������ ���� ������ �ٷ�� ������, C�� API�� �Լ��� ���� ���� ��)
	�α��� ���¿��� ������ ĳ���� ������ ����, �� �������� ������ ����, ������ ���� �⺻���� �ִ� �������� �ٸ�
	���� ������ ���ſ� ���� ȭ������ �Ѿ
	�� �� �־��� ���ӸӴϷ� ���� �������� ������ ĳ������ ���� �ɷ�ġ�� ������ �� ����
	�������� �� ���� ī�װ��� �з��ؼ� ó��(����, ��, ��ű�, ���)
	ĳ���� ����, ������ �������� �������� ������ �����ۿ� ���� �ɷ�ġ�� Ȯ���� �� �ִ� ȭ���� ����
*/

int main()
{
	// ������ ����
	API_Window_Main* window = API_Window_Main::Create_Instance();

	cout << "create window..." << endl;
	window->Initialize();	// ���� ������ �ʱ�ȭ
	window->Run();			// ���� ������ �⵿
	cout << "close window..." << endl;

	// �����츦 ����
	API_Window_Main::Release_Instance();
	system("pause");
	return 0;
}