#pragma once
#include <iostream>
using namespace std;

template<class T>
class Linklist//������ģ��Ĵ���
{
public:

	class LinkNode//�����ڵ�ڵ�
	{
	public:
		T data;
		LinkNode* Next;
		LinkNode();

		LinkNode(T data);

	};

	//�޲ι���
	Linklist();

	//Ƕ�����ͣ����������
	using iterator = LinkNode*;


	//��������ʵ��

	//��ӡ����
	void printLinklist();


	//β��
	void addtail(T data);


	//ͷ��
	void addhead(T data);


	//ɾ���±�Ϊindex�Ľڵ㣬�±��0��ʼ
	void deleteindex(int index);


	//��index������ڵ㣬index��0��ʼ
	//���indexΪ0����Ϊͷ�壬���index���������С����С��0����ֱ�ӷ���
	void insertindex(int index, typename T data);
	

	//��ȡ�����С
	int size();

	void clear();

	//��ʼ������
	iterator begin();

	iterator begin() const;

	//������������ָ�����һ���ڵ����һ���ڵ㣨ʵ����ָ��գ�
	iterator end();

	iterator end() const;


private:
	int _size;//�����С
	LinkNode* dummyhead;//����ͷ�ڵ㣬���ڴ�������
};

template<class T>
Linklist<T>::LinkNode::LinkNode()
{
	this->Next = NULL;
}

template<class T>
Linklist<T>::LinkNode::LinkNode(T data)//д������һ������Ϊ����Ҫ���߱�����T��һ��ģ�����������һ����ģ��ĳ�Ա��������ʵ��
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
	tmp->Next = dummyhead->Next;//����ͷ�ڵ���Ȼ��ָ�룬�����ָ��ָ��һ���ڵ㣬�ýڵ㲻�洢����
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
	cur->Next = tmp;//���ָ��ָ�����һ���ڵ㣬����Ҫ�ı��������ڵ��ָ�����ֵ
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
