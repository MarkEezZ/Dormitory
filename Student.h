#pragma once
#include <string>
#include <map>

using namespace std;

struct Student {
public:
	string name;
	string group;
	string averageMark;
	map<string, double> familyIncome;

	Student();
	Student(string name, string group, string averageMark, map<string, double> familyIncome);

	double countAverageIncome();
};