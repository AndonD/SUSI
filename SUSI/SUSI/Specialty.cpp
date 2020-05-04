#include "stdafx.h"
#include "Specialty.h"


Specialty::Specialty()
{
	name = "";
}

Specialty::Specialty(String _name)
{
	this->name = _name;
}

Specialty::~Specialty()
{
}


bool Specialty::isRegisteredSubject(const Subject & subject)
{
	return this->subjects.containsElement(subject);
}

bool Specialty::isRegisteredStudent(const Student & student)
{
	return this->students.containsElement(student);
}


bool Specialty::operator== (const Specialty& other)
{
	return (this->name == other.name);
}

bool Specialty::operator!= (const Specialty& other)
{
	return (this->name != other.name);
}

String Specialty::getName() const
{
	return this->name;
}


void Specialty::add_subject(const Subject& subjectToAdd)
{
	subjects.push_back(subjectToAdd);
	std::cout << "Subject '" << subjectToAdd.getName() << "' successfully added to specialty '" << name << "'!\n\n";
}

void Specialty::enroll_student(const Student & studentToEnroll)
{
	students.push_back(studentToEnroll);
	std::cout << "Student '" << studentToEnroll.getName() << "' successfully enrolled to specialty '" << name << "'!\n\n";
}


std::ostream& operator<< (std::ostream& out, Specialty specialty)
{
	out << specialty.getName();
	return out;
}