#pragma once

#include "stdafx.h"
#include <iostream>

#include "Student.h"
#include "Subject.h"
#include "String.h"
#include "Vector.cpp"
#include "SUSI.h"

String findingNextWord(String input, int &currentIndex);
unsigned int stringToPositiveNumber(String stringNumber, int size);
bool isEndOfString(String input, int currentIndex);
bool isNotEndOfString(String input, int currentIndex);

//Basic command functions
void SUSI::help()
{
	std::cout << "add_specialty <specialty name>\n"
		<< "add_subject <name of subject> <type ('compulsory' or 'elective')> <year> <name of specialty>\n"
		<< "enroll <faculty number> <specialty> <group> <name(s) of student>\n"
		<< "advance <faculty number>\n"
		<< "change <faculty number> <option ('specialty'/'group'/'year')> <value>\n"
		<< "graduate <faculty number>\n"
		<< "interrupt <faculty number>\n"
		<< "resume <faculty number>\n"
		<< "print <faculty number>\n"
		<< "print_all <specialty> <year>\n"
		<< "enroll_in <faculty number> <subject>\n"
		<< "add_grade <faculty number> <subject> <grade>\n"
		<< "protocol <subject>\n"
		<< "report <faculty number>\n"
		<< "help -> prints this info\n"
		<< "exit -> ends the program\n\n";
}

//Specific command functions
void SUSI::add_specialty(Specialty specialty)
{
	specialties.push_back(specialty);
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
			return;
		}
	}
}

void SUSI::enroll(unsigned int facultyNumber, String specialtyName, unsigned int group, String name)
{
	Student studentToEnroll(name, facultyNumber, specialtyName, group);
	Specialty buffer(specialtyName);
	for (size_t i = 0; i < specialties.length(); i++)	//Finding the specialty, where the student will be enrolled
	{
		if (buffer == specialties[i])
		{
			specialties[i].enroll_student(studentToEnroll);
			return;
		}
	}
}

void SUSI::advance(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].advanceStudent(facultyNumber);
			return;
		}
	}
}

void SUSI::changeSpecialty(unsigned int facultyNumber, String newSpecialty)
{
	Student newStudent = findStudent(facultyNumber);
	newStudent.setNewSpecialty(newSpecialty);
	newStudent.removeUnpassedElectiveSubjects();	//Removing all the unpassed elective subjects, because they may not be available in the new specialty
	
	removeFromCurrentSpecialty(facultyNumber);
	addToNewSpecialty(newStudent, newSpecialty);
}

void SUSI::changeGroup(unsigned int facultyNumber, unsigned int newGroup)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].changeGroupOfStudent(facultyNumber, newGroup);
			return;
		}
	}
}

void SUSI::graduate(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].graduateStudent(facultyNumber);
			return;
		}
	}
}

void SUSI::interrupt(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].interruptStudent(facultyNumber);
			return;
		}
	}
}

void SUSI::resume(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].resumeStudent(facultyNumber);
			return;
		}
	}
}

void SUSI::print(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Going through the students in this specialty (specialties[i])
		{
			if (specialties[i].getStudents()[j] == buffer)	//If this student (getStudents()[j]) in this specialty (specialties[i]) has the same faculty number as the student 'buffer'
			{
				std::cout << specialties[i].getStudents()[j];	//Printing the info of this student (getStudents()[j])
				return;
			}
		}
	}
}

void SUSI::print_all(String specialtyName, unsigned int course)
{
	int counter = 0;
	Specialty bufferSpecialty(specialtyName);
	for (size_t i = 0; i < specialties.length(); i++)	//Searching for the specialty with the name 'specialtyName'
	{
		if (specialties[i] == bufferSpecialty)	//finding the right specialty
		{
			for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Searching for students from this course
			{
				if (specialties[i].getStudents()[j].getCourse() == course)	//finding the students from this course
				{
					std::cout << specialties[i].getStudents()[j].getName() << " " << specialties[i].getStudents()[j].getFacultyNumber() << std::endl;	//Printing the info of the student
					counter++;	//counting the students in this specialty and course
				}
			}
			if (counter == 0) { std::cout << "There are no students in this specialty and course.\n"; }
			std::cout << std::endl;
			return;
		}
	}
}

void SUSI::enroll_in(unsigned int facultyNumber, Subject subject)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].getStudents().containsElement(buffer))	//Searching for the student with the same faculty number as the faculty number of 'buffer'
		{
			specialties[i].enrollStudentInSubject(facultyNumber, subject);
			return;
		}
	}
}

void SUSI::add_grade(unsigned int facultyNumber, Subject subjectToCompareWith, float grade)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].getStudents().containsElement(buffer))	//Searching for the student with the same faculty number as the faculty number of 'buffer'
		{
			specialties[i].addGradeToSubject(facultyNumber, subjectToCompareWith, grade);
			return;
		}
	}
}

