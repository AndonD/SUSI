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
	bool isRegisteredSubjectInSpecialty(String subjectName, unsigned int course, String specialtyName);
	bool isRegisteredSubject(String subjectName, unsigned int course);
	bool isPassedExam(unsigned int fn, Subject subjectToCompare);
	bool isRegisteredStudentInSpecialty(unsigned int fn, String specialtyName, unsigned int group, String name);
	bool isRegisteredStudentByFacultyNumber(unsigned int fn);
	bool isReadyToAdvance(unsigned int fn);
	bool isReadyToChangeSpecialty(unsigned int fn);
	bool isInterrupted(unsigned int fn);
	bool isGraduated(unsigned int fn);
	bool isReadyToGraduate(unsigned int fn);
	unsigned int findingCourseOfStudent(unsigned int fn);
	String findingSpecialtyOfStudent(unsigned int fn);
	Subject findingSubjectAndSettingData(String subjectName, unsigned int studentCourse, String studentSpecialty);
	Student findStudent(unsigned int fn);
	void removeFromCurrentSpecialty(unsigned int fn);
	void addToNewSpecialty(const Student & student, String newSpecialty);
	

	
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
	void advance(unsigned int fn);
	void changeSpecialty(unsigned int fn, String newSpecialty);
	void changeGroup(unsigned int fn, unsigned int newGroup);
	void graduate(unsigned int fn);
	void interrupt(unsigned int fn);
	void resume(unsigned int fn);
	void print(unsigned int fn);
	void print_all(String specialtyName, unsigned int course);
	void enroll_in(unsigned int fn, Subject subject);
	void add_grade(unsigned int fn, Subject subjectToCompareWith, float grade);
	void protocol(String subjectName);
	void report(unsigned int fn);

	//Functions for preparing data
	void prepareAdd_Specialty(String input, int currentIndex);
	void prepareAdd_Subject(String input, int currentIndex);
	void prepareEnroll(String input, int currentIndex);
	void prepareAdvance(String input, int currentIndex);
	void prepareChange(String input, int currentIndex);
	void prepareGraduate(String input, int currentIndex);
	void prepareInterrupt(String input, int currentIndex);
	void prepareResume(String input, int currentIndex);
	void preparePrint(String input, int currentIndex);
	void preparePrint_All(String input, int currentIndex);
	void prepareEnroll_In(String input, int currentIndex);
	void prepareAdd_Grade(String input, int currentIndex);
	void prepareProtocol(String input, int currentIndex);
	void prepareReport(String input, int currentIndex);
};

