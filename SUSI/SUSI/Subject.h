#pragma once

#include "String.h"
#include "Vector.cpp"

class Subject
{
private:
	String name;
	bool isCompulsory; /* compulsory = 1 / elective = 0 */
	unsigned int course;
	float grade;

public:
	Subject();
	Subject(String _name, bool _isCompulsory, unsigned int _course);
	Subject& operator= (const Subject & other);	//Used only for 'name', 'isCompulsory' and 'course'
	~Subject();

	bool operator== (const Subject& other);	//needed for the containsElement method in class Vector
	bool operator!= (const Subject& other);

	String getName() const;
	bool getIsCompulsory() const;
	float getGrade() const;

	void setGrade(float _grade);
};

std::ostream& operator<< (std::ostream& out, Subject subject);
