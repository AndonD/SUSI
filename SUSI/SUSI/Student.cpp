#include "stdafx.h"
#include "Student.h"


Student::Student()
{
	name = "";
	fn = 0;
	specialty = "";
	group = 0;
	course = 0;
	status = "";
	averageGrade = 0;
}

Student::Student(String _name, unsigned int _fn, String _specialty, unsigned int _group)
{
	this->name = _name;
	this->fn = _fn;
	this->specialty = _specialty;
	this->group = _group;
	this->course = 1;
	this->status = "enrolled";
}

Student::~Student()
{
}


bool Student::operator== (const Student& other)
{
	return (this->fn == other.fn);
}

bool Student::operator!= (const Student& other)
{
	return (this->fn != other.fn);
}

String Student::getName() const
{
	return this->name;
}
