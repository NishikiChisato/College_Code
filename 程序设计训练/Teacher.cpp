#include "Teacher.h"
#include "All_Func_Declare.h"
#include <vector>
#include <string>

using namespace std;

istream& operator>>(istream& cin, Teacher& ter)
{
	cin >> ter.m_name >> ter.password;
	return cin;
}

void Teacher::openmenu()
{
	system("cls");
	cout << "-------------�� ʦ �� �� ¼ �� ��------------" << endl;
	cout << "------------------�� ѡ ��-------------------" << endl;
	cout << "------------1.�� �� ѧ �� �� ��--------------" << endl;
	cout << "------------2.�� �� �� ʦ �� ��--------------" << endl;
	cout << "------------3.�� �� �� �� �� ��--------------" << endl;
	cout << "-----------4.�� �� �� �� �� ѧ ��------------" << endl;
	cout << "---------5.�� �� �� �� ѧ �� �� ��-----------" << endl;
	cout << "-------6.�� �� ÿ �� ѧ �� �� �� ѧ ��-------" << endl;
	cout << "--------------7.�� ѯ ѧ ��------------------" << endl;
	cout << "--------------8.ɾ �� ѧ ��------------------" << endl;
	cout << "--------------9.�� �� ѧ ��------------------" << endl;
	cout << "--------------10.�� �� ѧ ��-----------------" << endl;
	cout << "---------------0.�� �� �� ¼-----------------" << endl;
}

void Teacher::add_Student()
{
	ofstream ofs;

	ofs.open(STU_IFO_FILE, ios::out | ios::app | ios::binary);

	Student tmp;
	tmp.init_Student();

	ofs << tmp << endl;

	ofs.close();

	system("cls");
	cout << "ѧ����ӳɹ�" << endl;
	ofs.close();
}

void Teacher::add_Teacher()
{
	ofstream ofs;
	ofs.open(TEACHER_FILE, ios::out | ios::app);
	Teacher tmp;
	cout << "�������ʦ����������" << endl;
	cin >> tmp.m_name >> tmp.password;
	ofs << tmp.m_name << " " << tmp.password << endl;
	ofs.close();
	system("cls");
	cout << "��ʦ��ӳɹ�" << endl;
	ofs.close();
}


const char* SubName(const int& n)
{
	switch (n)
	{
	case 1:
		return "����"; 
		break;
	case 2:
		return "����";
		break;
	case 3:
		return "����";
		break;
	case 4:
		return "��ѧ";
		break;
	case 5:
		return "���ݽṹ";
		break;
	case 6:
		return "����";
		break;
	case 7:
		return "��ɢ";
		break;
	case 8:
		return "��ʷ";
		break;
	case 9:
		return "����";
		break;
	}
	return"";
}


void Teacher::show_Every_Class_Score()
{
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);

	int n = 0;
	cout << "������������İ༶����" << endl;
	cin >> n;

	//�±��ʾ�༶��Ԫ�ر�ʾ�༶����
	MyArry<int>stu_num(n + 1);

	//ͳ�ư༶���гɼ�֮��
	MyArry<int>sum_cla(n + 1);

	//����
	for (MyArry<int>::iterator it = stu_num.begin(); it != stu_num.end(); it++)
		*it = 0;
	for (MyArry<int>::iterator it = sum_cla.begin(); it != sum_cla.end(); it++)
		*it = 0;

	//�±��ʾ�༶
	//��ϣ���keyֵ��ʾѧ�Ʊ�ţ�value��ʾ�ÿ��ڸð���ܷ�
	//�������Լ�д�Ĺ�ϣ���������Եģ����ÿһ��ѧ��ֻ����һ���±������Ӧ
	MyArry<Hashmap<int, int, HashFunc_int> > arr(n + 1);

	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;

		int cla = tmp.reClass();//���ѧ�����ڵİ༶

		if (cla <= n)//��֤��Խ��
		{
			stu_num[cla]++;

			for (Linklist<Subject>::iterator it = tmp.m_Subject.begin(); it != tmp.m_Subject.end(); it = it->Next)
			{
				if (arr[cla].find(it->data.Subject_Num) == -1)//���ڹ�ϣ����
					arr[cla].insert(it->data.Subject_Num, it->data.Comprehensive_Achievements);
				else arr[cla][it->data.Subject_Num] += it->data.Comprehensive_Achievements;
			}
		}
	}



	for (int i = 1; i < (int)arr.size(); i++)
	{
		if (stu_num[i] == 0)
		{
			cout << i << " �����ʧ��" << endl;
			continue;
		}
		cout << i << " ��ĸ���ƽ���ɼ�Ϊ" << endl;
		for (Hashmap<int, int, HashFunc_int>::iterator it = arr[i].begin(); it != arr[i].end(); it++)
		{
			if (*it)
			{
				cout << SubName((*it)->key) << " " << 1.0 * (*it)->value / stu_num[i] << "   ";
				sum_cla[i] += (*it)->value;
			}
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i < (int)sum_cla.size(); i++)
	{
		if (stu_num[i] == 0)
		{
			cout << i <<" �����ʧ��" << endl;
			continue;
		}
		double n = 1.0 * (sum_cla[i] / stu_num[i]);
		cout << i << " �����ƽ���ɼ�Ϊ " << n / arr[i].Rsize() << endl;
	}
	cout << endl;
	ifs.close();
}

