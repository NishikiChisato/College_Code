#define _CRT_SECURE_NO_WARNINGS 1

#include "MyString.h"

Mystring::Mystring()
{
	this->str = new char[1];
	this->str[0] = '\0';
	length = 0;
}

Mystring::Mystring(const char* str)
{
	if (str == NULL)
	{
		this->str = new char[1];
		this->str[0] = '\0';
		length = 0;
	}
	else
	{
		this->length = strlen(str);
		this->str = new char[length + 1];
		strcpy(this->str, str);
		this->str[length] = '\0';
	}
}

Mystring::Mystring(const Mystring& str)
{
	if (!str.str)
	{
		this->length = 0;
		this->str = new char[1];
		*this->str = '\0';
	}
	else
	{
		this->length = str.length;
		this->str = new char[this->length + 1];
		strcpy(this->str, str.to_str());
	}
}

Mystring& Mystring::operator=(const Mystring& str)
{
	if (*str.str == '\0')
	{
		this->length = 0;
		this->str = new char[1];
		*this->str = '\0';
	}
	else
	{
		this->length = strlen(str.str);
		this->str = new char[this->length + 1];
		strcpy(this->str, str.str);
	}
	return *this;
}

Mystring& Mystring::operator+=(const Mystring& str)
{
	this->length += str.length;
	char* tmp = new char[this->length + 1];
	strcpy(tmp, this->str);
	strcat(tmp, str.str);
	delete[] this->str;
	this->str = tmp;
	return *this;
}

bool Mystring::operator==(const Mystring& str)
{
	if (this->length != str.length)
		return false;
	else return strcmp(this->str, str.str) == 0 ? true : false;
}

Mystring Mystring::operator+(const Mystring& str)
{
	Mystring ret;
	ret.length = this->length + str.length;
	ret.str = new char[ret.length];
	strcpy(ret.str, this->str);
	strcat(ret.str, str.str);
	return ret;
}

char Mystring::operator[](int index) const
{
	if (index < 0 || index >= this->length)
		return '\0';
	else return this->str[index];
}

int Mystring::size()
{
	return this->length;
}

char* Mystring::to_str()
{
	return this->str;
}

const char* Mystring::to_str() const
{
	return this->str;
}


Mystring::~Mystring()
{
	if (this->str != NULL)
	{
		delete[] this->str;
		this->str = NULL;
		this->length = 0;
	}
}

istream& operator>>(istream& cin, Mystring& str)//这个地方不能加作用域，如果加了的话就说明该函数是成员函数了
{
	//cin >> str.str;不能这么写，因为不能确定输入字符串的大小
	char tmp[1000] = "";
	cin >> tmp;
	str.length = strlen(tmp);
	str.str = new char[str.length + 1];
	strcpy(str.str, tmp);
	return cin;
}
ostream& operator<<(ostream& cout, Mystring str)
{
	cout << str.str;
	return cout;
}