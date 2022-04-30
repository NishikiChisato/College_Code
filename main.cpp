#define _CRT_SECURE_NO_WARNINGS 1

#include "All_Func_Declare.h"
#include <iostream>
#include <fstream>


using namespace std;

//声明测试函数，本函数仅供测试
void test01();



int main()
{
	//设置窗口标题
	SetConsoleTitle(L"教务管理系统");
	//设置颜色
	system("color 70");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

	int input = 0;
	while (true)
	{
	init_menu();
	cin >> input;
	switch (input)
	{
	//学生
	case 1:
		Login(STU_IFO_FILE, 1);
		break;
	//教师
	case 2:
		Login(TEACHER_FILE, 2);
		break;
	case 3:
		Explain();
		break;
	case 0:
		cout << "欢迎下次使用" << endl;
		return 0;
	default:
		cout << "输入有误，请重新输入" << endl;
		system("pause");
		system("cls");
		break;
	}
	}
	return 0;
}