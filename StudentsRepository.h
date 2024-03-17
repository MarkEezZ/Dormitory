#pragma once
#include <list>
#include "Student.h"

list<map<string, string>> getAllFromFile();
list<map<string, string>> getFromFileByCondition(map<string, string> condition);
void addToFile(list<map<string, string>> studentRecords);
void updateInFile(list<map<string, string>> studentRecordsToUpdate);
void deleteFromFile(list<string> studentRecordsToDelete);
void deleteAllFromFile();