#pragma once

#include "Name_Defined.h"
#include <iostream>
using namespace std;

class HashFunc_int
{
public:
	int operator()(const int& key)
	{
		return 3 * key + 1;
	}
};

template<typename Key, typename Value>
class HashNode
{
public:
	Key key;
	Value value;
	HashNode* next;
	HashNode(Key _key, Value _value) : key(_key), value(_value), next(NULL) {};
};

//简单实现哈希表
//本哈希表中的key值可以重复，删除时会删除掉所有相同的key值
template<typename Key, typename Value, typename HashFunc>
class Hashmap
{
private:
	int size;//大小
	HashNode<Key, Value>** table;//数组，每个元素都是一个链表
	HashFunc Hash;//自定义哈希函数
	Value valuenull;//用于引用时返回-1
public:
	
	using iterator = HashNode<Key, Value>**;

	Hashmap();//默认构造，默认开30个空间

	Hashmap(const int& size);//有参构造

	~Hashmap();//析构

	int Rsize();//返回实际大小

	bool insert(const Key& key, const Value& value);//插入

	bool del(const Key& key);//删除

	Value& find(const Key& key);//查找

	Value& operator[](const Key& key);

	iterator begin();

	iterator end();

	void print();//打印

};

template<typename Key, typename Value, typename HashFunc>
typename Hashmap<Key, Value, HashFunc>::iterator Hashmap<Key, Value, HashFunc>::begin()
{
	return this->table;
}

template<typename Key, typename Value, typename HashFunc>
typename Hashmap<Key, Value, HashFunc>::iterator Hashmap<Key, Value, HashFunc>::end()
{
	return this->table + this->size;
}

template<typename Key, typename Value, typename HashFunc>
int Hashmap<Key, Value, HashFunc>::Rsize()
{
	int n = 0;
	for (int i = 0; i < this->size; i++)
	{
		if (table[i] != NULL)
			n++;
	}
	return n;
}

template<typename Key, typename Value, typename HashFunc>
Hashmap<Key, Value, HashFunc>::Hashmap(const int& size) : Hash()
{
	this->size = size;
	this->valuenull = -1;
	this->table = new HashNode<Key, Value> *[size];
	for (int i = 0; i < size; i++)
		table[i] = NULL;
}

template<typename Key, typename Value, typename HashFunc>
Hashmap<Key, Value, HashFunc>::Hashmap() : Hash()
{
	this->size = HASHTABLE_SIZE;
	this->valuenull = -1;
	this->table = new HashNode<Key, Value> *[this->size];
	for (int i = 0; i < this->size; i++)
		table[i] = NULL;
}

template<typename Key, typename Value, typename HashFunc>
Hashmap<Key, Value, HashFunc>::~Hashmap()
{
	for (int i = 0; i < this->size; i++)
	{
		HashNode<Key, Value>* cur = table[i];
		while (cur)
		{
			HashNode<Key, Value>* pre = cur;
			cur = cur->next;
			delete pre;
		}
	}
	delete this->table;
}

template<typename Key, typename Value, typename HashFunc>
bool Hashmap<Key, Value, HashFunc>::insert(const Key& key, const Value& value)
{
	int index = Hash(key) % this->size;
	HashNode<Key, Value>* cur = table[index];
	HashNode<Key, Value>* tmp = new HashNode<Key, Value>(key, value);
	tmp->next = cur;//用前插
	table[index] = tmp;
	return true;
}

template<typename Key, typename Value, typename HashFunc>
bool Hashmap<Key, Value, HashFunc>::del(const Key& key)//
{
	int index = Hash(key) % this->size;
	HashNode<Key, Value>* cur = table[index];
	if (cur == NULL)
		return false;
	else if (cur->key == key)
	{
		table[index] = cur->next;
		delete cur;
	}
	else
	{
		HashNode<Key, Value>* pre = cur;
		cur = cur->next;
		while (cur)
		{
			if (cur->key == key)
			{
				pre->next = cur->next;
				delete cur;
				cur = NULL;
				return true;
			}
			else
			{
				cur = cur->next;
				pre = pre->next;
			}
		}
	}
	return true;
}

template<typename Key, typename Value, typename HashFunc>
Value& Hashmap<Key, Value, HashFunc>::find(const Key& key)
{
	int index = Hash(key);
	HashNode<Key, Value>* cur = table[index];
	if (cur == NULL)
		return valuenull;
	else
		while (cur)
		{
			if (cur->key == key)
				return cur->value;
			else
				cur = cur->next;
		}
	return valuenull;
}

template<typename Key, typename Value, typename HashFunc>
void Hashmap<Key, Value, HashFunc>::print()
{
	for (int i = 0; i < this->size; i++)
	{
		HashNode<Key, Value>* cur = table[i];
		while (cur)
		{
			cout << cur->key << "---" << cur->value << endl;
			cur = cur->next;
		}

	}
}

template<typename Key, typename Value, typename HashFunc>
Value& Hashmap<Key, Value, HashFunc>::operator[](const Key& key)
{
	return find(key);
}