void Teacher::showEvery_Stu_Credit()
{
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);
	;
	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		if (tmp.reSumCredit() != 0)
			cout << tmp.m_name << "  " << tmp.reSumCredit() << endl;
	}
	ifs.close();
	return;
}

void Teacher::show_Fail_Stu()
{
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);
	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		for (Linklist<Subject>::iterator it = tmp.m_Subject.begin(); it != tmp.m_Subject.end(); it = it->Next)
		{
			if (it->data.Comprehensive_Achievements < 60)
				cout << "ѧ�ţ�" << tmp.reStuNum() << "  ������" << tmp.m_name << "  "
				<< it->data.Subject_Name << "  ������" << it->data.Comprehensive_Achievements << " " << endl;
		}
	}
	ifs.close();
	return;
}

class Compare1
{
public:
	bool operator()(Student* e1, Student* e2)
	{
		return e1->reSumScore() > e2->reSumScore();
	}
};

class Compare2
{
public:
	bool operator()(Student* e1, Student* e2)
	{
		if (e1->reSumScore() == e2->reSumScore())
			return e1->reStuNum() < e2->reStuNum();
		return e1->reSumScore() < e2->reSumScore();
	}
};

class Compare3
{
public:
	bool operator()(Student* e1, Student* e2)
	{
		if (e1->reSumCredit() == e2->reSumCredit())
			return e1->reSumScore() < e2->reSumScore();
		return e1->reSumCredit() < e2->reSumCredit();
	}
};

static void Chose()
{
	system("cls");
	cout << "-------------������֧�ָ߼�����-------------" << endl;
	cout << "-------------��ѡ��Ĭ������-------------" << endl;
	cout << "-----------1.����ƽ���ɼ�����---------------" << endl;
	cout << "---2.ƽ��������ƽ������ͬ����ѧ������---" << endl;
	cout << "---3.ѧ�ְ�����ѧ����ͬ����ƽ��������---" << endl;
	cout << "------------------0.�˳�--------------------" << endl;
}


void Teacher::show_Every_Stu_Score()
{

	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);
	Linklist<Student>L;
	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		if (tmp.reStuNum() != 0)//��ȥ���һ��������Ķ�ȡ
		{
			L.addtail(tmp);
		}
	}

	vector<Student*>v;

	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	{
		v.push_back(&it->data);
	}

	int input = 0;
	do
	{
		Chose();
		cin >> input;

		switch (input)
		{
		case 1:
		{
			sort(v.begin(), v.end(), Compare1());
			system("cls");
			int i = 0;
			for (vector<Student*>::iterator it = v.begin(); it != v.end(); it++)
			{
				cout << "�� " << i + 1 << " ����" << endl;
				cout << (*it)->m_name << " ѧ�ţ�" << (*it)->reStuNum() << endl;
				(*it)->show_Every_Score();
				cout << "ƽ����Ϊ" << endl;
				cout << (*it)->reSumScore() << endl;
				i++;
			}
			system("pause");
		}
		break;
		case 2:
		{
			sort(v.begin(), v.end(), Compare2());
			system("cls");
			int i = 0;
			for (vector<Student*>::iterator it = v.begin(); it != v.end(); it++)
			{
				cout << "�� " << i + 1 << " ����" << endl;
				cout << (*it)->m_name << " ѧ�ţ�" << (*it)->reStuNum() << endl;
				(*it)->show_Every_Score();
				cout << "ƽ����Ϊ" << endl;
				cout << (*it)->reSumScore() << endl;
				i++;
			}
			system("pause");
		}
		break;
		case 3:
		{
			sort(v.begin(), v.end(), Compare3());
			system("cls");
			int i = 0;
			for (vector<Student*>::iterator it = v.begin(); it != v.end(); it++)
			{
				cout << "�� " << i + 1 << " ����" << endl;
				cout << (*it)->m_name << " ѧ�ţ�" << (*it)->reStuNum() << endl;
				(*it)->show_Every_Score();
				cout << "ƽ����Ϊ" << endl;
				cout << (*it)->reSumScore() << endl;
				i++;
			}
			system("pause");
		}
		break;
		case 0:
			break;
		default:
			cout << "����������������" << endl;
			system("pause");
			break;
		}
	} while (input);
	ifs.close();
}

