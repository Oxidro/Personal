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
	Store s(2);
	cin>>s;
	cout<<s;
	cout<<s.totalIncome();
	cout<<s["pesho"];
	return 0;
}
