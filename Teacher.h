#pragma once

#include "Abstract.h"

using namespace std;

class Teacher :public Abstract
{
	//全局函数友元声明
	friend istream& operator>>(istream& cin, Teacher& ter);

public:


	//登录菜单
	void openmenu();

	//添加学生账号
	void add_Student();

	//添加老师账号
	void add_Teacher();

	//查看每个学生成绩，有排序选择
	void show_Every_Stu_Score();

	//查看各班各门功课的平均成绩和总的平均成绩
	void show_Every_Class_Score();

	//查看不及格学生
	void show_Fail_Stu();

	//输出每个同学已修学分
	void showEvery_Stu_Credit();

	//查询学生
	void find_Stu();

	//删除学生
	void del_Stu();

	//修改学生
	void modify_Stu();

	//插入学生
	void insert_Stu();



};
