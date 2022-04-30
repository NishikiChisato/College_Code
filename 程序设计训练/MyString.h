#pragma once
#include <iostream>
using namespace std;
class Mystring//简易string类的实现
{
	friend istream& operator>>(istream& cin, Mystring& str);//左移与右移的重载不能写成员函数，只能写全局函数
	friend ostream& operator<<(ostream& cout, Mystring str);//写在成员函数的话我一定是需要有对象才可以调用的
private:
	char* str;
	int length;
public:
	//默认构造函数
	Mystring();

	//有参构造函数
	Mystring(const char* str);

	//拷贝构造函数，要深拷贝
	Mystring(const Mystring& str);

	//重载等号
	Mystring& operator=(const Mystring& str);

	//重载+=
	Mystring& operator+=(const Mystring& str);

	//重载==
	bool operator==(const Mystring& str);

	//重载+
	Mystring operator+(const Mystring& str);

	//重载[]
	char operator[](int index) const;//对于只读的函数要加上const

	//获取大小
	int size();

	//将Mystring转化成char类型
	char* to_str();

	const char* to_str() const;

	//析构函数
	~Mystring();//这里不涉及多态，因此不用写虚析构
};