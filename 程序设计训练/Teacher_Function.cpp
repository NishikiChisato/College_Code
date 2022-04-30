#include "All_Func_Declare.h"

void Tea_Func(Abstract* ptr)
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
		system("cls");
		((Teacher*)ptr)->add_Student();
		system("pause");
		break;
	case 2:
		system("cls");
		((Teacher*)ptr)->add_Teacher();
		system("pause");
		break;
	case 3:
		system("cls");
		((Teacher*)ptr)->show_Every_Class_Score();
		system("pause");
		break;
	case 4:
		system("cls");
		((Teacher*)ptr)->show_Fail_Stu();
		system("pause");
		break;
	case 5:
		system("cls");
		((Teacher*)ptr)->show_Every_Stu_Score();
		system("pause");
		break;
	case 6:
		system("cls");
		((Teacher*)ptr)->showEvery_Stu_Credit();
		system("pause");
		break;
	case 7:
		system("cls");
		((Teacher*)ptr)->find_Stu();
		system("pause");
		break;
	case 8:
		system("cls");
		((Teacher*)ptr)->del_Stu();
		system("pause");
		break;
	case 9:
		system("cls");
		((Teacher*)ptr)->insert_Stu();
		system("pause");
		break;
	case 10:
		system("cls");
		((Teacher*)ptr)->modify_Stu();
		system("pause");
		break;
	default:
		break;
	}
	} while (input);
	
	cout << "ÍË³ö³É¹¦" << endl;
	system("pause");
}