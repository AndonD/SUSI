#pragma once

#include "String.h"
#include "Vector.cpp"
#include "Student.h"
#include "Subject.h"

class Specialty
{
private:
	String name;
	Vector<Student> students;
	Vector<Subject> subjects;

public:
	Specialty();
	Specialty(const Specialty &other);
	Specialty(String _name);
	Specialty& operator= (const Specialty &other);
	~Specialty();
	
	bool isRegisteredSubject(const Subject &subject);
	bool isRegisteredStudent(const Student &student);
	bool isPassedExam(unsigned int facultyNumber, Subject subjectToCompareWith);
	bool isReadyToAdvance(unsigned int facultyNumber);
	bool isReadyToChangeSpecialty(unsigned int facultyNumber);
	bool isReadyToGraduate(unsigned int facultyNumber);
	bool isInterruptedStudent(unsigned int facultyNumber);
	bool isGraduatedStudent(unsigned int facultyNumber);
	bool hasThisSubject(unsigned int facultyNumber, String subjectName);

	bool operator== (const Specialty &other);
	bool operator!= (const Specialty &other);
	String getName() const;
	Vector<Student> getStudents() const;
	Vector<Subject> getSubjects() const;

	Student findStudent(unsigned int facultyNumber);

	void add_subject(const Subject &subjectToAdd);
	void enroll_student(const Student &studentToEnroll);
	void advanceStudent(unsigned int facultyNumber);
	void changeGroupOfStudent(unsigned int facultyNumber, unsigned int newGroup);
	void graduateStudent(unsigned int facultyNumber);
	void interruptStudent(unsigned int facultyNumber);
	void resumeStudent(unsigned int facultyNumber);
	void enrollStudentInSubject(unsigned int facultyNumber, Subject subject);
	void addGradeToSubject(unsigned int facultyNumber, Subject subjectToCompareWith, float grade);
	void removeStudent(unsigned int facultyNumber);
	void addToNewSpecialty(const Student &student);
	void protocol(String subjectName);
	void report(unsigned int facultyNumber);
};

std::ostream& operator<< (std::ostream &out, Specialty specialty);