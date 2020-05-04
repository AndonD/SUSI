#pragma once

#include <iostream>

#include "Vector.cpp"
#include "String.h"
#include "Specialty.h"
#include "Subject.h"
#include "Student.h"


class SUSI
{
private:
	Vector<Specialty> specialties;
public:
	SUSI();
	~SUSI();

	void startSUSI();	//start of the program SUSI
	bool isRegisteredSpecialty(String specialtyName);
	bool isRegisteredSubject(String subjectName, bool isCompulsory, unsigned int course, String specialtyName);
	bool isRegisteredStudent(unsigned int fn, String specialtyName, unsigned int group, String name);
	

	
	//Basic command functions
	void open();
	void close();
	void save();
	void save_as();
	void help();

	//Specific command functions
	void add_specialty(Specialty specialty);
	void add_subject(String name, bool isCompulsory, unsigned int course, String specialtyName);
	void enroll(unsigned int fn, String specialty, unsigned int group, String name);
	void advance();
	void change();
	void graduate();
	void interrupt();
	void resume();
	void print();
	void print_all();
	void enroll_in();
	void add_grade();
	void protocol();
	void report();

	//Functions for preparing data
	void prepareAdd_Specialty(String input, int currentIndex);
	void prepareAdd_Subject(String input, int currentIndex);
	void prepareEnroll(String input, int currentIndex);
	void prepareChange(String input, int currentIndex);
	void preparePrint_All(String input, int currentIndex);
	void prepareEnroll_In(String input, int currentIndex);
	void prepareAdd_Grade(String input, int currentIndex);
	void prepareProtocol(String input, int currentIndex);
};

