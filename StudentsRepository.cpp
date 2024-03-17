#include "StudentsRepository.h"
#include <fstream>
#include <iostream>
#include "DbPath.h"
#include "StringService.h"

list<map<string, string>> getAllFromFile()
{
    ifstream fin;
    list<map<string, string>> studentsRecords;

    try {
        cout << "Сообщение: Попытка открытия файла.\n";
        fin.open(DB_PATH);
        cout << "Сообщение: Файл успешно открыт.\n";

        string rawRecord;

        while (!fin.eof()) {
            rawRecord = "";
            getline(fin, rawRecord);

            map<string, string> studentRecord;

            if (rawRecord != "\n") {
                string key = "";
                string value = "";
                bool isKey = true;

                for (char ch: rawRecord) {
                    if (ch != ':') {
                        isKey = false;
                        continue;
                    }
                    if (isKey && ch != '\n') {
                        key += ch;
                    }
                    else if (!isKey && ch != '\n') {
                        value += ch;
                    }
                }
                trim(key); 
                trim(value);

                pair<string, string> pair;
                pair.first = key;
                pair.second = value;

                studentRecord.insert(pair);
            }
            else {
                studentsRecords.push_back(studentRecord);
            }
        }
        fin.close();

        return studentsRecords;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cout << "Ошибка: Не удалось открыть файл.\n";
    }
}


list<map<string, string>> getFromFileByCondition(pair<string, string> condition)
{
    ifstream fin;
    list<map<string, string>> studentsRecords;

    try {
        cout << "Сообщение: Попытка открытия файла.\n";
        fin.open(DB_PATH);
        cout << "Сообщение: Файл успешно открыт.\n";

        string rawRecord;

        while (!fin.eof()) {
            rawRecord = "";
            getline(fin, rawRecord);

            bool isRecordPushed = false;
            map<string, string> studentRecord;

            if (rawRecord != "\n") {
                string key = "";
                string value = "";
                bool isKey = true;

                for (char ch : rawRecord) {
                    if (ch != ':') {
                        isKey = false;
                        continue;
                    }
                    if (isKey && ch != '\n') {
                        key += ch;
                    }
                    else if (!isKey && ch != '\n') {
                        value += ch;
                    }
                }
                trim(key);
                trim(value);

                pair<string, string> pair;
                pair.first = key;
                pair.second = value;

                studentRecord.insert(pair);
            }
            else {
                if (!isRecordPushed && checkCondition(studentRecord, condition)) {
                    studentsRecords.push_back(studentRecord);
                    isRecordPushed = true;
                }
            }
        }
        fin.close();

        return studentsRecords;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cout << "Ошибка: Не удалось открыть файл.\n";
    }
}


bool checkCondition(map<string, string>& studentRecord, pair<string, string>& condition) {
    for (pair<string, string> pair : studentRecord) {
        if (pair.first == condition.first && pair.second == condition.second) {
            return true;
        }
    }
    return false;
}


void addToFile(list<map<string, string>> studentsRecords) {
    ofstream fout;

    try {
        cout << "Сообщение: Попытка открытия файла.\n";
        fout.open(DB_PATH, ofstream::app);
        cout << "Сообщение: Файл успешно открыт.\n";

        for (map<string, string> studentRecord: studentsRecords) {
            for (pair<string, string> pair: studentRecord)
            {
                fout << pair.first << ": " << pair.second << endl;
            }
            fout << endl;
        }

        cout << "Сообщение: Добавлена запись в файл.\n";
        fout.close();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cout << "Ошибка: Не удалось открыть файл.\n";
    }
}


void updateInFile(list<map<string, string>> studentsRecordsToUpdate)
{
    list<map<string, string>> studentsRecords = getAllFromFile();
    list<map<string, string>> updatedStudentsRecords;
    
    for (map<string, string> studentRecord : studentsRecords) {
        for (map<string, string> studentRecordToUpdate : studentsRecordsToUpdate) {
            if (studentRecord.begin()->first == studentRecordToUpdate.begin()->first &&
                studentRecord.begin()->second == studentRecordToUpdate.begin()->second) {
                updatedStudentsRecords.push_back(studentRecordToUpdate);
            }
            else {
                updatedStudentsRecords.push_back(studentRecord);
            }
        }
    }
    deleteAllFromFile();
    addToFile(updatedStudentsRecords);
}


void deleteFromFile(pair<string, string> conditionToDelete)
{
    ifstream fin;
    list<map<string, string>> studentsRecordsUpdated;

    try {
        cout << "Сообщение: Попытка открытия файла.\n";
        fin.open(DB_PATH);
        cout << "Сообщение: Файл успешно открыт.\n";

        string rawRecord;

        while (!fin.eof()) {
            rawRecord = "";
            getline(fin, rawRecord);

            bool isRecordPushed = false;
            map<string, string> studentRecord;

            if (rawRecord != "\n") {
                string key = "";
                string value = "";
                bool isKey = true;

                for (char ch : rawRecord) {
                    if (ch != ':') {
                        isKey = false;
                        continue;
                    }
                    if (isKey && ch != '\n') {
                        key += ch;
                    }
                    else if (!isKey && ch != '\n') {
                        value += ch;
                    }
                }
                trim(key);
                trim(value);

                pair<string, string> pair;
                pair.first = key;
                pair.second = value;

                studentRecord.insert(pair);
            }
            else {
                if (!isRecordPushed && !checkCondition(studentRecord, conditionToDelete)) {
                    studentsRecordsUpdated.push_back(studentRecord);
                    isRecordPushed = true;
                }
            }
        }
        fin.close();

        deleteAllFromFile();
        addToFile(studentsRecordsUpdated);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cout << "Ошибка: Не удалось открыть файл.\n";
    }
}


void deleteAllFromFile()
{
    ofstream fout;

    try {
        cout << "Сообщение: Попытка открытия файла.\n";
        fout.open(DB_PATH, std::ofstream::out | std::ofstream::trunc);
        cout << "Сообщение: Файл успешно открыт.\n";

        fout.clear();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cout << "Ошибка: Не удалось открыть файл.\n";
    }
}
