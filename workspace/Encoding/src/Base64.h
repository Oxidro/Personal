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

	void convertToBinary(int);
	int convertToInt(char*);
	unsigned char getByte(int);
	void encode(char*);
	void resize();
	void push(unsigned char);
	void coppy(unsigned char*);
	void getNewByte(int);

	Base& add(char*);

	Base();
	Base(char *);
	Base(Base const&);
	Base& operator=(Base const&);
	~Base();

	friend std::ostream& operator<<(std::ostream&, Base const&);
	friend std::istream& operator>>(std::ostream&, Base const&);
};



#endif /* BASE64_H_ */
