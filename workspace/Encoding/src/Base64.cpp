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
char byte[9];
char binary[25];

void append(unsigned char* ucp, unsigned char uc)
{
	ucp[strlen((char*)ucp)]=uc;
}

void Base::push(unsigned char uc)
{
	encoded[++current]=uc;
}

void Base::coppyEncoded(unsigned char const * _encoded)
{
	unsigned char *encoded1=new unsigned char[capacity];
	for(int i=0; i<=current; i++)
	{
		encoded1[i]=_encoded[i];
	}
	delete[] encoded;
	encoded=encoded1;
}
/*
void Base::resize()
{
	capacity*=2;
	coppyEncoded(encoded);
}*/

void Base::convertToBinary(int num, int byteLenght)
{
	for(int i=byteLenght-1; i>=0; i--)
	{
		byte[i]=num%2+48;
		num/=2;
	}
	byte[byteLenght]='\0';
}
int Base::convertToInt(int byteLenght)
{
	int num=0;
	for(int i=0; i<byteLenght; i++)
	{
		num+=(byte[i]-48)*pow(2, byteLenght-1-i);
	}
	return num;
}
unsigned char Base::getEncodedChar(int byte)
{
	if(byte==62) return '+';
	if(byte==63) return '/';
	if(byte>=0 && byte <=25)	return byte+65;
	if(byte>=26 && byte <=51)	return byte-26+97;
	if(byte>=52 && byte <=61)	return byte-52+48;
	return byte;
}
unsigned char Base::getDecodedChar(int byte)
{
	if(byte=='+') return 62;
	if(byte=='/') return 63;
	if(byte>=65 && byte <=90)	return byte-65;
	if(byte>=97 && byte <=122)	return byte+26-97;
	if(byte>=48	 && byte <=57)	return byte+52-48;
	return byte;
}
void Base::getDecodedByte(int n, unsigned char* decoded)
{
	for(int i=0; i<n; i++)
	{
		byte[i%8]=binary[i];
		if((i+1)%8==0)
		{
			append(decoded, (convertToInt(8)));
		}
	}
}
void Base::getEncodedByte(int n)
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
		byte[j%6]=binary[j];
		if((j+1)%6==0)
		{
			byte[6]=0;
			push(getEncodedChar(convertToInt(6)));
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
void Base::encode(unsigned char* arr, int len)
{
	delete[] encoded;
	capacity=len+(len/3);
	current=-1;
	encoded=new unsigned char[capacity];
	for(int i=0; i<=len; i++)
	{

		if(i%3==0 && i!=0)
		{
			getEncodedByte(24);
		}
		if(i%3==0 && i<len)
		{
			convertToBinary(arr[i], 8);
			strcpy(binary, byte);
		}
		if(i%3!=0 && i<len)
		{
			convertToBinary(arr[i], 8);
			strcat(binary, byte);
		}
		if(i==len-1)
		{
			if(len%3==1)
			{
				getEncodedByte(12);
			}
			else if(len%3==2)
			{
				getEncodedByte(18);
			}
		}
	}
}

unsigned char* Base::decode()
{
	return decode(0, current);
}

unsigned char* Base::decode(int start, int finish)
{
	unsigned char* decoded=new unsigned char [(current*3)/4];
	for(int i=start; i<=finish; i++)
	{
		if(encoded[i]=='=' && i==current)
		{
			getDecodedByte(16, decoded);
		}
		if(encoded[i]=='=' && i==current-1)
		{
			getDecodedByte(8, decoded);
		}
		if(i%4==0 && i!=0)
		{
			getDecodedByte(24, decoded);
		}
		if(i%4==0 && i<current)
		{
			convertToBinary(getDecodedChar(encoded[i]), 6);
			strcpy(binary, byte);
		}
		if(i%4!=0 && i<current)
		{
			convertToBinary(getDecodedChar(encoded[i]), 6);
			strcat(binary, byte);
		}
	}
	return decoded;
}
Base::Base()
	:capacity(DEFAULTCAPACITY), current(-1)
{
	encoded=new unsigned char[capacity];
}

Base::Base(unsigned char *arr, int n)
	:capacity(DEFAULTCAPACITY), current(-1)
{
	encoded=new unsigned char[capacity];
	encode(arr, n);
}
Base::Base(Base const& b)
{
	capacity=b.capacity;
	current=b.current;
	encoded=new unsigned char[capacity];
	coppyEncoded(b.encoded);
}
Base& Base::operator=(Base const& b)
{
	if(this!=&b)
	{
		capacity=b.capacity;
		current=b.current;
		encoded=new unsigned char[capacity];
		coppyEncoded(b.encoded);
	}
	return *this;
}
Base::~Base()
{
	delete[] encoded;
}

ostream& operator<<(ostream& os, Base const& b)
{
	for(int i=0; i<=b.current; i++)
	{
		os<<b.encoded[i];
	}
	return os;
}

unsigned char Base::operator[](int n)
{
	int s=(n/3)*4;
	return decode(s,s+4)[n%3];
}

Base Base::operator +(Base const& b)
{
	Base c=*this;
	c+=b;
	return c;
}

Base& Base::operator +=(Base const& b)
{
	unsigned char *encoded1=new unsigned char[current+b.current];
	for(int i=0; i<=current; i++)
	{
		encoded1[i]=encoded[i];
	}
	for(int i=0; i<=b.current; i++)
	{
		encoded1[current+i+1]=b.encoded[i];
	}
	current+=b.current+1;
	delete[] encoded;
	encoded=encoded1;
	return *this;
}

void Base::deleteSomeElements(int start, int number)
{
	if(start>=0 && start<=current && (start+number)<=current+1)
	{
		for(int i=start; i<=start+number; i++)
		{
			encoded[start]=encoded[start+number];
		}
		current-=number;
	}
}

unsigned char* Base::operator()(int start, int lenght)
{
	unsigned char* encodedSubArray=new unsigned char[lenght];
	for(int i=0; i<=lenght; i++)
	{
		encodedSubArray[i]=encoded[start+i];
	}
	return encodedSubArray;
}

bool subArray(Base const& b1, Base const& b2)
{
	int i=0, j=0;
	while(i<=b1.current && j<=b2.current)
	{
		if(b1.encoded[i]==b2.encoded[j])
		{
			j++;
		}
		else if(b1.encoded[i]!=b2.encoded[j])
		{
			j=0;
			if(b1.encoded[i]==b2.encoded[j])
			{
				j++;
			}
		}
		i++;
	}
	if(j==b2.current+1)
		return true;
	return false;
}

bool operator<(Base const& a, Base const& b)
{
	if(a.current==b.current)
		return false;
	if(subArray(b, a))
		return true;
	return false;
}

bool operator>(Base const& a, Base const& b)
{
	if(a.current==b.current)
		return false;
	if(subArray(a, b))
		return true;
	return false;
}

bool operator<=(Base const& a, Base const&b)
{
	if(a.current!=b.current)
		return false;
	if(subArray(b, a))
		return true;
	return false;
}

bool operator>=(Base const& a, Base const&b)
{
	if(a.current!=b.current)
		return false;
	if(subArray(a, b))
		return true;
	return false;
}

/*
istream& operator>>(istream& is, Base const& b)
{
	char buffer[31]; 						// Правим буфер в който ще четем
	is.get(buffer,31); 						// Четем буфера
	int buffered=strlen(buffer); 			// Инициализираме променлива която да ни казва колко
	delete[] P.name;						// Освобождаваме старата памет заделена за име
	P.name=new char[buffered+1];			// символа сме прочели до сега и заделяме памет за толкова
	strcpy(P.name,buffer);					// копираме буфера в заделеното място
	while (strlen(buffer)>=30){				// Докато в буфера имамем записани максимум байта (30)
		is.get(buffer,30);						// продължаваме да четем в буфера
		buffered+=strlen(buffer);				// Уевеличаваме броя на прочетените съмволи
		char* name1= new char[buffered+1];		// с дължината на буфера и заделяме толкова памет
		strcpy(name1,P.name);					// В новозаделента памет кпираме досега почетената част от името
		strcat(name1,buffer);					// и към него конкатенираме тукощо буферираната част
		delete[] P.name;						// Освобождаваме старата памет
		P.name=name1;							// и на нейно място записваме новополученото име
	}
	return is;
}*/




