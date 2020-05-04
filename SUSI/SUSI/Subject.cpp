#include "stdafx.h"
#include "Subject.h"


Subject::Subject()
{
	name = "";
	course = 0;
	isCompulsory = false;
}

Subject::Subject(String _name, bool _isCompulsory, unsigned int _course)
{
	this->name = _name;
	this->course = _course;
	this->isCompulsory = _isCompulsory;
}

Subject::~Subject()
{
}


bool Subject::operator== (const Subject& other)
{
	return ( (this->name == other.name) && (this->isCompulsory == other.isCompulsory) && (this->course == other.course) );
}

bool Subject::operator!= (const Subject& other)
{
	return (this->name != other.name);
}

String Subject::getName() const
{
	return this->name;
}


std::ostream& operator<< (std::ostream& out, Subject subject)
{
	out << subject.getName();
	return out;
}