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


//��¼������ǰ��Ϊ��¼�ļ�������Ϊ��¼���ͣ�ѧ������ʦ��
//typeΪ1��ʾѧ����2��ʾ��ʦ
void Login(Mystring filename, int type);

//��ʼ����˵�����
void init_menu();

//����˵������
void Explain();

//ѧ���˹��ܺ��������ڴ���ѧ���˹���
//����1Ϊ����ָ�룬���ڶ�̬���������ຯ��������2Ϊ��ѧ��������
void Stu_Func(Abstract* ptr);


//��ʦ�˹��ܺ���
//����ָ�����ڶ�̬
void Tea_Func(Abstract* ptr);
