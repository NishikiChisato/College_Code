#define _CRT_SECURE_NO_WARNINGS 1

#include "All_Func_Declare.h"
#include <iostream>
#include <fstream>


using namespace std;

//�������Ժ�������������������
void test01();



int main()
{
	//���ô��ڱ���
	SetConsoleTitle(L"�������ϵͳ");
	//������ɫ
	system("color 70");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

	int input = 0;
	while (true)
	{
	init_menu();
	cin >> input;
	switch (input)
	{
	//ѧ��
	case 1:
		Login(STU_IFO_FILE, 1);
		break;
	//��ʦ
	case 2:
		Login(TEACHER_FILE, 2);
		break;
	case 3:
		Explain();
		break;
	case 0:
		cout << "��ӭ�´�ʹ��" << endl;
		return 0;
	default:
		cout << "������������������" << endl;
		system("pause");
		system("cls");
		break;
	}
	}
	return 0;
}