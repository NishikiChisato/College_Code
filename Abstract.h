#pragma once
#include <iostream>
#include "MyString.h"

using namespace std;
class Abstract
{
public:
	virtual void openmenu() = 0;//纯虚函数，提供公共接口

	Mystring m_name;
	Mystring password;

};


