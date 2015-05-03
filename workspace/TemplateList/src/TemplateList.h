/*
 * TemplateList.h
 *
 *  Created on: May 3, 2015
 *      Author: ivko
 */

#ifndef TEMPLATELIST_H_
#define TEMPLATELIST_H_

template <typename QQ>
class TemplateList
{
private:
	QQ *data;
	int capacity;
	int current;

	void resize();
	void coppy(TemplateList const&);
	void shift(int);
public:
	TemplateList();
	TemplateList(TemplateList const&);
	TemplateList& operator=(TemplateList const&);
	~TemplateList();

	void push(QQ);
	void deleteElement(int);
	void print();
	TemplateList& operator+=(QQ);
	QQ operator[](int);
};

#endif /* TEMPLATELIST_H_ */
