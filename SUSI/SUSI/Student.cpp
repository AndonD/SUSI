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
	this->averageGrade = 0;
}

Student & Student::operator=(const Student& other)
{
	this->name = other.name;
	this->fn = other.fn;
	this->specialty = other.specialty;
	this->course = other.course;
	this->group = other.group;
	this->status = other.status;
	this->averageGrade = other.averageGrade;
	this->subjects = other.subjects;

	return *this;
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

unsigned int Student::getFN() const
{
	return this->fn;
}

String Student::getSpecialty() const
{
	return this->specialty;
}

unsigned int Student::getCourse() const
{
	return this->course;
}

unsigned int Student::getGroup() const
{
	return this->group;
}

String Student::getStatus() const
{
	return this->status;
}

float Student::getAverageGrade() const
{
	return this->averageGrade;
}

Vector<Subject> Student::getSubjects() const
{
	return this->subjects;
}

float Student::getGrade(String subjectName) const
{
	for (size_t i = 0; i < subjects.length(); i++)
	{
		if (subjects[i].getName() == subjectName)
		{
			return subjects[i].getGrade();
		}
	}
}


bool Student::isReadyToAdvance()
{
	int numberOfUnpassedExams = 0;
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (this->subjects[i].getIsCompulsory() && this->subjects[i].getGrade() < 3)
		{
			numberOfUnpassedExams++;
		}
	}
	if (numberOfUnpassedExams > 2)
	{
		return false;
	}
	return true;
}

bool Student::isReadyToChangeSpecialty()
{
	int numberOfUnpassedExams = 0;
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (this->subjects[i].getIsCompulsory() && (this->subjects[i].getGrade() < 3 || 6 < this->subjects[i].getGrade()))
		{
			numberOfUnpassedExams++;
		}
	}
	if (numberOfUnpassedExams > 0)
	{
		return false;
	}
	return true;
}

bool Student::isReadyToGraduate()
{
	int numberOfUnpassedExams = 0;
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (this->subjects[i].getGrade() < 3 || 6 < this->subjects[i].getGrade())
		{
			numberOfUnpassedExams++;
		}
	}
	if (numberOfUnpassedExams != 0)
	{
		return false;
	}
	return true;
}

bool Student::isInterrupted()
{
	if (this->status == "interrupted")
	{
		return true;
	}
	return false;
}

bool Student::isGraduated()
{
	if (this->status == "graduated")
	{
		return true;
	}
	return false;
}

bool Student::hasThisSubject(String subjectName)
{
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (this->subjects[i].getName() == subjectName)
		{
			return true;
		}
	}
	return false;
}

void Student::advance()
{
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (this->subjects[i].getGrade() >= 3 && 6 <= this->subjects[i].getGrade())
		{
			this->subjects.removeFromIndex(i);
		}
	}

	this->course++;
	std::cout << "Student with faculty number " << this->fn << " successfully passed " << this->course - 1 << " course. Already enrolled in " << this->course << " course.\n\n";
}

void Student::setNewGroup(unsigned int newGroup)
{
	this->group = newGroup;
	std::cout << "Student with faculty number " << fn << " successfully moved to " << this->group << " group.\n\n";
}

void Student::setNewSpecialty(String newSpecialty)
{
	this->specialty = newSpecialty;
}

void Student::graduate()
{
	this->status = "graduated";
	std::cout << "Student with faculty number " << fn << " successfully graduated!\n\n";
}

void Student::interrupt()
{
	this->status = "interrupted";
	std::cout << "Student with faculty number " << fn << " interrupted.\n\n";
}

void Student::resume()
{
	this->status = "enrolled";
	std::cout << "Student with faculty number " << fn << " resumed.\n\n";
}

void Student::enrollInSubject(Subject subject)
{
	this->subjects.push_back(subject);	//Adding the new subject
	updateAverageGrade();
	std::cout << "Student with faculty number " << this->fn
			  << " successfully enrolled in subject '" << subject << "'.\n\n";
}

bool Student::hasPassedExam(Subject subjectToCompareWith)
{
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (subjects[i] == subjectToCompareWith)
		{
			if (subjects[i].getGrade() < 3 || 6 < subjects[i].getGrade())
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;	//Default return
}

void Student::setGradeToSubject(Subject subjectToCompareWith, float grade)
{
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (subjects[i] == subjectToCompareWith)
		{
			subjects[i].setGrade(grade);
			if (3 <= grade && grade <= 6)
			{
				std::cout << "Grade " << grade << " successfully added!\n\n";
			}
			break;
		}
	}
	updateAverageGrade();
	return;
}

void Student::updateAverageGrade()
{
	float sumOfAllGrades = 0;
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		sumOfAllGrades += subjects[i].getGrade();
	}
	this->averageGrade = sumOfAllGrades / (float)subjects.length();
}

void Student::removeUnpassedElectiveSubjects()
{
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (!subjects[i].getIsCompulsory() && (subjects[i].getGrade() < 3 || 6 < subjects[i].getGrade()))
		{
			subjects.removeFromIndex(i);
		}
	}
}



std::ostream & operator<<(std::ostream & out, Student student)
{

	out << "Student info:\n";
	out << "Faculty number: " << student.getFN() << std::endl;
	out << "Name: " << student.getName() << std::endl;
	out << "Specialty: " << student.getSpecialty() << std::endl;
	out << "Course: " << student.getCourse() << std::endl;
	out << "Group: " << student.getGroup() << std::endl;
	out << "Status: " << student.getStatus() << std::endl;
	out << "Average grade: " << student.getAverageGrade() << std::endl;
	out << "Subjects this student is enrolled in: " << student.getSubjects() << std::endl << std::endl;

	return out;
}
