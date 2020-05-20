#include "stdafx.h"
#include "Subject.h"


Subject::Subject()
{
	name = "";
	course = 0;
	isCompulsory = false;
	grade = 2;	//default grade
}

Subject::Subject(String _name, bool _isCompulsory, unsigned int _course)
{
	this->name = _name;
	this->course = _course;
	this->isCompulsory = _isCompulsory;
	this->grade = 2;	//default grade
}

Subject& Subject::operator=(const Subject & other)
{
	if (this != &other)
	{
		this->name = other.name;
		this->course = other.course;
		this->isCompulsory = other.isCompulsory;
		this->grade = other.grade;
	}

	return *this;
}

Subject::~Subject()
{
}


bool Subject::operator== (const Subject & other)
{
	return ( (this->name == other.name) && (this->course == other.course) );
}

bool Subject::operator!= (const Subject & other)
{
	return ((this->name != other.name) || (this->course != other.course));
}

String Subject::getName() const
{
	return this->name;
}

bool Subject::getIsCompulsory() const
{
	return this->isCompulsory;
}

float Subject::getGrade() const
{
	return this->grade;
}

void Subject::setGrade(float _grade)
{
	this->grade = _grade;
}


std::ostream& operator<< (std::ostream& out, Subject subject)
{
	out << subject.getName();
	return out;
}