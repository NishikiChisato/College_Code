#pragma once

#include "Linklist.hpp"
#include "MyString.h"
#include "MyArry.hpp"
#include "Name_Defined.h"
#include "Abstract.h"
#include "Student.h"
#include "Teacher.h"
#include "Hashmap.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <conio.h>

using namespace std;


//登录函数，前者为登录文件，后者为登录类型（学生或老师）
//type为1表示学生，2表示老师
void Login(Mystring filename, int type);

//初始界面菜单函数
void init_menu();

//程序说明函数
void Explain();

//学生端功能函数，用于处理学生端功能
//参数1为基类指针，用于多态调用派生类函数，参数2为该学生的数据
void Stu_Func(Abstract* ptr);


//教师端功能函数
//基类指针用于多态
void Tea_Func(Abstract* ptr);
