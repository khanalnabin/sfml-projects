#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

enum class Errors {
    ROLL_ABSENT,
    FILE_OPEN_ERROR,
    EMPTY_STUDENTS,
    NO_ERROR,
    ROLL_ALREADY_PRESENT,
    MARKSHEET_EMPTY
};

const char subjects[8][50] = {
    "English",    "Math",        "Social",
    "Optional I", "Optional II", "Environment Health and Population",
    "Nepali",     "Science"};

struct Marks {
    int term;
    int marks[8];
    bool filled = false;
};

struct Student {
    char name[25];
    int roll_no;
    Marks marksheet;
};

class Students {
private:
    std::vector<Student> students;
    int grade;
    char section;
    std::string filename;
    std::vector<int> present_students;
    void fill_present_students();

public:
    Students(int p_grade, char p_section);
    Errors addStudent(Student p_student);
    Errors deleteStudent(int p_roll);
    Errors returnRecord(std::vector<Student> &p_svector);
    Errors returnSingleRecord(int p_roll, Student &student);
    Errors modifyData(Student student);
    Errors editMarks(Student& student);
    Errors showMarks(Student& student );
};
