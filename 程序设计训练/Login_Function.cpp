#include "All_Func_Declare.h"
#include <iostream>
#include <fstream>

using namespace std;



void Login(Mystring filename, int type)
{
	//基类指针，用于调用函数
	Abstract* ptr;


	//文件读取对象
	ifstream ifs;

	//转换为char*类型
	char* file = filename.to_str();

	ifs.open(file, ios::in);

	//用户输入的名字与密码
	Mystring Account;
	Mystring Password;

	system("cls");
	
	cout << "请输入姓名与密码" << endl;
	cin >> Account >> Password;

	if (type == 1)//学生登录
	{
	

		//这里没有用哈希表的必要，用哈希表的话也需要将全部登录信息都载入内存当中，还不如直接在文件当中查找
		while (!ifs.eof())
		{	
			//临时对象，用于查找，这个一定要写在循环里面
			Student tmp;

			ifs >> tmp;
			if (Account == tmp.m_name && Password == tmp.password)
			{
				cout << "学生端登录成功" << endl;
				system("pause");
				Stu_Func(&tmp);
				system("cls");
				return;
			}
		}
	}
	if (type == 2)
	{
		
		while (!ifs.eof())
		{
			Teacher tmp;
			ifs >> tmp;
			if (Account == tmp.m_name && Password == tmp.password)
			{
				cout << "教师端登录成功" << endl;
				system("pause");
				ptr = new Teacher;
				Tea_Func(ptr);
				system("cls");
				return;
			}
		}
	}
	cout << "验证失败，返回主菜单" << endl;
	system("pause");
	system("cls");
	return;
}

void init_menu()
{

	cout << "-------------------------------------------" << endl;
	cout << "----------欢 迎 登 录 教 务 系 统----------" << endl;
	cout << "----------       请 选 择        ----------" << endl;
	cout << "----------    1.学 生 登 录      ----------" << endl;
	cout << "----------    2.教 师 登 录      ----------" << endl;
	cout << "----------    3.关 于 版 本      ----------" << endl;
	cout << "----------    0.退 出 登 录      ----------" << endl;
	cout << "-------------------------------------------" << endl;
}

void Explain()
{
	system("cls");
	//设置本地语言
	locale::global(locale(""));
	char inc = ' ';
	wchar_t ch[] = L"关于该版本的几点说明（按下任意键跳过该动画过程）：\n1.我在原来的基础上新增了教师模块，"
		L"将原本教务系统的基本功能与统计功能全部移动到教师模块上，学生部分仅提供最基础的成绩信息查询\n"
		L"2.所有账号的登录均是用名字与密码来进行登录\n"
		L"3.所有账号的初始密码均为 123456\n"
		L"4.教师部分有两个初始账号：Hekari、平冢静\n"
		L"目前已知的问题：\n"
		L"1.学科数目只有9个，要增加的话必须要改动源码\n"
		L"2.本版本在每个模块处并没有直接退出的选项，需要将该模块执行完毕后才能退出\n"
		L"其他：\n"
		L"1.在显示所有学生成绩的模块（教师端按下5），由于我欠缺内存管理方面的知识，"
		L"并且我找遍了各大论坛都没有找到我所需要的知识；另一方面，由于学生对象内部还维护了一个链表，"
		L"并且该链表还不是以指针的形式定义，这就导致了我在构造函数那一块只能依靠我链表内部自身的构造函数来对"
		L"这个成员遍历进行初始化（我一开始并没有考虑到这里需要用指针来维护这个链表，要不然我肯定会用指针的！岂可休！！）"
		L"，或许是这两点导致我学生对象的指针总是初始化失败，"
		L"最后我实在是没有办法，最终只能选择用STL容器自带的vector来解决这一问题，并且用了sort排序来解决指针排序的问题\n"
		L"2.我自己实现了三个类模板：动态扩容数组，字符串，哈希表。第三个没有问题，"
		L"第一个是在对象的初始化以及动态扩容上有问题（当然，如果对象有明确的构造函数的话这两方面都不会有问题）"
		L"第二个是在拷贝构造函数这里有问题，之后我得专门找个时间去把STL的容器全部实现一遍\n";
	for (int i = 0; i < 637; i++)
	{
		wcout << ch[i];
		if (_kbhit() != 0)
		{
			system("cls");
			wcout << ch << endl;
			break;
		}
		Sleep(100);
	}
	system("pause");
	system("cls");
}