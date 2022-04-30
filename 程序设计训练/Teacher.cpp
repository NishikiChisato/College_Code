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
	cout << "-------------教 师 端 登 录 成 功------------" << endl;
	cout << "------------------请 选 择-------------------" << endl;
	cout << "------------1.添 加 学 生 账 号--------------" << endl;
	cout << "------------2.添 加 教 师 账 号--------------" << endl;
	cout << "------------3.查 看 各 班 成 绩--------------" << endl;
	cout << "-----------4.查 看 不 及 格 学 生------------" << endl;
	cout << "---------5.查 看 所 有 学 生 成 绩-----------" << endl;
	cout << "-------6.查 看 每 个 学 生 已 修 学 分-------" << endl;
	cout << "--------------7.查 询 学 生------------------" << endl;
	cout << "--------------8.删 除 学 生------------------" << endl;
	cout << "--------------9.插 入 学 生------------------" << endl;
	cout << "--------------10.修 改 学 生-----------------" << endl;
	cout << "---------------0.退 出 登 录-----------------" << endl;
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
	cout << "学生添加成功" << endl;
	ofs.close();
}

void Teacher::add_Teacher()
{
	ofstream ofs;
	ofs.open(TEACHER_FILE, ios::out | ios::app);
	Teacher tmp;
	cout << "请输入教师名字与密码" << endl;
	cin >> tmp.m_name >> tmp.password;
	ofs << tmp.m_name << " " << tmp.password << endl;
	ofs.close();
	system("cls");
	cout << "教师添加成功" << endl;
	ofs.close();
}


const char* SubName(const int& n)
{
	switch (n)
	{
	case 1:
		return "高数"; 
		break;
	case 2:
		return "大物";
		break;
	case 3:
		return "计网";
		break;
	case 4:
		return "哲学";
		break;
	case 5:
		return "数据结构";
		break;
	case 6:
		return "天文";
		break;
	case 7:
		return "离散";
		break;
	case 8:
		return "历史";
		break;
	case 9:
		return "国语";
		break;
	}
	return"";
}


void Teacher::show_Every_Class_Score()
{
	ifstream ifs;
	ifs.open(STU_IFO_FILE, ios::in);

	int n = 0;
	cout << "请输入检索到的班级数量" << endl;
	cin >> n;

	//下标表示班级，元素表示班级人数
	MyArry<int>stu_num(n + 1);

	//统计班级所有成绩之和
	MyArry<int>sum_cla(n + 1);

	//清零
	for (MyArry<int>::iterator it = stu_num.begin(); it != stu_num.end(); it++)
		*it = 0;
	for (MyArry<int>::iterator it = sum_cla.begin(); it != sum_cla.end(); it++)
		*it = 0;

	//下标表示班级
	//哈希表的key值表示学科编号，value表示该科在该班的总分
	//由于我自己写的哈希函数是线性的，因此每一个学科只会有一个下标与其对应
	MyArry<Hashmap<int, int, HashFunc_int> > arr(n + 1);

	while (!ifs.eof())
	{
		Student tmp;
		ifs >> tmp;

		int cla = tmp.reClass();//这个学生属于的班级

		if (cla <= n)//保证不越界
		{
			stu_num[cla]++;

			for (Linklist<Subject>::iterator it = tmp.m_Subject.begin(); it != tmp.m_Subject.end(); it = it->Next)
			{
				if (arr[cla].find(it->data.Subject_Num) == -1)//不在哈希表中
					arr[cla].insert(it->data.Subject_Num, it->data.Comprehensive_Achievements);
				else arr[cla][it->data.Subject_Num] += it->data.Comprehensive_Achievements;
			}
		}
	}



	for (int i = 1; i < (int)arr.size(); i++)
	{
		if (stu_num[i] == 0)
		{
			cout << i << " 班检索失败" << endl;
			continue;
		}
		cout << i << " 班的各科平均成绩为" << endl;
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
			cout << i <<" 班检索失败" << endl;
			continue;
		}
		double n = 1.0 * (sum_cla[i] / stu_num[i]);
		cout << i << " 班的总平均成绩为 " << n / arr[i].Rsize() << endl;
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
				cout << "学号：" << tmp.reStuNum() << "  姓名：" << tmp.m_name << "  "
				<< it->data.Subject_Name << "  分数：" << it->data.Comprehensive_Achievements << " " << endl;
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
	cout << "-------------本功能支持高级排序-------------" << endl;
	cout << "-------------请选择（默认升序）-------------" << endl;
	cout << "-----------1.仅按平均成绩排序---------------" << endl;
	cout << "---2.平均分升序，平均分相同则按照学号升序---" << endl;
	cout << "---3.学分按升序，学分相同则按照平均分升序---" << endl;
	cout << "------------------0.退出--------------------" << endl;
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
		if (tmp.reStuNum() != 0)//除去最后一次无意义的读取
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
				cout << "第 " << i + 1 << " 名：" << endl;
				cout << (*it)->m_name << " 学号：" << (*it)->reStuNum() << endl;
				(*it)->show_Every_Score();
				cout << "平均分为" << endl;
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
				cout << "第 " << i + 1 << " 名：" << endl;
				cout << (*it)->m_name << " 学号：" << (*it)->reStuNum() << endl;
				(*it)->show_Every_Score();
				cout << "平均分为" << endl;
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
				cout << "第 " << i + 1 << " 名：" << endl;
				cout << (*it)->m_name << " 学号：" << (*it)->reStuNum() << endl;
				(*it)->show_Every_Score();
				cout << "平均分为" << endl;
				cout << (*it)->reSumScore() << endl;
				i++;
			}
			system("pause");
		}
		break;
		case 0:
			break;
		default:
			cout << "输入错误，请从新输入" << endl;
			system("pause");
			break;
		}
	} while (input);
	ifs.close();
}

void Teacher::find_Stu()
{
	cout << "请输入学生姓名" << endl;
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
		cout << "未找到" << endl;
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

	cout << "当前数据库为" << endl;
	cout << endl;
	
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();

	cout << endl;
	cout << "请输入待删除对象的下标编号" << endl;

	int index = 0;
	cin >> index;
	cout << endl;

	L.deleteindex(index);

	cout << "删除后数据库为" << endl;

	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();
	
	cout << endl;
	ifs.close();
	//删除文件
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

	cout << "当前数据库为" << endl;
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
		it->data.show_Student();

	int index = 0;
	cout << "请输入插入学生位置的下标" << endl;
	cin >> index;

	Student tmp;
	tmp.init_Student();
	L.insertindex(index, tmp);

	cout << "插入后数据库为" << endl;
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
	cout << "学生信息修改成功" << endl;
	return;
}

void Teacher::modify_Stu()
{
	Mystring Name;
	Mystring Pass;
	cout << "请输入待修改的学生的姓名与密码" << endl;
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
	//应该先删除掉该信息，然后再从新插入
	int flag = 0;//判断该学生是否存在
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
		cout << "该学生不存在" << endl;
		return;
	}
	ifs.close();
	L.deleteindex(index);
	Student tmp;
	cout << "请从新输入该学生信息" << endl;
	tmp.init_Student();
	L.insertindex(index, tmp);

	//删除原文件
	if (remove(STU_IFO_FILE) == 0)
		cout << "File Delete Success" << endl;

	ofstream ofs;
	ofs.open(STU_IFO_FILE, ios::out | ios::app);
	for (Linklist<Student>::iterator it = L.begin(); it != L.end(); it = it->Next)
	{
		ofs << it->data << endl;
	}

	ofs.close();
	cout << "学生信息修改成功" << endl;

}