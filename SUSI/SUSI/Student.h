#pragma once

#include "String.h"
#include "Vector.cpp"
#include "Subject.h"

class Student
{
private:
	String name;
	unsigned int fn;	//faculty number
	String specialty;
	unsigned int course;
	unsigned int group;
	String status;		/* enrolled/interrupted/graduated */
	float averageGrade;
	Vector<Subject> subjects;

public:
	Student();
	Student(String _name, unsigned int _fn, String _specialty, unsigned int group);
	Student& operator= (const Student& other);
	~Student();

	bool operator== (const Student& other);	//needed for the containsElement method in class Vector
	bool operator!= (const Student& other);
	
	String getName() const;
	unsigned int getFN() const;
	String getSpecialty() const;
	unsigned int getCourse() const;
	unsigned int getGroup() const;
	String getStatus() const;
	float getAverageGrade() const;
	Vector<Subject> getSubjects() const;
	float getGrade(String subjectName) const;

	bool isReadyToAdvance();
	bool isReadyToChangeSpecialty();
	bool isReadyToGraduate();
	bool isInterrupted();
	bool isGraduated();
	bool hasThisSubject(String subjectName);

	void advance();
	void setNewGroup(unsigned int newGroup);
	void setNewSpecialty(String newSpecialty);
	void graduate();
	void interrupt();
	void resume();
	void enrollInSubject(Subject subject);
	bool hasPassedExam(Subject subjectToCompareWith);
	void setGradeToSubject(Subject subjectToCompareWith, float grade);
	void updateAverageGrade();
	void removeUnpassedElectiveSubjects();

};

std::ostream& operator<< (std::ostream& out, Student student);
