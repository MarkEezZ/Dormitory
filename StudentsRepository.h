#pragma once
#include <list>
#include "Student.h"

list<map<string, string>> getAllFromFile();
list<map<string, string>> getFromFileByCondition(pair<string, string> condition);
void addToFile(list<map<string, string>> studentsRecords);
void updateInFile(list<map<string, string>> studentsRecordsToUpdate);
void deleteFromFile(pair<string, string> conditionToDelete);
void deleteAllFromFile();