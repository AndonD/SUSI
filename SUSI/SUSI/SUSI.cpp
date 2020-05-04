#include "stdafx.h"
#include "SUSI.h"

//SUSI methods defined at the bottom of this file



String findingNextWord(String input, int &currentIndex);

void SUSI::startSUSI()
{
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
			//help();
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
			//enroll();
		}
		else if (commandName == "advance")
		{
			//advance();
		}
		else if (commandName == "change")
		{
			//prepareChange(input, currentIndex);
			//change();
		}
		else if (commandName == "graduate")
		{
			//graduate();
		}
		else if (commandName == "interrupt")
		{
			//interrupt();
		}
		else if (commandName == "resume")
		{
			//resume();
		}
		else if (commandName == "print")
		{
			//print();
		}
		else if (commandName == "print_all")
		{
			//preparePrint_All(input, currentIndex);
			//print_all();
		}
		else if (commandName == "enroll_in")
		{
			//prepareEnroll_In(input, currentIndex);
			//enroll_in();
		}
		else if (commandName == "add_grade")
		{
			//prepareAdd_Grade(input, currentIndex);
			//add_grade();
		}
		else if (commandName == "protocol")
		{
			//prepareProtocol(input, currentIndex);
			//protocol();
		}
		else if (commandName == "report")
		{
			//report();
		}
		else if (commandName == "exit")
		{
			return;
		}
		else if (input != "exit")
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

bool SUSI::isRegisteredSubject(String subjectName, bool isCompulsory, unsigned int course, String specialtyName)
{
	Subject buffer(subjectName, isCompulsory, course);
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

bool SUSI::isRegisteredStudent(unsigned int fn, String specialtyName, unsigned int group, String name)
{
	Student buffer(name, fn, specialtyName, group);
	for (size_t i = 0; i < specialties.length(); i++)
	{
		if (specialties[i].getName() == specialtyName)
		{
			return specialties[i].isRegisteredStudent(buffer);
		}
	}
	std::cout << "There is not such a specialty.\n\n";
	return false;
}
