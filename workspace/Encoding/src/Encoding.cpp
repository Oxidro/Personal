//============================================================================
// Name        : Encoding.cpp
// Author      : Ivailo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "string.h"
#include "Base64.h"
using namespace std;

int main()
{
	Base b;
	ifstream sourceFile;
	sourceFile.open("Test.txt");
	char line[61];
	sourceFile.get(line, 61);
	cout<<line<<endl;
	b.encode(line);
	//cout<<b<<endl;
	sourceFile.close();
	ofstream destinationFile;
	destinationFile.open("Test2.txt");
	destinationFile<<b;
	destinationFile.close();
	return 0;
}
