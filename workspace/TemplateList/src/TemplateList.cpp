//============================================================================
// Name        : TemplateList.cpp
// Author      : Ivailo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TemplateList.h"
using namespace std;
const int DEFAULTCAPACITY=10;

template <typename QQ>
void TemplateList<QQ>::coppy(TemplateList<QQ> const& list)
{
	QQ *data1=new QQ[capacity];
	for(int i=0; i<current; i++)
	{
		data1[i]=list.data[i];
	}
	delete[] data;
	data=data1;
}
template <typename QQ>
TemplateList<QQ>::TemplateList()
	:capacity(DEFAULTCAPACITY), current(0)
{
	data=new QQ[capacity];
}
template <typename QQ>
TemplateList<QQ>::TemplateList(TemplateList<QQ> const& list)
	:capacity(list.capacity), current(list.current)
{
	coppy(list);
}
template <typename QQ>
TemplateList<QQ>& TemplateList<QQ>::operator=(TemplateList<QQ> const& list)
{
	if(this!=&list)
	{
		capacity=list.capacity;
		current=list.current;
		coppy(list);
	}
	return *this;
}
template <typename QQ>
TemplateList<QQ>::~TemplateList()
{
	delete[] data;
}
template <typename QQ>
void TemplateList<QQ>::resize()
{
	capacity+=DEFAULTCAPACITY;
	coppy(*this);
}
template <typename QQ>
void TemplateList<QQ>::shift(int n)
{
	for(int i=n+1; i<current; i++)
	{
		data[i-1]=data[i];
	}
	current-=1;
}
template <typename QQ>
void TemplateList<QQ>::push(QQ element)
{
	if(current==capacity)
		resize();
	data[current++]=element;
}
template <typename QQ>
void TemplateList<QQ>::deleteElement(int n)
{
	shift(n);
}
template <typename QQ>
void TemplateList<QQ>::print()
{
	for(int i=0; i<current; i++)
	{
		cout<<data[i]<<endl;
	}
}
template <typename QQ>
QQ TemplateList<QQ>::operator[](int n)
{
	return data[n];
}
template<typename QQ>
TemplateList<QQ>& TemplateList<QQ>::operator+=(QQ element)
{
	push(element);
	return *this;
}

int main()
{
	TemplateList<int> list;
	list.print();
	for(int i=0; i<=12; i++)
	{
		list.push(i);
	}
	list+=13;
	list.print();
	cout<<list[9];
	list.deleteElement(9);
	list.print();
	return 0;
}
//yo
