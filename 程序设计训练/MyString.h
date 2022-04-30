#pragma once
#include <iostream>
using namespace std;
class Mystring//����string���ʵ��
{
	friend istream& operator>>(istream& cin, Mystring& str);//���������Ƶ����ز���д��Ա������ֻ��дȫ�ֺ���
	friend ostream& operator<<(ostream& cout, Mystring str);//д�ڳ�Ա�����Ļ���һ������Ҫ�ж���ſ��Ե��õ�
private:
	char* str;
	int length;
public:
	//Ĭ�Ϲ��캯��
	Mystring();

	//�вι��캯��
	Mystring(const char* str);

	//�������캯����Ҫ���
	Mystring(const Mystring& str);

	//���صȺ�
	Mystring& operator=(const Mystring& str);

	//����+=
	Mystring& operator+=(const Mystring& str);

	//����==
	bool operator==(const Mystring& str);

	//����+
	Mystring operator+(const Mystring& str);

	//����[]
	char operator[](int index) const;//����ֻ���ĺ���Ҫ����const

	//��ȡ��С
	int size();

	//��Mystringת����char����
	char* to_str();

	const char* to_str() const;

	//��������
	~Mystring();//���ﲻ�漰��̬����˲���д������
};