void Teacher::find_Stu()
{
	cout << "������ѧ������" << endl;
	Mystring Name;
	cin >> Name;
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);
	int flag = 0;
	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		if (tmp.m_name == Name)
		{
			tmp.show_Student();
			flag = 1;
		}
	}
	if (flag == 0)
		cout << "δ�ҵ�" << endl;
	else;
	ifs.close();
}

void Teacher::del_Stu()
{
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);



	Linklist<Student>L;
	
	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		if (tmp.reStuNum() != 0)
		{
			L.addtail(tmp);
		}
	}

	cout << "��ǰ���ݿ�Ϊ" << endl;
	cout << endl;
	
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();

	cout << endl;
	cout << "�������ɾ��������±���" << endl;

	int index = 0;
	cin >> index;
	cout << endl;

	L.deleteindex(index);

	cout << "ɾ�������ݿ�Ϊ" << endl;

	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();
	
	cout << endl;
	ifs.close();
	//ɾ���ļ�
	if (remove(STU_IFO_FILE) == 0)
		cout << "File Delete Success" << endl;

	ofstream ofs;
	ofs.open(STU_IFO_FILE, ios::out | ios::app);
	if (ofs.is_open())
		cout << "File Create Success" << endl << endl;

	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		ofs << it->data << endl;
	
}

void Teacher::insert_Stu()
{
	Linklist<Student>L;
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);

	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		if (tmp.reStuNum() != 0)
			L.addtail(tmp);
	}

	cout << "��ǰ���ݿ�Ϊ" << endl;
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();

	int index = 0;
	cout << "���������ѧ��λ�õ��±�" << endl;
	cin >> index;

	Student tmp;
	tmp.init_Student();
	L.insertindex(index, tmp);

	cout << "��������ݿ�Ϊ" << endl;
	cout << endl;
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();
	ifs.close();

	ofstream ofs;
	ofs.open(STU_IFO_FILE, ios::out | ios::app);
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	{
		ofs << it->data << endl;
	}

	ofs.close();
	cout << "ѧ����Ϣ�޸ĳɹ�" << endl;
	return;
}

void Teacher::modify_Stu()
{
	Mystring Name;
	Mystring Pass;
	cout << "��������޸ĵ�ѧ��������������" << endl;
	cin >> Name >> Pass;
	Linklist<Student>L;
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);

	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;
		if (tmp.reStuNum() != 0)
			L.addtail(tmp);
	}
	//Ӧ����ɾ��������Ϣ��Ȼ���ٴ��²���
	int flag = 0;//�жϸ�ѧ���Ƿ����
	int index = 0;
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	{
		if (Name == it->data.m_name && Pass == it->data.password)
		{
			break;
			flag = 1;
		}
		index++;
	}
	if (flag == 0)
	{
		cout << "��ѧ��������" << endl;
		return;
	}
	ifs.close();
	L.deleteindex(index);
	Student tmp;
	cout << "����������ѧ����Ϣ" << endl;
	tmp.init_Student();
	L.insertindex(index, tmp);

	//ɾ��ԭ�ļ�
	if (remove(STU_IFO_FILE) == 0)
		cout << "File Delete Success" << endl;

	ofstream ofs;
	ofs.open(STU_IFO_FILE, ios::out | ios::app);
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	{
		ofs << it->data << endl;
	}

	ofs.close();
	cout << "ѧ����Ϣ�޸ĳɹ�" << endl;

}