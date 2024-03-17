#pragma once
#include <list>
#include "Student.h"

list<map<string, string>> parseStudentsData(list<Student> studentsToRecords);
map<string, string> parseStudentData(Student studentToRecord);

list<Student> parseRecordsData(list<map<string, string>> studentRecords);
Student parseRecordData(map<string, string> studentRecord);