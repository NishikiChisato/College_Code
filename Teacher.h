#pragma once

#include "Abstract.h"

using namespace std;

class Teacher :public Abstract
{
	//ȫ�ֺ�����Ԫ����
	friend istream& operator>>(istream& cin, Teacher& ter);

public:


	//��¼�˵�
	void openmenu();

	//���ѧ���˺�
	void add_Student();

	//�����ʦ�˺�
	void add_Teacher();

	//�鿴ÿ��ѧ���ɼ���������ѡ��
	void show_Every_Stu_Score();

	//�鿴������Ź��ε�ƽ���ɼ����ܵ�ƽ���ɼ�
	void show_Every_Class_Score();

	//�鿴������ѧ��
	void show_Fail_Stu();

	//���ÿ��ͬѧ����ѧ��
	void showEvery_Stu_Credit();

	//��ѯѧ��
	void find_Stu();

	//ɾ��ѧ��
	void del_Stu();

	//�޸�ѧ��
	void modify_Stu();

	//����ѧ��
	void insert_Stu();



};
