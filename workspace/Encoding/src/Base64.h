/*
 * Base64.h
 *
 *  Created on: Apr 29, 2015
 *      Author: ivko
 */

#ifndef BASE64_H_
#define BASE64_H_

#include <iostream>

class Base
{
public:
	unsigned char *encoded;
	int capacity;
	int current;
public:

	void convertToBinary(int, int);
	int convertToInt(int);

	unsigned char getEncodedChar(int);
	unsigned char getDecodedChar(int);

	void encode(unsigned char*, int);
	unsigned char* decode(int, int);
	unsigned char* decode();

	void getEncodedByte(int);
	void getDecodedByte(int, unsigned char*);

	void push(unsigned char);
	void coppyEncoded(unsigned char const*);


	Base();
	Base(unsigned char *, int);
	Base(Base const&);
	Base& operator=(Base const&);
	~Base();

	unsigned char operator[](int);
	Base operator+(Base const&);
	Base& operator+=(Base const&);
	unsigned char* operator()(int, int);

	void deleteSomeElements(int, int);
	friend bool subArray(Base const&, Base const&);

	friend std::ostream& operator<<(std::ostream&, Base const&);
	friend std::istream& operator>>(std::ostream&, Base const&);
	friend bool operator<(Base const&, Base const&);
	friend bool operator>(Base const&, Base const&);
	friend bool operator<=(Base const&, Base const&);
	friend bool operator>=(Base const&, Base const&);
};

#endif /* BASE64_H_ */
