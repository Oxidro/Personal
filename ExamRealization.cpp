/*
 * ExamRealization.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: ivko
 */

#include <iostream>
#include "Exam.h"
#include "string.h"
using namespace std;

const int DCAPACITY=10;

Order::Order(int _number)
	:number(_number), capacity(DCAPACITY), current(-1)
{
	items=new char*[capacity];
}
Order::Order(Order const& o)
	:number(o.number), capacity(o.capacity), current(o.current)
{
	coppy(o);
}
Order::~Order()
{
	clear();
	delete[] items;
}

void Order::coppy(Order const& o)
{
	items=new char*[capacity];
	int i=0;
	while(i<=current)
	{
		items[i]=new char[strlen(o.items[i])+1];
		strcpy(items[i], o.items[i]);
		i++;
	}

}

Order& Order::operator =(Order const& o)
{
	if(this!=&o)
	{
		number=o.number;
		capacity=o.capacity;
		current=o.current;
		clear();
		delete items;
		coppy(o);
	}
	return *this;
}

void Order::clear()
{
	while(current>=0)
	{
		delete[] items[current];
		current--;
	}
}


void Order::resizeItems()
{
	cout<<"Resizing..."<<endl;
	capacity+=7;
	char** items1=new char*[capacity];
	for(int i=0; i<=current;i++)
	{
		items1[i]=items[i];
	}
	delete[] items;
	items=items1;

}

void Order::addItem(char* item)
{
	if(current==capacity-1)
	{
		resizeItems();
	}
	items[++current]=new char[strlen(item)+1];
	strcpy(items[current], item);
}

ostream& operator<<(ostream& os, Order const& o)
{
	os<<"Number "<<o.number<<endl;
	for(int i=0; i<=o.current; i++)
	{
		os<<o.items[i]<<endl;
	}
	return os;
}

Cashier::Cashier(char* _name, double _income)
	:income(_income)
{
	strcpy(name, _name);
}
ostream& operator <<(ostream& os, Cashier const& c)
{
	os<<c.name<<" "<<c.income<<endl;
	return os;
}
istream& operator >>(istream& is, Cashier & c)
{
	is.getline(c.name, 31);
	is>>c.income;
	return is;
}
void Cashier::setName(char *_name){strncpy(name,_name, 31);};

Store::Store(int n)
{
	numberOfPayDesks=n;
}
ostream& operator<<(ostream& os, Store const & s)
{
	for(int i=0; i<s.numberOfPayDesks; i++)
	{
		os<<i<<") "<<s.payDesk[i]<<endl;
	}
	return os;
}
istream& operator>>(istream& is, Store & s)
{
	for(int i=0; i<s.numberOfPayDesks; i++)
	{
		char string[31];
		Cashier c;
		is.getline(string, 31);
		c.setName(string);
		double income;
		is>>income;
		c.setIncome(income);
		s.payDesk[i]=c;
		is.getline(string, 31);
	}
	return is;
}
double Store::totalIncome() const
{
	double totalIncome=0;
	for(int i=0; i<numberOfPayDesks; i++)
	{
		totalIncome+=payDesk[i].getIncome();
	}
	return totalIncome;
}
Cashier const& Store::operator[](char* name)
{
	int n=10;
	for(int i=0; i<numberOfPayDesks; i++)
	{
		if(strcmp(payDesk[i].getName() , name)==0)
			n=i;
	}
	if(n==10)
		cout<<"Not found";
	return payDesk[n];
}

double Store::avarageIncome() const
{
	return totalIncome()/numberOfPayDesks;
}

bool Store::operator==(Store const& s)
{
	return avarageIncome()==s.avarageIncome();
}









