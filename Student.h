#pragma once

#include "Abstract.h"
#include "Linklist.hpp"


using namespace std;

//ѧ����
class Subject
{
	friend istream& operator>>(istream& cin, Subject& sub);
	friend ostream& operator<<(ostream& cout, Subject& sub);

public:
	//ѧ�Ʊ��
	int Subject_Num;

	//ѧ������
	Mystring Subject_Name;

	//���Գɼ�
	int Exam_Resule;

	//ƽʱ�ɼ�
	int Usual_Performance;

	//�ۺϳɼ�
	int Comprehensive_Achievements;

	//ѧ��ѧ��
	int Subject_Credit;

	//���޴�����0��ʾ��������
	int Repair_Num;

	//����ѧ��
	Mystring Repair_term;
	
	//���޷�����0��ʾ��δ���ޣ���0���������ֵ��ʾ���������
	int Repair_Score;

	//Ĭ�Ϲ���
	Subject();

	//��ʼ��������
	Subject* init_Subject();

	//��ӡѧ�ƶ���
	void show_Subject();
};

//ѧ����
class Student : public Abstract, public Subject
{

	//�������ơ������������ר�������ļ������������
	friend istream& operator>>(istream& cin, Student& stu);
	friend ostream& operator<<(ostream& cout, Student& stu);


private:
	int Student_number;//ѧ��
	Mystring Gender;//�Ա�
	int age;//����
	int S_class;//�༶
	int Dormitory_num;//�������
	int Telephone_num;//�绰����


public:

	int Subject_sum;//��ѡѧ������
	//��ѡ��Ŀ������洢
	Linklist<Subject>m_Subject;


	//Ĭ�Ϲ��캯��
	Student();

	//�������캯��
	Student(const Student& stu);

	//��ʼ��ѧ������
	Student* init_Student();

	//��ӡѧ������
	void show_Student();

	//��¼�˵�
	void openmenu();

	//��ӡÿ�ƿ��Գɼ�
	void show_Every_Score();

	//��������ѧ��
	int reSumCredit();

	//�������޿�Ŀƽ���ɼ�
	double reSumScore();

	//���ذ༶
	int reClass();

	//����ѧ��
	int reStuNum();



	//�鿴�������
	void showRepairs();

	//���صȺŸ�ֵ
	Student& operator=(const Student& STU);


};