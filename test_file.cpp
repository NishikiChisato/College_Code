#define _CRT_SECURE_NO_WARNINGS 1
#include "All_Func_Declare.h"
#include <vector>
using namespace std;

//注：该文件仅仅为测试文件，不参与任何函数的调用

class Compare
{
public:
	bool operator()(Student* e1, Student* e2)
	{
		return e1->reSumScore() > e2->reSumScore();
	}
};



void test01()
{
	
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);

	Student tmp;
	ifs >> tmp;
	tmp.show_Student();



	////存储每个学生对象
	//Linklist<Student>L;

	//while (!ifs.eof())
	//{
	//	Student tmp;
	//	ifs >> tmp;
	//	if (tmp.reStuNum() != 0)
	//	{
	//		L.addtail(tmp);
	//	}
	//}

	//cout << "当前数据库为" << endl;
	//cout << endl;
	//for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	//	it->data.show_Student();

	//cout << endl;
	//cout << "请输入待删除对象的下标编号" << endl;


	//int index = 0;
	//cin >> index;
	//cout << endl;


	//L.deleteindex(index);


	//cout << "删除后数据库为" << endl;
	//for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	//	it->data.show_Student();

	//ifs.close();
	//if (remove(STU_IFO_FILE) == 0)
	//	cout << "File Delete Success" << endl;

	//ofstream ofs;
	//ofs.open(STU_IFO_FILE, ios::out | ios::app);
	//if (ofs.is_open())
	//	cout << "File Create Success" << endl;



	//for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	//	ofs << it->data << endl;


}