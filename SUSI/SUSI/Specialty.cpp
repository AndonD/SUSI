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

bool Specialty::isPassedExam(unsigned int fn, Subject subjectToCompareWith)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i].hasPassedExam(subjectToCompareWith);
		}
	}
	return false;	//Default return
}

bool Specialty::isReadyToAdvance(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i].isReadyToAdvance();
		}
	}
	return false;	//Default return
}

bool Specialty::isReadyToChangeSpecialty(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i].isReadyToChangeSpecialty();
		}
	}
	return false;	//Default return
}

bool Specialty::isReadyToGraduate(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i].isReadyToGraduate();
		}
	}
	return false;	//Default return
}

bool Specialty::isInterruptedStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i].isInterrupted();
		}
	}
	return false;	//Default return
}

bool Specialty::isGraduatedStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i].isGraduated();
		}
	}
	return false;	//Default return
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

Vector<Student> Specialty::getStudents() const
{
	return students;
}

Vector<Subject> Specialty::getSubjects() const
{
	return subjects;
}

Student Specialty::findStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)	//Going through the students in this specialty
	{
		if (students[i].getFN() == fn)	//Finding the student with this faculty number
		{
			return students[i];
		}
	}
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

void Specialty::advanceStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].advance();
			return;
		}
	}
}

void Specialty::changeGroupOfStudent(unsigned int fn, unsigned int newGroup)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].setNewGroup(newGroup);
			return;
		}
	}
}

void Specialty::graduateStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].graduate();
			return;
		}
	}
}

void Specialty::interruptStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].interrupt();
			return;
		}
	}
}

void Specialty::resumeStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].resume();
			return;
		}
	}
}

void Specialty::enrollStudentInSubject(unsigned int fn, Subject subject)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].enrollInSubject(subject);
			return;
		}
	}
}

void Specialty::addGradeToSubject(unsigned int fn, Subject subjectToCompareWith, float grade)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students[i].setGradeToSubject(subjectToCompareWith, grade);
			return;
		}
	}
}

void Specialty::removeStudent(unsigned int fn)
{
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].getFN() == fn)
		{
			students.removeFromIndex(i);
			return;
		}
	}
}

void Specialty::addToNewSpecialty(const Student & student)
{
	students.push_back(student);
	std::cout << "Student '" << student.getName() << "' successfully moved to specialty '" << name << "'!\n\n";
}

void Specialty::protocol(String subjectName)
{
	std::cout << "Specialty: " << this->name << std::endl;

	Vector<Student> studentsInProtocol;
	for (size_t i = 0; i < students.length(); i++)
	{
		if (students[i].hasThisSubject(subjectName))
		{
			studentsInProtocol.push_back(students[i]);
		}
	}

	if (!studentsInProtocol.isEmpty())
	{
		int minimum;	//Index of the student with the smallest faculty number
		for (size_t i = 0; i < studentsInProtocol.length(); i++)
		{
			minimum = i;	//Doing this for every single student in the vector
			for (size_t j = i + 1; j < studentsInProtocol.length(); j++)
			{
				//If there is a student on index bigger than minimum(i) with smaller faculty number, then change the value of "minimum" to swap the students
				if (studentsInProtocol[minimum].getFN() > studentsInProtocol[j].getFN())
				{
					minimum = j;
				}
			}
			std::swap(studentsInProtocol[i], studentsInProtocol[minimum]);	//Swapping the students. If "minimum" is still equal to "i" after the for-loops, nothing will happen
		}
	}
 

	std::cout << "Faculty number\t\tName\t\t\tGrade\n";
	for (size_t i = 0; i < studentsInProtocol.length(); i++)
	{
		std::cout << studentsInProtocol[i].getFN() << "\t\t\t" 
				  << studentsInProtocol[i].getName() << "\t\t\t"
				  << studentsInProtocol[i].getGrade(subjectName) << std::endl;
	}
	std::cout << std::endl;
}


std::ostream& operator<< (std::ostream& out, Specialty specialty)
{
	out << specialty.getName();
	return out;
}