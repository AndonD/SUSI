#pragma once

#include "String.h"
#include "Vector.cpp"

class Subject
{
private:
	String name;
	bool isCompulsory;
	unsigned int course;
	float grade;

public:
	Subject();
	//Subject(const Subject &other);
	Subject(String _name, bool _isCompulsory, unsigned int _course);
	Subject& operator= (const Subject &other);
	~Subject();

	bool operator== (const Subject &other);
	bool operator!= (const Subject &other);

	String getName() const;
	bool getIsCompulsory() const;
	float getGrade() const;

	void setGrade(float _grade);
};

std::ostream& operator<< (std::ostream &out, Subject subject);
