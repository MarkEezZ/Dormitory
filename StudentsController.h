#pragma once
#include <list>
#include "Student.h"
#include "Sorts.h"
#include "Searches.h"

list<Student> getAllStudents(Sorts sort);
Student getStudentByName(string studentName, Searches search);

void addStudentToFile(Student studentData);
void addStudentsToFile(list<Student> studentsData);

void updateStudent(string studentName);
void updateStudents(list<string> studentsNames);

void deleteStudent(string studentName);
void deleteStudents(list<string> studentsNames);
void deleteAllStudents();