#include "All_Func_Declare.h"


void Stu_Func(Abstract* ptr)
{
	system("cls");

	int input = 0;
	do 
	{
		ptr->openmenu();
		cin >> input;
		switch (input)
		{
		case 1:
		{
			system("cls");
			((Student*)ptr)->show_Every_Score();
			system("pause");
		}
			break;
		case 2:
		{
			system("cls");
			cout << "目前已修学分为：" << ((Student*)ptr)->reSumCredit() << endl;
			system("pause");
		}
			break;
		case 3:
		{
			system("cls");
			cout << "总平均成绩为：" << ((Student*)ptr)->reSumScore() << endl;
			system("pause");
		}
			break;
		case 4:
		{
			system("cls");
			((Student*)ptr)->showRepairs();
			system("pause");
		}
			break;
		default:
			break;
		}

	} while (input);

	cout << "退出成功" << endl;
	system("pause");

}