void SUSI::protocol(String subjectName)
{
	for (size_t i = 0; i < specialties.length(); i++)
	{
		for (size_t j = 0; j < specialties[i].getSubjects().length(); j++)
		{
			if (specialties[i].getSubjects()[j].getName() == subjectName)	//If this specialty contains this subject
			{
				specialties[i].protocol(subjectName);
			}
		}
	}
}

void SUSI::report(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].getStudents().containsElement(buffer))	//Searching for the student with the same faculty number as the faculty number of 'buffer'
		{
			specialties[i].report(facultyNumber);
			return;
		}
	}
}


//Functions for preparing data
void SUSI::prepareAdd_Specialty(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. More data is needed.
	
	String specialtyName = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.
	
	if (isRegisteredSpecialty(specialtyName))	//Checking if the specialty is already registered to SUSI.
	{
		std::cout << "Adding specialty failed. This specialty had already been added to SUSI.\n\n";
		return;
	}
	
	add_specialty(Specialty(specialtyName));
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
		std::cout << "A subject must be either 'compulsory' or 'elective'.\n\n";
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
		std::cout << "The course number must be a positive number, bigger than 0.\n\n";
		return;
	}

	
	String specialtyName = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	if (!isRegisteredSpecialty(specialtyName))	//Checking if the specialty is registered. You can not add subject to non-existing specialty.
	{
		std::cout << "Adding subject failed. There is not such specialty.\n\n";
		return;
	}
	
	if (isRegisteredSubjectInSpecialty(subjectName, course, specialtyName))	//Checking if the subject is already added to this specialty.
	{
		std::cout << "Adding subject failed. This subject had already been added to this specialty.\n\n";
		return;
	}

	
	add_subject(subjectName, isCompulsory, course, specialtyName);
}

void SUSI::prepareEnroll(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}
	
	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking if there is already a student with this faculty number.
	{
		std::cout << "Enrolling student failed. There is already student with this faculty number in the system.\n\n";
		return;
	}


	String specialtyName = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	if (!isRegisteredSpecialty(specialtyName))	//Checking if the specialty is registered. You can not enroll student to non-existing specialty.
	{
		std::cout << "Enrolling student failed. There is not such specialty.\n\n";
		return;
	}


	String groupNumber = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }
	
	for (size_t i = 0; i < groupNumber.length(); i++)	//Validation of the group number.
	{
		if (groupNumber[i] < '0' || '9' < groupNumber[i])
		{
			std::cout << "The group number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int group = (unsigned int)stringToPositiveNumber(groupNumber, groupNumber.length());
	if (group == 0)	//Validation if the course is bigger than zero (0).
	{
		std::cout << "The group number must be a positive number, bigger than 0.\n\n";
		return;
	}

	
	String name;
	for (size_t i = currentIndex; input[i] != '\0'; i++)	//Input the name until '\0', because it can be more than one word
	{
		name += input[i];
	}


	enroll(facultyNumber, specialtyName, group, name);
}

void SUSI::prepareAdvance(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'graduate' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(facultyNumber))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}

	if (!isReadyToAdvance(facultyNumber))	//Checking if this student has more than 2 unpassed exams
	{
		std::cout << "This student had not passed enough exams to go in next course.\n\n";
		return;
	}

	
	advance(facultyNumber);
}

void SUSI::prepareChange(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'change' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(facultyNumber))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}

	
	String option = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	if (option != "specialty" && option != "group" && option != "year")
	{
		std::cout << "This is not a valid option. You can change only the specialty, the group or the year.\n\n";
		return;
	}

	
	String value = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.


	if (option == "specialty")	//If the chosen option is "specialty"
	{
		if (isRegisteredStudentInSpecialty(facultyNumber, value))
		{
			std::cout << "This student is already enrolled in this specialty.\n\n";
			return;
		}

		if (!isRegisteredSpecialty(value))	//Checking if the specialty is registered. You can not re-enroll student to non-existing specialty.
		{
			std::cout << "Changing specialty failed. There is not specialty '" << value << "'.\n\n";
			return;
		}

		if (!isReadyToChangeSpecialty(facultyNumber))
		{
			std::cout << "Changing specialty failed. This student had not passed all exams for compulsory subjects.\n\n";
			return;
		}

		changeSpecialty(facultyNumber, value);
	}

	if (option == "group")		//If the chosen option is "group"
	{
		for (size_t i = 0; i < value.length(); i++)	//Validation of the new group number.
		{
			if (value[i] < '0' || '9' < value[i])
			{
				std::cout << "The new group number must be a positive number.\n\n";
				return;
			}
		}

		unsigned int newGroup = stringToPositiveNumber(value, value.length());
		if (newGroup == 0)	//Validation if the new group number is bigger than zero (0).
		{
			std::cout << "The new group number must be a positive number, bigger than 0.\n\n";
			return;
		}

		changeGroup(facultyNumber, newGroup);
	}

	if (option == "year")		//If the chosen option is "year"
	{
		advance(facultyNumber);
	}
}

