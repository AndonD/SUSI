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
	bool isPassedExam(unsigned int facultyNumber, Subject subjectToCompare);
	bool isRegisteredStudentInSpecialty(unsigned int facultyNumber, String specialtyName);
	bool isRegisteredStudentByFacultyNumber(unsigned int facultyNumber);
	bool isReadyToAdvance(unsigned int facultyNumber);
	bool isReadyToChangeSpecialty(unsigned int facultyNumber);
	bool isInterrupted(unsigned int facultyNumber);
	bool isGraduated(unsigned int facultyNumber);
	bool isReadyToGraduate(unsigned int facultyNumber);
	unsigned int findingCourseOfStudent(unsigned int facultyNumber);
	String findingSpecialtyOfStudent(unsigned int facultyNumber);
	Subject findingSubjectAndSettingData(String subjectName, unsigned int studentCourse, String studentSpecialty);
	Student findStudent(unsigned int facultyNumber);
	void removeFromCurrentSpecialty(unsigned int facultyNumber);
	void addToNewSpecialty(const Student &student, String newSpecialty);
	

	
	//Basic command functions
	void open();
	void close();
	void save();
	void save_as();
	void help();

	//Specific command functions
	void add_specialty(Specialty specialty);
	void add_subject(String name, bool isCompulsory, unsigned int course, String specialtyName);
	void enroll(unsigned int facultyNumber, String specialty, unsigned int group, String name);
	void advance(unsigned int facultyNumber);
	void changeSpecialty(unsigned int facultyNumber, String newSpecialty);
	void changeGroup(unsigned int facultyNumber, unsigned int newGroup);
	void graduate(unsigned int facultyNumber);
	void interrupt(unsigned int facultyNumber);
	void resume(unsigned int facultyNumber);
	void print(unsigned int facultyNumber);
	void print_all(String specialtyName, unsigned int course);
	void enroll_in(unsigned int facultyNumber, Subject subject);
	void add_grade(unsigned int facultyNumber, Subject subjectToCompareWith, float grade);
	void protocol(String subjectName);
	void report(unsigned int facultyNumber);

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

