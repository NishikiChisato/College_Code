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
			cout << "Ŀǰ����ѧ��Ϊ��" << ((Student*)ptr)->reSumCredit() << endl;
			system("pause");
		}
			break;
		case 3:
		{
			system("cls");
			cout << "��ƽ���ɼ�Ϊ��" << ((Student*)ptr)->reSumScore() << endl;
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

	cout << "�˳��ɹ�" << endl;
	system("pause");

}