void SUSI::prepareGraduate(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'graduate' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(facultyNumber))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}

	if (!isReadyToGraduate(facultyNumber))
	{
		std::cout << "Command 'graduate' failed. This student had not passed all exams.\n\n";
		return;
	}


	graduate(facultyNumber);
}

void SUSI::prepareInterrupt(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'interrupt' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	interrupt(facultyNumber);
}

void SUSI::prepareResume(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'resume' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (!isInterrupted(facultyNumber))
	{
		std::cout << "Student successfully resumed.\n\n";
		return;
	}
	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	resume(facultyNumber);
}

void SUSI::preparePrint(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'print' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	print(facultyNumber);
}

void SUSI::preparePrint_All(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String specialtyName = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	if (!isRegisteredSpecialty(specialtyName))	//Checking if the specialty is registered. You can not enroll student to non-existing specialty.
	{
		std::cout << "Command 'print_all' failed. There is not such specialty.\n\n";
		return;
	}

	String courseString = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < courseString.length(); i++)	//Validation of the faculty number.
	{
		if (courseString[i] < '0' || '9' < courseString[i])
		{
			std::cout << "The course number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int course = stringToPositiveNumber(courseString, courseString.length());
	if (course == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The course number must be a positive number, bigger than 0.\n\n";
		return;
	}


	print_all(specialtyName, course);
}

void SUSI::prepareEnroll_In(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}
	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'print' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(facultyNumber))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	String subjectName = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.


	//Checking if the specialty of this student has this subject in this course/year
	unsigned int studentCourse = findingCourseOfStudent(facultyNumber);
	String studentSpecialty = findingSpecialtyOfStudent(facultyNumber);
	if (!isRegisteredSubjectInSpecialty(subjectName, studentCourse, studentSpecialty))
	{
		std::cout << "Command 'enroll_in' failed. There is not such subject in the year and the specialty of the student with the entered faculty number.\n\n";
		return;
	}
	Subject subjectToEnrollIn = findingSubjectAndSettingData(subjectName, studentCourse, studentSpecialty);	//Setting more data to 'subjectToEnrollIn' (only type - compulsory/elective)
	
	
	enroll_in(facultyNumber, subjectToEnrollIn);
}

void SUSI::prepareAdd_Grade(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}
	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'print' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(facultyNumber))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(facultyNumber))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	String subjectName = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	unsigned int studentCourse = findingCourseOfStudent(facultyNumber);
	if (!hasThisSubject(facultyNumber, subjectName))	//Checking if this student has this subject
	{
		std::cout << "Command 'add_grade' failed. There is not such subject in the year and the specialty of the student with the entered faculty number.\n\n";
		return;
	}
	
	Subject subjectToCompareWith(subjectName, true, studentCourse);

	if (isPassedExam(facultyNumber, subjectToCompareWith))
	{
		std::cout << "This student had already passed this exam, you can not change its grade.\n\n";
		return;
	}


	String gradeString = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	float grade = strtof(gradeString.c_str(), '\0');
	if (grade < 2 || 6 < grade)
	{
		std::cout << "Command 'add_grade' failed. The grade must be a number between 2 and 6.\n\n";
		return;
	}

	
	add_grade(facultyNumber, subjectToCompareWith, grade);
}

void SUSI::prepareProtocol(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String subjectName = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	protocol(subjectName);
}

void SUSI::prepareReport(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumberStr = findingNextWord(input, currentIndex);
	if (isNotEndOfString(input, currentIndex)) { return; }	//Checking if there are more arguments for the command.

	for (size_t i = 0; i < facultyNumberStr.length(); i++)	//Validation of the faculty number.
	{
		if (facultyNumberStr[i] < '0' || '9' < facultyNumberStr[i])
		{
			std::cout << "The faculty number must be a positive number.\n\n";
			return;
		}
	}

	unsigned int facultyNumber = stringToPositiveNumber(facultyNumberStr, facultyNumberStr.length());
	if (facultyNumber == 0)	//Validation if the faculty number is bigger than zero (0).
	{
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(facultyNumber))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'graduate' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	
	report(facultyNumber);
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

bool isNotEndOfString(String input, int currentIndex)
{
	if (input[currentIndex] != '\0')
	{
		std::cout << "This is not a valid input. Too many arguments.\n\n";
		return true;
	}
	return false;
}