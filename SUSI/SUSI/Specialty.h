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
	Specialty(String _name);
	~Specialty();
	
	bool isRegisteredSubject(const Subject& subject);
	bool isRegisteredStudent(const Student& student);
	bool isPassedExam(unsigned int fn, Subject subjectToCompareWith);
	bool isReadyToAdvance(unsigned int fn);
	bool isReadyToChangeSpecialty(unsigned int fn);
	bool isReadyToGraduate(unsigned int fn);
	bool isInterruptedStudent(unsigned int fn);
	bool isGraduatedStudent(unsigned int fn);

	bool operator== (const Specialty& other);
	bool operator!= (const Specialty& other);
	String getName() const;
	Vector<Student> getStudents() const;
	Vector<Subject> getSubjects() const;

	Student findStudent(unsigned int fn);

	void add_subject(const Subject& subjectToAdd);
	void enroll_student(const Student& studentToEnroll);
	void advanceStudent(unsigned int fn);
	void changeGroupOfStudent(unsigned int fn, unsigned int newGroup);
	void graduateStudent(unsigned int fn);
	void interruptStudent(unsigned int fn);
	void resumeStudent(unsigned int fn);
	void enrollStudentInSubject(unsigned int fn, Subject subject);
	void addGradeToSubject(unsigned int fn, Subject subjectToCompareWith, float grade);
	void removeStudent(unsigned int fn);
	void addToNewSpecialty(const Student & student);
	void protocol(String subjectName);
};

std::ostream& operator<< (std::ostream& out, Specialty specialty);