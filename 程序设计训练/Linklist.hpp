#pragma once
#include <iostream>
using namespace std;

template<class T>
class Linklist//链表类模板的创建
{
public:

	class LinkNode//创建节点节点
	{
	public:
		T data;
		LinkNode* Next;
		LinkNode();

		LinkNode(T data);

	};

	//无参构造
	Linklist();

	//嵌套类型：链表迭代器
	using iterator = LinkNode*;


	//基本函数实现

	//打印链表
	void printLinklist();


	//尾插
	void addtail(T data);


	//头插
	void addhead(T data);


	//删除下标为index的节点，下标从0开始
	void deleteindex(int index);


	//在index处插入节点，index从0开始
	//如果index为0，则为头插，如果index大于链表大小或者小于0，则直接返回
	void insertindex(int index, typename T data);
	

	//获取链表大小
	int size();

	void clear();

	//起始迭代器
	iterator begin();

	iterator begin() const;

	//结束迭代器，指向最后一个节点的下一个节点（实际上指向空）
	iterator end();

	iterator end() const;


private:
	int _size;//链表大小
	LinkNode* dummyhead;//虚拟头节点，便于处理链表
};

template<class T>
Linklist<T>::LinkNode::LinkNode()
{
	this->Next = NULL;
}

template<class T>
Linklist<T>::LinkNode::LinkNode(T data)//写上面这一行是因为我需要告诉编译器T是一个模板参数，这是一个类模板的成员函数类外实现
{
	this->data = data;
	this->Next = NULL;
}

template<class T>
Linklist<T>::Linklist()
{
	this->_size = 0;
	this->dummyhead = new LinkNode();
}

template<class T>
void Linklist<T>::clear()
{
	Linklist<T>::LinkNode* cur = dummyhead;
	while (cur->Next != NULL)
	{
		Linklist<T>::LinkNode* tmp = cur->Next;
		delete cur;
		cur = tmp->Next;
	}
	return;
}

template<class T>
void Linklist<T>::printLinklist()
{
	LinkNode* cur = dummyhead;
	while (cur->Next != NULL)
	{
		cout << cur->Next->data << " ";
		cur = cur->Next;
	}
	cout << endl;
}

template<class T>
void Linklist<T>::addtail(T data)
{
	LinkNode* cur = dummyhead;
	while (cur->Next != NULL)
		cur = cur->Next;
	LinkNode* tmp = new LinkNode(data);
	cur->Next = tmp;
	_size++;
}

template<class T>
void Linklist<T>::deleteindex(int index)
{
	if (index < 0 || index >= size())
		return;
	LinkNode* cur = dummyhead;
	while (index--)
		cur = cur->Next;
	LinkNode* tmp = cur->Next;
	cur->Next = cur->Next->Next;
	delete tmp;
	_size--;
}

template<class T>
void Linklist<T>::addhead(T data)
{
	Linklist<T>::LinkNode* tmp = new LinkNode(data);
	tmp->Next = dummyhead->Next;//虚拟头节点虽然是指针，但这个指针指向一个节点，该节点不存储数据
	dummyhead->Next = tmp;
	_size++;
}

template<class T>
void Linklist<T>::insertindex(int index, T data)
{
	if (index < 0 || index > size())
		return;
	typename Linklist<T>::LinkNode* cur = dummyhead;
	typename Linklist<T>::LinkNode* tmp = new LinkNode(data);
	for (int i = 0; i < index; i++)
		cur = cur->Next;
	tmp->Next = cur->Next;
	cur->Next = tmp;//这个指针指向的是一个节点，我需要改变的是这个节点的指针域的值
	_size++;
}

template<class T>
int Linklist<T>::size()
{
	return this->_size;
}

template<class T>
typename Linklist<T>::iterator Linklist<T>::begin()
{
	return dummyhead->Next;
}

template<class T>
typename Linklist<T>::iterator Linklist<T>::begin() const
{
	return dummyhead->Next;
}

template<class T>
typename Linklist<T>::iterator Linklist<T>::end()
{
	Linklist<T>::LinkNode* cur = dummyhead;
	while (cur != NULL)
	{
		cur = cur->Next;
	}
	return cur;
}

template<class T>
typename Linklist<T>::iterator Linklist<T>::end() const
{
	Linklist<T>::LinkNode* cur = dummyhead;
	while (cur != NULL)
	{
		cur = cur->Next;
	}
	return cur;
}
