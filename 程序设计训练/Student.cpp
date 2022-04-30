#include <iostream>
#include "Student.h"
#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

//ѧ������������غ��������캯���Լ���Ա������ʵ��

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
	cout << "�����������ѧ����ѧ�Ƶ�ѧ�Ʊ�š�ѧ���������Գɼ���ƽʱ�ɼ����ۺϳɼ���ѧ�ֺ����޴���" << endl;
	cin >> this->Subject_Num >>this->Subject_Name >> this->Exam_Resule >> this->Usual_Performance 
		>> this->Comprehensive_Achievements>> this->Subject_Credit >> this->Repair_Num;
	if (this->Repair_Num != 0)
	{
		cout << "�������ѧ��������ѧ�������޷���" << endl;
		cin >> this->Repair_term >> this->Repair_Score;
	}
	return this;
}

void Subject::show_Subject()
{
	cout <<  this->Subject_Num << " " << this->Subject_Name << " " << this->Exam_Resule << " " 
		<< this->Usual_Performance << " "<< this->Comprehensive_Achievements << " "<< this->Subject_Credit << " ";
	if (this->Repair_Num == 0)
		cout << "����Ҫ����" << endl;
	else
	{
		cout << "���޴��� " << this->Repair_Num << " ����ʱ�� " << this->Repair_term 
			<< " ���޷��� " << this->Repair_Score << endl;
	}
}


//ѧ�����Ա������ʵ��

//������������������ļ��������
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

//��ӡѧ������
void Student::show_Student()
{
	cout << "ѧ�ţ� " << this->Student_number << "  " << "������ " << this->m_name << "  ";
	cout << "�༶�� " << this->S_class << "  ";
	cout << "���䣺 " << this->age << "  " << "�Ա� " << this->Gender << "  ";
	cout << "������룺 " << this->Dormitory_num << "  " << "�绰���룺 " << this->Telephone_num << "  " << endl;
	cout << "����Ŀ���Ϊ��" << endl;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
	{
		cout << it->data.Subject_Name << " " << it->data.Exam_Resule << " " << it->data.Usual_Performance << " "
			<< it->data.Comprehensive_Achievements << " ";
		if (it->data.Repair_Num == 0)
			cout << "����Ҫ����" << endl;
		else
			cout << "��Ҫ���� " << it->data.Repair_term << " " << it->data.Repair_Score << endl;
	}
}

//��ʼ��ѧ������
Student* Student::init_Student()
{
	cout << "��ֱ�����ѧ��ѧ�š��������༶�����䡢�Ա�������롢�绰����" << endl;
	cin >> this->Student_number >> this->m_name >> this->S_class >> this->age 
		>> this->Gender >> this->Dormitory_num >> this->Telephone_num;
	cout << "�������ѧ����¼����" << endl;
	cin >> this->password;
	cout << "�������ѧ����ѡ��Ŀ�Ŀ��" << endl;
	cin >> this->Subject_sum;
	for (int i = 0; i < this->Subject_sum; i++)
	{
		cout << "�� " << i + 1 << " ��ѧ�ƣ�";
		Subject tmp;
		tmp.init_Subject();
		this->m_Subject.addtail(tmp);
	}
	return this;
}

//ѧ����ʼ�˵���ʾ����
void Student::openmenu()
{
	system("cls");
	cout << "------------ѧ �� �� �� ¼ �� ��------------" << endl;
	cout << "------------------�� ѡ ��------------------" << endl;
	cout << "-----------1.�� �� �� �� �� ��--------------" << endl;
	cout << "-----------2.�� �� �� �� ѧ ��--------------" << endl;
	cout << "-----------3.�� �� ƽ �� �� ��--------------" << endl;
	cout << "-----------4.�� �� �� �� �� ��--------------" << endl;
	cout << "--------------0.�� �� �� ¼-----------------" << endl;
}

//Ĭ�Ϲ��캯��
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

//����ѧ������ѧ��
int Student::reSumCredit()
{
	int sum_of_credit = 0;
	for (Linklist<Subject>::iterator it = this->m_Subject.begin(); it != this->m_Subject.end(); it = it->Next)
	{
		sum_of_credit += it->data.Subject_Credit;
	}
	return sum_of_credit;
}

//���سɼ�ƽ��ֵ
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

//��ӡÿ�ƿ��Գɼ�
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
			cout << it->data.Subject_Name << " ���޴��� " << it->data.Repair_Num << " ����ʱ�� "
				<< it->data.Repair_term << " ���޷��� " << it->data.Repair_Score << endl;
			flag = 1;
		}
	if (flag == 0)
		cout << "����Ҫ����" << endl;
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