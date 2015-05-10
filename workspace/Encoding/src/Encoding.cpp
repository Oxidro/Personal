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
	char *str="Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
	unsigned char* byteArray=(unsigned char*) str;
	Base b(byteArray, 269);
	/*
	ifstream sourceFile;
	sourceFile.open("Test.txt");

	// Destination
	ofstream destinationFile;
	destinationFile.open("Test2.txt");

	char buffer[101];
	while(!sourceFile.eof())
	{
		sourceFile.read(buffer, 101, );
		b.encode(buffer);
	}
	cout<<b;
	destinationFile<<b;*/
	cout<<b<<endl;
	cout<<b.decode()<<endl;
	cout<<b[0]<<endl;
	b.deleteSomeElements(3,357);
	cout<<b<<endl;
	cout<<"------------------"<<endl;
	Base a((unsigned char*)"abc", 3);
	Base c((unsigned char*)"def", 3);
	cout<<a<<endl;
	cout<<c<<endl;
	a+=c;
	cout<<a<<endl;
	cout<<c<<endl;
	if(c>=c)
		cout<<"YAAA";
	return 0;
}
