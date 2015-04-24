/*
 * Exam.h
 *
 *  Created on: Apr 22, 2015
 *      Author: ivko
 */

#ifndef EXAM_H_
#define EXAM_H_

#include <iostream>

class Order
{
private:
	int number;
	char** items;
	int capacity;
	int current;

	void resizeItems();
	void coppy(Order const &);
public:
	Order(int number=0);
	Order(Order const&);
	Order& operator=(Order const&);
	~Order();

	friend std::ostream& operator<<(std::ostream&,Order const&);

	void clear();
	void addItem(char*);
};

class Cashier
{
private:
	char name[31];
	double income;
public:
	Cashier(char* name="<unnamed>", double income=0);
	friend std::ostream& operator <<(std::ostream&, Cashier const&);
	friend std::istream& operator >>(std::istream&, Cashier &);
	char* getName(){return  name;};
	double getIncome(){return income;};
	void setName(char *);
	void setIncome(double _income){income=_income;};
};
class Store
{
private:
	int numberOfPayDesks;
	Cashier payDesk[10];
public:
	Store(int numberOfPayDesks=1);
	friend std::ostream& operator<<(std::ostream&, Store const &);
	friend std::istream& operator>>(std::istream&, Store &);
	void setNumberOfPayDesks(int);
	double totalIncome();
	Cashier const& operator[](char*);
	double avarageIncome();
	bool operator==(Store const&);
	bool operator<(Store const&);
	bool operator>(Store const&);
	bool operator<=(Store const&);
	bool operator>=(Store const&);

};


#endif /* EXAM_H_ */
