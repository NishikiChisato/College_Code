#pragma once
#include <iostream>
using namespace std;

template<class T>//动态扩容数组
class MyArry
{
public:

	//嵌套类型
	using value_type = T;
	using iterator = T*;
	using reference = T&;
	using size_type = size_t;

protected:
	iterator _start;
	iterator _end;
	iterator end_of_storage;

	void Capacity_Expand();

public:

	//默认构造函数
	MyArry() : _start(0), _end(0), end_of_storage(0) {};

	//有参构造，给出初始大小
	MyArry(size_type n);


	~MyArry()
	{
		if (_start)
		{
			delete[]_start;
			_end = _start;
			end_of_storage = _start;
		}
	}

	//判断是否为空
	bool empty()
	{
		return _start == _end;
	}

	//大小
	size_type size() const
	{
		return _end - _start;
	}

	//非常对象版本
	size_type size()
	{
		return _end - _start;
	}

	//容量
	size_type capacity() const
	{
		return end_of_storage - _start;
	}

	size_type capacity()
	{
		return end_of_storage - _start;
	}

	//起始迭代器
	iterator begin()
	{
		return _start;
	}

	iterator const_begin() const
	{
		return _start;
	}

	//最后一个元素的下一个位置的迭代器
	iterator end()
	{
		return _end;
	}

	iterator const_end() const
	{
		return _end;
	}

	reference operator[](int x)
	{
		return *(begin() + x);
	}

	reference operator[](int x) const
	{
		return *(begin() + x);
	}

	//返回第一个元素
	reference front()
	{
		return *begin();
	}

	//返回最后一个元素
	reference back()
	{
		return *(end() - 1);
	}

	//尾删
	void pop_back()
	{
		--_end;
	}

	//尾插
	void push_back(const T& x)
	{
		if (size() == capacity())
			Capacity_Expand();
		else;
		*_end = x;
		_end++;
	}

	//在pos位置后插入
	void insert(iterator pos, const T& x)
	{
		while (size() + 1 >= capacity)
			Capacity_Expand();

		copy_backward(pos, _end, pos + 1);
		*pos = x;
	}

	//在pos位置后插入n个elem
	void insert(iterator pos, const T& x, size_type n)
	{
		while (size() + n >= capacity())
			Capacity_Expand();
		std::copy_backward(pos, _end, pos + n);
		std::fill(pos, pos + n, x);
	}

	//清空容器
	void clear()
	{
		if (_start)
		{
			delete[]_start;
			_end = _start;
			end_of_storage = _start;
		}
	}


};


template<class T>
void MyArry<T>::Capacity_Expand()
{
	size_type old_size = size();
	size_type new_size = old_size == 0 ? 1 : (2 * old_size);
	iterator new_start = new T[new_size];
	iterator new_end = new_start + old_size;
	memmove(new_start, _start, old_size * sizeof(T));
	if (_start)
		delete[]_start;
	_start = new_start;
	_end = new_end;
	end_of_storage = _start + new_size;
}


template<class T>
MyArry<T>::MyArry(size_type n)
{
	_start = new T[n];
	_end = _start + n;
	end_of_storage = _start + (2 * n);
}
