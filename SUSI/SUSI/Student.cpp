#include "stdafx.h"
#include "Student.h"


Student::Student()
{
	name = "";
	facultyNumber = 0;
	specialty = "";
	group = 0;
	course = 0;
	status = "";
	averageGrade = 0;
}

Student::Student(const Student &other)
{
	this->name = other.name;
	this->facultyNumber = other.facultyNumber;
	this->specialty = other.specialty;
	this->course = other.course;
	this->group = other.group;
	this->status = other.status;
	this->averageGrade = other.averageGrade;
	this->subjects = other.subjects;
}

Student::Student(String _name, unsigned int _facultyNumber, String _specialty, unsigned int _group)
{
	this->name = _name;
	this->facultyNumber = _facultyNumber;
	this->specialty = _specialty;
	this->group = _group;
	this->course = 1;
	this->status = "enrolled";
	this->averageGrade = 0;
}

Student& Student::operator=(const Student &other)
{
	this->name = other.name;
	this->facultyNumber = other.facultyNumber;
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


bool Student::operator== (const Student &other)
{
	return (this->facultyNumber == other.facultyNumber);
}

bool Student::operator!= (const Student &other)
{
	return (this->facultyNumber != other.facultyNumber);
}


String Student::getName() const
{
	return this->name;
}

unsigned int Student::getFacultyNumber() const
{
	return this->facultyNumber;
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
	std::cout << "Student with faculty number " << this->facultyNumber << " successfully passed " << this->course - 1 << " course. Already enrolled in " << this->course << " course.\n\n";
}

void Student::setNewGroup(unsigned int newGroup)
{
	this->group = newGroup;
	std::cout << "Student with faculty number " << facultyNumber << " successfully moved to " << this->group << " group.\n\n";
}

void Student::setNewSpecialty(String newSpecialty)
{
	this->specialty = newSpecialty;
}

void Student::graduate()
{
	this->status = "graduated";
	std::cout << "Student with faculty number " << facultyNumber << " successfully graduated!\n\n";
}

void Student::interrupt()
{
	this->status = "interrupted";
	std::cout << "Student with faculty number " << facultyNumber << " interrupted.\n\n";
}

void Student::resume()
{
	this->status = "enrolled";
	std::cout << "Student with faculty number " << facultyNumber << " resumed.\n\n";
}

void Student::enrollInSubject(Subject subject)
{
	this->subjects.push_back(subject);	//Adding the new subject
	updateAverageGrade();
	std::cout << "Student with faculty number " << this->facultyNumber
			  << " successfully enrolled in subject '" << subject << "'.\n\n";
}

bool Student::hasPassedExam(Subject subjectToCompareWith)
{
	for (size_t i = 0; i < this->subjects.length(); i++)
	{
		if (subjects[i].getName() == subjectToCompareWith.getName())
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
		if (subjects[i].getName() == subjectToCompareWith.getName())
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

void Student::report()
{
	Vector<Subject> passedExams;
	Vector<Subject> unpassedExams;

	for (size_t i = 0; i < subjects.length(); i++)
	{
		if (3 <= subjects[i].getGrade() && subjects[i].getGrade() <= 6)
		{
			passedExams.push_back(subjects[i]);
		}
		else
		{
			unpassedExams.push_back(subjects[i]);
		}
	}

	//Валидирай дали са празни векторите
	//Изхвърля ме от програмата ако студентът няма предмети и изкарва 

	std::cout << "Passed exams:\n";
	for (size_t i = 0; i < passedExams.length(); i++)	//Output the list of passed exams
	{
		std::cout << passedExams[i] << " --> " << passedExams[i].getGrade() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Unpassed exams:\n";
	for (size_t i = 0; i < unpassedExams.length(); i++)	//Output the list of unpassed exams
	{
		std::cout << unpassedExams[i] << " --> " << passedExams[i].getGrade() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Average grade: " << averageGrade << "\n\n";
}


std::ostream& operator<<(std::ostream &out, Student student)
{

	out << "Student info:\n";
	out << "Faculty number: " << student.getFacultyNumber() << std::endl;
	out << "Name: " << student.getName() << std::endl;
	out << "Specialty: " << student.getSpecialty() << std::endl;
	out << "Course: " << student.getCourse() << std::endl;
	out << "Group: " << student.getGroup() << std::endl;
	out << "Status: " << student.getStatus() << std::endl;
	out << "Average grade: " << student.getAverageGrade() << std::endl;
	out << "Subjects this student is enrolled in: " << student.getSubjects() << std::endl << std::endl;

	return out;
}