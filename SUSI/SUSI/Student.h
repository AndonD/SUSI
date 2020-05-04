#pragma once

#include "String.h"
#include "Vector.cpp"
#include "Subject.h"

class Student
{
private:
	String name;
	unsigned int fn;	//faculty number
	String specialty;
	unsigned int course;
	unsigned int group;
	String status;		/* enrolled/interrupted/graduated */
	float averageGrade;
	Vector<Subject> subjects;

public:
	Student();
	Student(String _name, unsigned int _fn, String _specialty, unsigned int group);
	~Student();

	bool operator== (const Student& other);	//needed for the containsElement method in class Vector
	bool operator!= (const Student& other);
	String getName() const;

};

