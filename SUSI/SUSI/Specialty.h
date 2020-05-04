#pragma once

#include "String.h"
#include "Vector.cpp"
#include "Student.h"
#include "Subject.h"

class Specialty
{
private:
	String name;
	Vector<Student> students;
	Vector<Subject> subjects;

public:
	Specialty();
	Specialty(String _name);
	~Specialty();
	
	bool isRegisteredSubject(const Subject& subject);
	bool isRegisteredStudent(const Student& student);

	bool operator== (const Specialty& other);
	bool operator!= (const Specialty& other);
	String getName() const;

	void add_subject(const Subject& subjectToAdd);
	void enroll_student(const Student& studentToEnroll);
};

std::ostream& operator<< (std::ostream& out, Specialty specialty);