#pragma once

#include "stdafx.h"
#include <iostream>

#include "Student.h"
#include "Subject.h"
#include "String.h"
#include "Vector.cpp"
#include "SUSI.h"


//Basic command functions
void open();
void close();
void save();
void save_as();
void help();

//Other functions
String findingNextWord(String input, int &currentIndex);
unsigned int stringToPositiveNumber(String stringNumber, int size);
bool isEndOfString(String input, int currentIndex);


//Basic command functions


//Specific command functions
void SUSI::add_specialty(Specialty specialty)
{
	this->specialties.push_back(specialty);
	std::cout << "Specialty '" << specialty << "' successfully added!\n\n";
}

void SUSI::add_subject(String name, bool isCompulsory, unsigned int course, String specialtyName)
{
	Subject subjectToAdd(name, isCompulsory, course);
	Specialty buffer(specialtyName);
	for (size_t i = 0; i < specialties.length(); i++)	//Finding the specialty, where the subject will be added
	{
		if (buffer == specialties[i])
		{
			specialties[i].add_subject(subjectToAdd);
			break;
		}
	}
}

void SUSI::enroll(unsigned int fn, String specialtyName, unsigned int group, String name)
{
	Student studentToEnroll(name, fn, specialtyName, group);
	Specialty buffer(specialtyName);
	for (size_t i = 0; i < specialties.length(); i++)	//Finding the specialty, where the student will be enrolled
	{
		if (buffer == specialties[i])
		{
			specialties[i].enroll_student(studentToEnroll);
			break;
		}
	}
}


//Functions for preparing data
void SUSI::prepareAdd_Specialty(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. More data is needed.
	
	String specialtyName = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command. There must be only name of specialty.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}
	if (isRegisteredSpecialty(specialtyName))	//Checking if the specialty is already registered to SUSI.
	{
		std::cout << "Adding specialty failed. This specialty had already been added to SUSI.\n\n";
		return;
	}
	
	add_specialty(specialtyName);
}

void SUSI::prepareAdd_Subject(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. More data is needed.

	String subjectName = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	String subjectType = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	bool isCompulsory = false;
	if (subjectType == "compulsory")	//Checking if the subject is compulsory or elective. Otherwise it is invalid input.
	{
		isCompulsory = true;
	}
	else if (subjectType == "elective")
	{
		isCompulsory = false;
	}
	else
	{
		std::cout << "A subject must be either compulsory or elective.\n\n";
		return;
	}

	String stringCourse = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }
	for (size_t i = 0; i < stringCourse.length(); i++)	//Validation if the course is a number > 0
	{
		if (stringCourse[i] < '0' || '9' < stringCourse[i])
		{
			std::cout << "The course number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int course = stringToPositiveNumber(stringCourse, stringCourse.length());
	if (course == 0)	//Validation if the course is bigger than zero (0).
	{
		std::cout << "The course number must be a positive number.\n\n";
		return;
	}

	String specialtyName = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}
	if (!isRegisteredSpecialty(specialtyName))	//Checking if the specialty is registered. You can not add subject to non-existing specialty.
	{
		std::cout << "Adding subject failed. There is not such a specialty.\n\n";
		return;
	}
	
	if (isRegisteredSubject(subjectName, isCompulsory, course, specialtyName))	//Checking if the subject is already added to this specialty.
	{
		std::cout << "Adding subject failed. This subject had already been added to this specialty.\n\n";
		return;
	}

	add_subject(subjectName, isCompulsory, course, specialtyName);
}

void SUSI::prepareEnroll(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }
	for (size_t i = 0; i < facultyNumber.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumber[i] < '0' || '9' < facultyNumber[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}
	
	unsigned int fn = stringToPositiveNumber(facultyNumber, facultyNumber.length());
	if (fn == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number.\n\n";
		return;
	}

	String specialtyName = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	String groupNumber = findingNextWord(input, currentIndex);
	for (size_t i = 0; i < groupNumber.length(); i++)	//Validation of the group number.
	{
		if (groupNumber[i] < '0' || '9' < groupNumber[i])
		{
			std::cout << "The group number must be a positive number.\n\n";
			return;
		}
	}
	if (isEndOfString(input, currentIndex)) { return; }

	unsigned int group = (unsigned int)stringToPositiveNumber(groupNumber, groupNumber.length());
	if (group == 0)	//Validation if the course is bigger than zero (0).
	{
		std::cout << "The group number must be a positive number.\n\n";
		return;
	}

	String name;
	for (size_t i = currentIndex; input[i] != '\0'; i++)	//Input the name until '\0', because it can be more than one word
	{
		name += input[i];
	}
	
	if (isRegisteredStudent(fn, specialtyName, group, name))	//Checking if the student is already enrolled to this specialty.
	{
		std::cout << "Enrolling student failed. There is already student with this faculty number in the system.\n\n";
		return;
	}

	enroll(fn, specialtyName, group, name);
}

void SUSI::prepareChange(String input, int currentIndex)
{
	//change();
}

void SUSI::preparePrint_All(String input, int currentIndex)
{
	//print_all();
}

void SUSI::prepareEnroll_In(String input, int currentIndex)
{
	//enroll_in();
}

void SUSI::prepareAdd_Grade(String input, int currentIndex)
{
	//add_grade();
}

void SUSI::prepareProtocol(String input, int currentIndex)
{
	//protocol();
}


//Other functions
String findingNextWord(String input, int &currentIndex)
{
	String result;
	for (size_t i = currentIndex; input[i] != ' ' && input[i] != '\0'; i++)
	{
		result += input[i];
		currentIndex = i;
	}
	currentIndex++;
	while (input[currentIndex] == ' ') { currentIndex++; }

	return result;
}

unsigned int stringToPositiveNumber(String stringNumber, int size)	//converting string to unsigned int
{
	if (size == 1)
	{
		return (unsigned int)(stringNumber[0] - '0');
	}
	return (unsigned int)((stringToPositiveNumber(stringNumber, size - 1) * 10) + (stringNumber[size - 1] - '0'));
}

bool isEndOfString(String input, int currentIndex)
{
	if (input[currentIndex] == '\0')
	{
		std::cout << "This is not a valid input. More data is needed.\n\n";
		return true;
	}
	return false;
}
