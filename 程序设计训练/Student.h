#pragma once

#include "Abstract.h"
#include "Linklist.hpp"


using namespace std;

//学科类
class Subject
{
	friend istream& operator>>(istream& cin, Subject& sub);
	friend ostream& operator<<(ostream& cout, Subject& sub);

public:
	//学科编号
	int Subject_Num;

	//学科名称
	Mystring Subject_Name;

	//考试成绩
	int Exam_Resule;

	//平时成绩
	int Usual_Performance;

	//综合成绩
	int Comprehensive_Achievements;

	//学科学分
	int Subject_Credit;

	//重修次数，0表示不用重修
	int Repair_Num;

	//重修学期
	Mystring Repair_term;
	
	//重修分数，0表示还未重修，除0以外的其他值表示已重修完毕
	int Repair_Score;

	//默认构造
	Subject();

	//初始化对象函数
	Subject* init_Subject();

	//打印学科对象
	void show_Subject();
};

//学生类
class Student : public Abstract, public Subject
{

	//重载左移、右移运算符，专门用于文件的输入与输出
	friend istream& operator>>(istream& cin, Student& stu);
	friend ostream& operator<<(ostream& cout, Student& stu);


private:
	int Student_number;//学号
	Mystring Gender;//性别
	int age;//年龄
	int S_class;//班级
	int Dormitory_num;//宿舍号码
	int Telephone_num;//电话号码


public:

	int Subject_sum;//所选学科数量
	//所选科目，链表存储
	Linklist<Subject>m_Subject;


	//默认构造函数
	Student();

	//拷贝构造函数
	Student(const Student& stu);

	//初始化学生对象
	Student* init_Student();

	//打印学生对象
	void show_Student();

	//登录菜单
	void openmenu();

	//打印每科考试成绩
	void show_Every_Score();

	//返回已修学分
	int reSumCredit();

	//返回已修科目平均成绩
	double reSumScore();

	//返回班级
	int reClass();

	//返回学号
	int reStuNum();



	//查看重修情况
	void showRepairs();

	//重载等号赋值
	Student& operator=(const Student& STU);


};