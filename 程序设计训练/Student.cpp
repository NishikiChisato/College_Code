#include <iostream>
#include "Student.h"
#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

//学科类运算符重载函数、构造函数以及成员函数的实现

ostream& operator<<(ostream& cout, Subject& sub)
{
	cout << sub.Subject_Num << " " << sub.Subject_Name << " " << sub.Exam_Resule << " "
		<< sub.Usual_Performance << " " << sub.Comprehensive_Achievements << " " << sub.Subject_Credit << " ";
	if (sub.Repair_Num == 0)
		cout << sub.Repair_Num << " ";
	else
		cout << sub.Repair_Num << " " << sub.Repair_term << " " << sub.Repair_Score << " ";
	return cout;
}

istream& operator>>(istream& cin, Subject& sub)
{
	cin >> sub.Subject_Num >> sub.Subject_Name >> sub.Exam_Resule
		>> sub.Usual_Performance >> sub.Comprehensive_Achievements >> sub.Subject_Credit
		>> sub.Repair_Num;
	if (sub.Repair_Num != 0)
		cin >> sub.Repair_term >> sub.Repair_Score;
	else;
	return cin;
}

Subject::Subject()
{
	this->Subject_Num = 0;
	this->Exam_Resule = 0;
	this->Usual_Performance = 0;
	this->Comprehensive_Achievements = 0;
	this->Subject_Credit = 0;
	this->Repair_Num = 0;
	this->Repair_Score = 0;
}

Subject* Subject::init_Subject()
{
	cout << "请依次输入该学生该学科的学科编号、学科名、考试成绩、平时成绩、综合成绩、学分和重修次数" << endl;
	cin >> this->Subject_Num >>this->Subject_Name >> this->Exam_Resule >> this->Usual_Performance 
		>> this->Comprehensive_Achievements>> this->Subject_Credit >> this->Repair_Num;
	if (this->Repair_Num != 0)
	{
		cout << "请输入该学生的重修学期与重修分数" << endl;
		cin >> this->Repair_term >> this->Repair_Score;
	}
	return this;
}

void Subject::show_Subject()
{
	cout <<  this->Subject_Num << " " << this->Subject_Name << " " << this->Exam_Resule << " " 
		<< this->Usual_Performance << " "<< this->Comprehensive_Achievements << " "<< this->Subject_Credit << " ";
	if (this->Repair_Num == 0)
		cout << "不需要重修" << endl;
	else
	{
		cout << "重修次数 " << this->Repair_Num << " 重修时间 " << this->Repair_term 
			<< " 重修分数 " << this->Repair_Score << endl;
	}
}


//学生类成员函数的实现

//重载运算符，仅用作文件输入输出
ostream& operator<<(ostream& cout, Student& stu)
{
	cout << stu.Student_number << " " << stu.m_name << " " << stu.S_class
		<< " " << stu.age << " " << stu.Gender << " " << stu.Dormitory_num << " " << stu.Telephone_num << " "
		<< stu.password << " " << stu.Subject_sum << " ";
	for (Linklist<Subject>::iterator it = stu.m_Subject.begin(); it != stu.m_Subject.end(); it = it->Next)
		cout << it->data;
	return cout;
}

istream& operator>>(istream& cin, Student& stu)
{
	cin >> stu.Student_number >> stu.m_name >> stu.S_class >> stu.age >> stu.Gender >> stu.Dormitory_num >> stu.Telephone_num;
	cin >> stu.password;
	cin >> stu.Subject_sum;
	Subject tmp;
	for (int i = 0; i < stu.Subject_sum; i++)
	{
		cin >> tmp;
		stu.m_Subject.addtail(tmp);
	}
	return cin;
}

//打印学生对象
void Student::show_Student()
{
	cout << "学号： " << this->Student_number << "  " << "姓名： " << this->m_name << "  ";
	cout << "班级： " << this->S_class << "  ";
	cout << "年龄： " << this->age << "  " << "性别： " << this->Gender << "  ";
	cout << "宿舍号码： " << this->Dormitory_num << "  " << "电话号码： " << this->Telephone_num << "  " << endl;
	cout << "各科目情况为：" << endl;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
	{
		cout << it->data.Subject_Name << " " << it->data.Exam_Resule << " " << it->data.Usual_Performance << " "
			<< it->data.Comprehensive_Achievements << " ";
		if (it->data.Repair_Num == 0)
			cout << "不需要重修" << endl;
		else
			cout << "需要重修 " << it->data.Repair_term << " " << it->data.Repair_Score << endl;
	}
}

