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

void SUSI::enroll(unsigned int fn, String specialtyName, unsigned int group, String name)
{
	Student studentToEnroll(name, fn, specialtyName, group);
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

void SUSI::advance(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].advanceStudent(fn);
			return;
		}
	}
}

void SUSI::changeSpecialty(unsigned int fn, String newSpecialty)
{
	Student newStudent = findStudent(fn);
	newStudent.setNewSpecialty(newSpecialty);
	newStudent.removeUnpassedElectiveSubjects();	//Removing all the unpassed elective subjects, because they may not be available in the new specialty
	
	removeFromCurrentSpecialty(fn);
	addToNewSpecialty(newStudent, newSpecialty);
}

void SUSI::changeGroup(unsigned int fn, unsigned int newGroup)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].changeGroupOfStudent(fn, newGroup);
			return;
		}
	}
}

void SUSI::graduate(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].graduateStudent(fn);
			return;
		}
	}
}

void SUSI::interrupt(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].interruptStudent(fn);
			return;
		}
	}
}

void SUSI::resume(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))
		{
			specialties[i].resumeStudent(fn);
			return;
		}
	}
}

void SUSI::print(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
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
	Specialty bufferSpecialty(specialtyName);
	for (size_t i = 0; i < specialties.length(); i++)	//Searching for the specialty with the name 'specialtyName'
	{
		if (specialties[i] == bufferSpecialty)	//finding the right specialty
		{
			for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Searching for students from this course
			{
				if (specialties[i].getStudents()[j].getCourse() == course)	//finding the students from this course
				{
					std::cout << specialties[i].getStudents()[j].getName() << " " << specialties[i].getStudents()[j].getFN() << std::endl;	//Printing the info of the student
				}
			}
			std::cout << std::endl;
			return;
		}
	}
}

void SUSI::enroll_in(unsigned int fn, Subject subject)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].getStudents().containsElement(buffer))	//Searching for the student with the same faculty number as the faculty number of 'buffer'
		{
			specialties[i].enrollStudentInSubject(fn, subject);
			return;
		}
	}
}

void SUSI::add_grade(unsigned int fn, Subject subjectToCompareWith, float grade)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].getStudents().containsElement(buffer))	//Searching for the student with the same faculty number as the faculty number of 'buffer'
		{
			specialties[i].addGradeToSubject(fn, subjectToCompareWith, grade);
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

void SUSI::report(unsigned int fn)
{

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
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}
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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (isRegisteredStudentByFacultyNumber(fn))	//Checking if there is already a student with this faculty number.
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
		std::cout << "The group number must be a positive number, bigger than 0.\n\n";
		return;
	}

	
	String name;
	for (size_t i = currentIndex; input[i] != '\0'; i++)	//Input the name until '\0', because it can be more than one word
	{
		name += input[i];
	}


	enroll(fn, specialtyName, group, name);
}

void SUSI::prepareAdvance(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'graduate' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(fn))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(fn))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}

	if (!isReadyToAdvance(fn))	//Checking if this student has more than 2 unpassed exams
	{
		std::cout << "This student had not passed enough exams to go in next course.\n\n";
		return;
	}

	
	advance(fn);
}

void SUSI::prepareChange(String input, int currentIndex)
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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'change' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(fn))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(fn))
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
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}


	if (option == "specialty")	//If the chosen option is "specialty"
	{
		if (!isRegisteredSpecialty(value))	//Checking if the specialty is registered. You can not re-enroll student to non-existing specialty.
		{
			std::cout << "Changing specialty failed. There is not specialty '" << value << "'.\n\n";
			return;
		}

		if (!isReadyToChangeSpecialty(fn))
		{
			std::cout << "Changing specialty failed. This student had not passed all exams for compulsory subjects.\n\n";
			return;
		}

		changeSpecialty(fn, value);
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

		changeGroup(fn, newGroup);
	}

	if (option == "year")		//If the chosen option is "year"
	{

		//To Do: validate if the input for year is the next year (course) || print "student successfully advanced to the next course"

		advance(fn);
	}
}

void SUSI::prepareGraduate(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'graduate' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(fn))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(fn))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}

	if (!isReadyToGraduate(fn))
	{
		std::cout << "Command 'graduate' failed. This student had not passed all exams.\n\n";
		return;
	}


	graduate(fn);
}

void SUSI::prepareInterrupt(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'interrupt' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isGraduated(fn))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	interrupt(fn);
}

void SUSI::prepareResume(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'resume' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (!isInterrupted(fn))
	{
		std::cout << "Student successfully resumed.\n\n";
		return;
	}
	if (isGraduated(fn))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	resume(fn);
}

