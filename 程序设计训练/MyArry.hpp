#pragma once
#include <iostream>
using namespace std;

template<class T>//��̬��������
class MyArry
{
public:

	//Ƕ������
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

	//Ĭ�Ϲ��캯��
	MyArry() : _start(0), _end(0), end_of_storage(0) {};

	//�вι��죬������ʼ��С
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

	//�ж��Ƿ�Ϊ��
	bool empty()
	{
		return _start == _end;
	}

	//��С
	size_type size() const
	{
		return _end - _start;
	}

	//�ǳ�����汾
	size_type size()
	{
		return _end - _start;
	}

	//����
	size_type capacity() const
	{
		return end_of_storage - _start;
	}

	size_type capacity()
	{
		return end_of_storage - _start;
	}

	//��ʼ������
	iterator begin()
	{
		return _start;
	}

	iterator const_begin() const
	{
		return _start;
	}

	//���һ��Ԫ�ص���һ��λ�õĵ�����
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

	//���ص�һ��Ԫ��
	reference front()
	{
		return *begin();
	}

	//�������һ��Ԫ��
	reference back()
	{
		return *(end() - 1);
	}

	//βɾ
	void pop_back()
	{
		--_end;
	}

	//β��
	void push_back(const T& x)
	{
		if (size() == capacity())
			Capacity_Expand();
		else;
		*_end = x;
		_end++;
	}

	//��posλ�ú����
	void insert(iterator pos, const T& x)
	{
		while (size() + 1 >= capacity)
			Capacity_Expand();

		copy_backward(pos, _end, pos + 1);
		*pos = x;
	}

	//��posλ�ú����n��elem
	void insert(iterator pos, const T& x, size_type n)
	{
		while (size() + n >= capacity())
			Capacity_Expand();
		std::copy_backward(pos, _end, pos + n);
		std::fill(pos, pos + n, x);
	}

	//�������
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