//初始化学生对象
Student* Student::init_Student()
{
	cout << "请分别输入学生学号、姓名、班级、年龄、性别、宿舍号码、电话号码" << endl;
	cin >> this->Student_number >> this->m_name >> this->S_class >> this->age 
		>> this->Gender >> this->Dormitory_num >> this->Telephone_num;
	cout << "请输入该学生登录密码" << endl;
	cin >> this->password;
	cout << "请输入该学生已选择的科目数" << endl;
	cin >> this->Subject_sum;
	for (int i = 0; i < this->Subject_sum; i++)
	{
		cout << "第 " << i + 1 << " 门学科：";
		Subject tmp;
		tmp.init_Subject();
		this->m_Subject.addtail(tmp);
	}
	return this;
}

//学生开始菜单显示函数
void Student::openmenu()
{
	system("cls");
	cout << "------------学 生 端 登 录 成 功------------" << endl;
	cout << "------------------请 选 择------------------" << endl;
	cout << "-----------1.查 看 自 己 成 绩--------------" << endl;
	cout << "-----------2.查 看 已 修 学 分--------------" << endl;
	cout << "-----------3.查 看 平 均 成 绩--------------" << endl;
	cout << "-----------4.查 看 重 修 情 况--------------" << endl;
	cout << "--------------0.退 出 登 录-----------------" << endl;
}

//默认构造函数
Student::Student()
{
	this->age = 0;
	this->Dormitory_num = 0;
	this->S_class = 0;
	this->Telephone_num = 0;
	this->Student_number = 0;
	this->Subject_sum = 0;
	this->m_Subject;
}

//返回学生已修学分
int Student::reSumCredit()
{
	int sum_of_credit = 0;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
	{
		sum_of_credit += it->data.Subject_Credit;
	}
	return sum_of_credit;
}

//返回成绩平均值
double Student::reSumScore()
{
	double sum_of_score = 0;
	int n = 0;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
	{
		sum_of_score += it->data.Comprehensive_Achievements;
		n++;
	}
	return (1.0) * sum_of_score / n;
}

//打印每科考试成绩
void Student::show_Every_Score()
{
	int count = 0;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
	{
		it->data.show_Subject();
		count++;
		if (count == 5)
		{
			cout << endl;
			count = 0;
		}
	}
}

void Student::showRepairs()
{
	int flag = 0;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
		if (it->data.Repair_Num != 0)
		{
			cout << it->data.Subject_Name << " 重修次数 " << it->data.Repair_Num << " 重修时间 "
				<< it->data.Repair_term << " 重修分数 " << it->data.Repair_Score << endl;
			flag = 1;
		}
	if (flag == 0)
		cout << "不需要重修" << endl;
	return;
	
}

Student& Student::operator=(const Student& STU)
{
	this->Student_number = STU.Student_number;
	this->m_name= STU.m_name;
	password = STU.password;
	S_class = STU.S_class;
	this->age = STU.age;
	Gender = STU.Gender;
	this->Dormitory_num = STU.Dormitory_num;
	this->Telephone_num = STU.Telephone_num;
	this->Subject_sum = STU.Subject_sum;
	for (Linklist<Subject>::iterator it = STU.m_Subject.begin(); it != STU.m_Subject.end(); it = it->Next)
	{
		this->m_Subject.addtail(it->data);
	}
	return *this;
}

Student::Student(const Student& STU)
{
	this->Student_number = STU.Student_number;
	this->m_name = STU.m_name;
	password = STU.password;
	S_class = STU.S_class;
	this->age = STU.age;
	Gender = STU.Gender;
	this->Dormitory_num = STU.Dormitory_num;
	this->Telephone_num = STU.Telephone_num;
	this->Subject_sum = STU.Subject_sum;
	for (Linklist<Subject>::iterator it = STU.m_Subject.begin(); it != STU.m_Subject.end(); it = it->Next)
	{
		this->m_Subject.addtail(it->data);
	}
}

int Student::reClass()
{
	return this->S_class;
}

int Student::reStuNum()
{
	return this->Student_number;
}