void SUSI::preparePrint(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}

	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'print' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	print(fn);
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
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

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

	String facultyNumber = findingNextWord(input, currentIndex);

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}
	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'print' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(fn))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(fn))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	String subjectName = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}


	//Checking if the specialty of this student has this subject in this course/year
	unsigned int studentCourse = findingCourseOfStudent(fn);
	String studentSpecialty = findingSpecialtyOfStudent(fn);
	if (!isRegisteredSubjectInSpecialty(subjectName, studentCourse, studentSpecialty))
	{
		std::cout << "Command 'enroll_in' failed. There is not such subject in the year and the specialty of the student with the entered faculty number.\n\n";
		return;
	}
	Subject subjectToEnrollIn = findingSubjectAndSettingData(subjectName, studentCourse, studentSpecialty);	//Setting more data to 'subjectToEnrollIn' (only type - compulsory/elective)
	
	
	enroll_in(fn, subjectToEnrollIn);
}

void SUSI::prepareAdd_Grade(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String facultyNumber = findingNextWord(input, currentIndex);

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
		std::cout << "The faculty number must be a positive number, bigger than 0.\n\n";
		return;
	}
	if (!isRegisteredStudentByFacultyNumber(fn))	//Checking by faculty number if the student is registered.
	{
		std::cout << "Command 'print' failed. There is not student with this faculty number in the system.\n\n";
		return;
	}

	if (isInterrupted(fn))
	{
		std::cout << "Command failed. This student had interrupted.\n\n";
		return;
	}
	if (isGraduated(fn))
	{
		std::cout << "Command failed. This student had already graduated.\n\n";
		return;
	}


	String subjectName = findingNextWord(input, currentIndex);
	if (isEndOfString(input, currentIndex)) { return; }

	unsigned int studentCourse = findingCourseOfStudent(fn);
	String studentSpecialty = findingSpecialtyOfStudent(fn);
	if (!isRegisteredSubjectInSpecialty(subjectName, studentCourse, studentSpecialty))	//Checking if the specialty of this student has this subject in this course/year
	{
		std::cout << "Command 'add_grade' failed. There is not such subject in the year and the specialty of the student with the entered faculty number.\n\n";
		return;
	}
	
	Subject subjectToCompareWith(subjectName, true, studentCourse);

	if (isPassedExam(fn, subjectToCompareWith))
	{
		std::cout << "This student had already passed this exam, you can not change its grade.\n\n";
		return;
	}


	String gradeString = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

	float grade = strtof(gradeString.content, '\0');
	if (grade < 2 || 6 < grade)
	{
		std::cout << "Command 'add_grade' failed. The grade must be a number between 2 and 6.\n\n";
		return;
	}

	
	add_grade(fn, subjectToCompareWith, grade);
}

void SUSI::prepareProtocol(String input, int currentIndex)
{
	if (isEndOfString(input, currentIndex)) { return; }	//If it is end of the input, then it is not valid input. It is needed more data.

	String subjectName = findingNextWord(input, currentIndex);
	if (input[currentIndex] != '\0')	//Checking if there are more arguments for the command.
	{
		std::cout << "Too much arguments in the command.\n\n";
		return;
	}

	protocol(subjectName);
}

void SUSI::prepareReport(String input, int currentIndex)
{
	//report();
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

unsigned int SUSI::findingCourseOfStudent(unsigned int fn)
{
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Going through the students of this specialty (specialties[i])
		{
			if (specialties[i].getStudents()[j].getFN() == fn)
			{
				return specialties[i].getStudents()[j].getCourse();
			}
		}
	}
}

String SUSI::findingSpecialtyOfStudent(unsigned int fn)
{
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Going through the students of this specialty (specialties[i])
		{
			if (specialties[i].getStudents()[j].getFN() == fn)
			{
				return specialties[i].getStudents()[j].getSpecialty();
			}
		}
	}
}

Subject SUSI::findingSubjectAndSettingData(String subjectName, unsigned int studentCourse, String studentSpecialty)
{
	Specialty specialtyToCheck(studentSpecialty);
	Subject subjectToCheckAndSet(subjectName, true, studentCourse);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i] == specialtyToCheck)	//Finding the specialty of the student
		{
			for (size_t j = 0; j < specialties[i].getSubjects().length(); j++)	//Going through the subjects in this specialty (specialties[i])
			{
				if (specialties[i].getSubjects()[j] == subjectToCheckAndSet)	//Finding the subject in this year (studentCourse) of this specialty (studentSpecialty)
				{
					subjectToCheckAndSet = specialties[i].getSubjects()[j];	//Setting the new data (only 'isCompulsory' of the subject)
					return subjectToCheckAndSet;
				}
			}
			break;
		}
	}
}

Student SUSI::findStudent(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].findStudent(fn);
		}
	}
	std::cout << "Command failed. There is not such student.\n\n";
}

void SUSI::removeFromCurrentSpecialty(unsigned int fn)
{
	Student buffer("default", fn, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			specialties[i].removeStudent(fn);
			return;
		}
	}
	std::cout << "Command failed. There is not such student.\n\n";
}

void SUSI::addToNewSpecialty(const Student & student, String newSpecialty)
{
	Specialty buffer(newSpecialty);
	for (size_t i = 0; i < specialties.length(); i++)
	{
		if (specialties[i] == buffer)
		{
			specialties[i].addToNewSpecialty(student);
			return;
		}
	}
}
