//============================================================================
// Name        : Exam.cpp
// Author      : Ivailo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Exam.h"
using namespace std;

int main() {
	Cashier c("gosho", 10);
	Cashier c1;
	c1.setName("qwertyuiopqwertyuiopqwertyuiopasdfghjkl");
	//cin>>c1;
	cout<<c1;
	return 0;
}
