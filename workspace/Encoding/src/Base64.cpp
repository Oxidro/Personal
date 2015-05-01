/*
 * Base64.cpp
 *
 *  Created on: Apr 29, 2015
 *      Author: ivko
 */
#include <iostream>
#include "string.h"
#include "math.h"
#include "Base64.h"
using namespace std;

const int DEFAULTCAPACITY=30;
const int DEFAULTCURRENT=0;
char oldByte[9];
char binary[25];
char newByte[7];

void Base::push(unsigned char uc)
{
	if(current==capacity) resize();
	encoded[current++]=uc;
}

void Base::coppy(unsigned char * _encoded)
{
	unsigned char *encoded1=new unsigned char[capacity];
	for(int i=0; i<8; i++)
	{
		encoded1[i]=_encoded[i];
	}
	delete[] encoded;
	encoded=encoded1;
}

void Base::resize()
{
	capacity+=DEFAULTCAPACITY;
	coppy(encoded);
}


void Base::convertToBinary(int num)
{
	oldByte[0]=5;
	for(int i=7; i>=0; i--)
	{
		oldByte[i]=num%2+48;
		num/=2;
	}
	oldByte[8]='\0';
}
int Base::convertToInt(char* byte)
{
	int num=0;
	for(int i=0; i<6; i++)
	{
		num+=(byte[i]-48)*pow(2, 5-i);
	}
	return num;
}
unsigned char Base::getByte(int byte)
{
	if(byte==62) return '+';
	if(byte==63) return '/';
	if(byte>=0 && byte <=25)	return byte+65;
	if(byte>=26 && byte <=51)	return byte-26+97;
	if(byte>=52 && byte <=61)	return byte-52+48;
	return byte;
}

void Base::getNewByte(int n)
{
	if(n==12)
	{
		binary[8]=48;binary[9]=48;binary[10]=48;binary[11]=48;binary[12]=0;
	}
	if(n==18)
	{
		binary[16]=48;binary[17]=48;binary[18]=0;
	}
	for(int j=0; j<n; j++)
	{
		newByte[j%6]=binary[j];
		if((j+1)%6==0)
		{
			push(getByte(convertToInt(newByte)));
		}
	}
	if(n==12)
	{
		push('=');push('=');
	}
	if(n==18)
	{
		push('=');
	}
}
void Base::encode(char* arr)
{
	int len=strlen(arr);
	for(int i=0; i<=len; i++)
	{

		if(i%3==0 && i!=0)
		{
			getNewByte(24);
		}
		if(i%3==0 && i<len)
		{
			convertToBinary(arr[i]);
			strcpy(binary, oldByte);
		}
		if(i%3!=0 && i<len)
		{
			convertToBinary(arr[i]);
			strcat(binary, oldByte);
		}
		if(i==len-1)
		{
			if(len%3==1)
			{
				getNewByte(12);
			}
			else if(len%3==2)
			{
				getNewByte(18);
			}
		}
	}
}

Base::Base()
	:capacity(DEFAULTCAPACITY), current(DEFAULTCURRENT)
{
	encoded=new unsigned char[capacity];
}

Base::Base(char *arr)
	:capacity(DEFAULTCAPACITY), current(DEFAULTCURRENT)
{
	encoded=new unsigned char[capacity];
	encode(arr);

}
Base::Base(Base const& b)
	:capacity(b.capacity), current(b.current)
{
	coppy(b.encoded);

}
Base& Base::operator=(Base const& b)
{
	if(this!=&b)
	{
		capacity=b.capacity;
		current=b.current;
		coppy(b.encoded);
	}
	return *this;
}
Base::~Base()
{
	delete encoded;
}

Base& Base::add(char* str)
{

}

ostream& operator<<(ostream& os, Base const& b)
{
	os<<b.encoded;
	return os;
}
istream& operator>>(istream& is, Base const& b)
{
	is>>b.encoded;
	return is;
}



