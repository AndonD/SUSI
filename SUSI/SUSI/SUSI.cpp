#include "stdafx.h"
#include "SUSI.h"

//SUSI methods defined at the bottom of this file



String findingNextWord(String input, int &currentIndex);

void SUSI::startSUSI()
{
	std::cout << "Instructions:\n";
	help();

	//Start
	String input;
	std::cin >> input;
	bool startOfProgram = true;

	while (input != "exit")
	{
		if (!startOfProgram)		//if it is not the start of the program, type new input
		{
			input.clear();
			std::cin >> input;
		}

		int currentIndex = 0;

		String commandName = findingNextWord(input, currentIndex);

		//Basic functions
		if (commandName == "open")
		{
			//open();
		}
		else if (commandName == "close")
		{
			//close();
		}
		else if (commandName == "save")
		{
			//save();
		}
		else if (commandName == "save_as")
		{
			//save_as();
		}
		else if (commandName == "help")
		{
			help();
		}

		//Specific functions for SUSI
		else if (commandName == "add_specialty")
		{
			prepareAdd_Specialty(input, currentIndex);
		}
		else if (commandName == "add_subject")
		{
			prepareAdd_Subject(input, currentIndex);
		}
		else if (commandName == "enroll")
		{
			prepareEnroll(input, currentIndex);
		}
		else if (commandName == "advance")
		{
			prepareAdvance(input, currentIndex);
		}
		else if (commandName == "change")
		{
			prepareChange(input, currentIndex);
		}
		else if (commandName == "graduate")
		{
			prepareGraduate(input, currentIndex);
		}
		else if (commandName == "interrupt")
		{
			prepareInterrupt(input, currentIndex);
		}
		else if (commandName == "resume")
		{
			prepareResume(input, currentIndex);
		}
		else if (commandName == "print")
		{
			preparePrint(input, currentIndex);
		}
		else if (commandName == "print_all")
		{
			preparePrint_All(input, currentIndex);
		}
		else if (commandName == "enroll_in")
		{
			prepareEnroll_In(input, currentIndex);
		}
		else if (commandName == "add_grade")
		{
			prepareAdd_Grade(input, currentIndex);	
		}
		else if (commandName == "protocol")
		{
			prepareProtocol(input, currentIndex);
		}
		else if (commandName == "report")
		{
			prepareReport(input, currentIndex);
		}
		else if (commandName == "exit")
		{
			return;
		}
		else
		{
			std::cout << "This is not a valid command.\nType again.\n\n";
		}

		startOfProgram = false;
	}
}


//SUSI methods defined here
SUSI::SUSI()
{
}
SUSI::~SUSI()
{
}

bool SUSI::isRegisteredSpecialty(String specialtyName)
{
	Specialty buffer(specialtyName);
	return specialties.containsElement(buffer);
}

bool SUSI::isRegisteredSubjectInSpecialty(String subjectName, unsigned int course, String specialtyName)
{
	Subject buffer(subjectName, true, course);
	for (size_t i = 0; i < specialties.length(); i++)
	{
		if (specialties[i].getName() == specialtyName)
		{
			return specialties[i].isRegisteredSubject(buffer);
		}
	}
	std::cout << "There is not such a specialty.\n\n";
	return false;
}

bool SUSI::isRegisteredSubject(String subjectName, unsigned int course)
{
	Subject buffer(subjectName, true, course);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].isRegisteredSubject(buffer))	//Checking if there is a subject same as the 'buffer' subject in this specialty
		{
			return true;
		}
	}
	return false;
}

bool SUSI::isPassedExam(unsigned int facultyNumber, Subject subjectToCompareWith)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		if (specialties[i].getStudents().containsElement(buffer))	//Searching for the student with the same faculty number as the faculty number of 'buffer'
		{
			return specialties[i].isPassedExam(facultyNumber, subjectToCompareWith);
		}
	}
	return false;	//Default return
}

bool SUSI::isRegisteredStudentInSpecialty(unsigned int facultyNumber, String specialtyName)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)
	{
		if (specialties[i].getName() == specialtyName)
		{
			return specialties[i].isRegisteredStudent(buffer);
		}
	}
	std::cout << "There is not such specialty.\n\n";
	return false;
}

bool SUSI::isRegisteredStudentByFacultyNumber(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return true;
		}
	}
	return false;
}

bool SUSI::isReadyToAdvance(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].isReadyToAdvance(facultyNumber);
		}
	}

	return false;	//Default return
}

bool SUSI::isReadyToChangeSpecialty(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].isReadyToChangeSpecialty(facultyNumber);
		}
	}

	return false;	//Default return
}

bool SUSI::isInterrupted(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].isInterruptedStudent(facultyNumber);
		}
	}

	return false;	//Default return
}

bool SUSI::isGraduated(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].isGraduatedStudent(facultyNumber);
		}
	}

	return false;	//Default return
}

bool SUSI::isReadyToGraduate(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].isReadyToGraduate(facultyNumber);
		}
	}

	return false;	//Default return
}

unsigned int SUSI::findingCourseOfStudent(unsigned int facultyNumber)
{
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Going through the students of this specialty (specialties[i])
		{
			if (specialties[i].getStudents()[j].getFacultyNumber() == facultyNumber)
			{
				return specialties[i].getStudents()[j].getCourse();
			}
		}
	}
}

String SUSI::findingSpecialtyOfStudent(unsigned int facultyNumber)
{
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties
	{
		for (size_t j = 0; j < specialties[i].getStudents().length(); j++)	//Going through the students of this specialty (specialties[i])
		{
			if (specialties[i].getStudents()[j].getFacultyNumber() == facultyNumber)
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

Student SUSI::findStudent(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			return specialties[i].findStudent(facultyNumber);
		}
	}
	std::cout << "Command failed. There is not such student.\n\n";
}

void SUSI::removeFromCurrentSpecialty(unsigned int facultyNumber)
{
	Student buffer("default", facultyNumber, "default", 0);
	for (size_t i = 0; i < specialties.length(); i++)	//Going through the specialties in SUSI
	{
		if (specialties[i].getStudents().containsElement(buffer))	//If there is already registered a student with faculty number as the buffer's faculty number in this specialty (specialties[i])
		{
			specialties[i].removeStudent(facultyNumber);
			return;
		}
	}
	std::cout << "Command failed. There is not such student.\n\n";
}

void SUSI::addToNewSpecialty(const Student &student, String newSpecialty)
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
