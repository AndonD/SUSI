#pragma once

#include "String.h"
#include "Vector.cpp"

class Subject
{
private:
	String name;
	bool isCompulsory; /* compulsory = 1 / elective = 0 */
	unsigned int course;
	Vector<float> grades;

public:
	Subject();
	Subject(String _name, bool _isCompulsory, unsigned int _course);
	~Subject();

	bool operator== (const Subject& other);	//needed for the containsElement method in class Vector
	bool operator!= (const Subject& other);
	String getName() const;
};

std::ostream& operator<< (std::ostream& out, Subject subject);