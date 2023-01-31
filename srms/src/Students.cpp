#include "Students.hpp"

Students::Students(int p_grade, char p_section)
    : grade(p_grade), section(p_section), present_students(std::vector<int>{}) {
    filename =
        "STUDENTS" + std::to_string(grade) + std::to_string(p_section) + ".DAT";
    fill_present_students();
}

Errors Students::addStudent(Student s) {
    if (std::find(present_students.begin(), present_students.end(),
                  s.roll_no) != present_students.end()) {
        std::cout << "Student is already present" << std::endl;
        return Errors::ROLL_ALREADY_PRESENT;
    }
    std::ofstream file(filename,
                       std::ios::out | std::ios::app | std::ios::binary);
    if (!file)
        return Errors::FILE_OPEN_ERROR;
    file.write(reinterpret_cast<char *>(&s), sizeof(s));
    file.close();
    present_students.push_back(s.roll_no);
    return Errors::NO_ERROR;
}

Errors Students::returnRecord(std::vector<Student> &svector) {
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    if (!infile)
        return Errors::FILE_OPEN_ERROR;
    else if (present_students.empty())
        return Errors::EMPTY_STUDENTS;
    infile.seekg(0);
    Student s;
    svector.clear();
    infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    while (!infile.eof()) {
        svector.push_back(s);
        infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    }
    infile.close();
    return Errors::NO_ERROR;
}

void Students::fill_present_students() {
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    infile.seekg(0);
    if (!infile)
        return;
    Student s;
    infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    while (!infile.eof()) {
        if (s.roll_no)
            present_students.push_back(s.roll_no);
        infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    }
    infile.close();
}

Errors Students::returnSingleRecord(int p_roll, Student &student) {
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    if (!infile)
        return Errors::FILE_OPEN_ERROR;
    else if (present_students.empty())
        return Errors::EMPTY_STUDENTS;
    infile.seekg(0);
    Student s;
    infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    while (!infile.eof()) {
        if (s.roll_no == p_roll) {
            student = s;
            break;
        }
        infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    }
    infile.close();
    return Errors::NO_ERROR;
}

Errors Students::modifyData(Student student) {
    if (std::find(present_students.begin(), present_students.end(),
                  student.roll_no) == present_students.end()) {
        std::cerr << "The student with that roll number doesnot exist."
                  << std::endl;
        return Errors::ROLL_ABSENT;
    }
    std::fstream file(filename,
                      std::ios::out | std::ios::in | std::ios::binary);
    if (!file)
        return Errors::FILE_OPEN_ERROR;
    bool found = false;
    Student s;
    file.read(reinterpret_cast<char *>(&s), sizeof(s));
    while (!file.eof() && found == false) {
        if (s.roll_no == student.roll_no) {
            auto pos = -1 * sizeof(s);
            file.seekg(pos, std::ios::cur);
            file.write(reinterpret_cast<char *>(&student), sizeof(student));
            found = true;
            break;
        }
        file.read(reinterpret_cast<char *>(&s), sizeof(s));
    }
    file.close();
    return Errors::NO_ERROR;
}

Errors Students::deleteStudent(int p_roll) {
    if (std::find(present_students.begin(), present_students.end(), p_roll) ==
        present_students.end()) {
        std::cerr << "The student with that roll number exists." << std::endl;
        return Errors::ROLL_ABSENT;
    }
    std::ifstream infile(filename, std::ios::in);
    if (!infile)
        return Errors::FILE_OPEN_ERROR;
    std::ofstream outfile("TEMP.DAT", std::ios::out);
    if (!outfile)
        return Errors::FILE_OPEN_ERROR;
    infile.seekg(0, std::ios::beg);
    Student student;
    infile.read(reinterpret_cast<char *>(&student), sizeof(student));
    while (!infile.eof()) {
        if (student.roll_no != p_roll)
            outfile.write(reinterpret_cast<char *>(&student), sizeof(student));
        infile.read(reinterpret_cast<char *>(&student), sizeof(student));
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());
    rename("TEMP.DAT", filename.c_str());
    return Errors::NO_ERROR;
}

Errors Students::showMarks(Student &student) {
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    if (!infile)
        return Errors::FILE_OPEN_ERROR;
    else if (present_students.empty())
        return Errors::EMPTY_STUDENTS;
    infile.seekg(0);
    Student s;
    infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    while (!infile.eof()) {
        if (s.roll_no == student.roll_no) {
            break;
        }
        infile.read(reinterpret_cast<char *>(&s), sizeof(s));
    }
    infile.close();
    if (s.marksheet.filled) {
        for (int i = 0; i < 8; i++) {
            student.marksheet.marks[i] = s.marksheet.marks[i];
        }
        student.marksheet.filled = true;
        student.marksheet.term = s.marksheet.term;
        std::memcpy(student.name, s.name, sizeof(s.name));
        return Errors::NO_ERROR;
    }
    return Errors::MARKSHEET_EMPTY;
}

Errors Students::editMarks(Student &student) {
    if (std::find(present_students.begin(), present_students.end(),
                  student.roll_no) == present_students.end()) {
        std::cerr << "The student with that roll number doesnot exist."
                  << std::endl;
        return Errors::ROLL_ABSENT;
    }
    std::fstream file(filename,
                      std::ios::out | std::ios::in | std::ios::binary);
    if (!file)
        return Errors::FILE_OPEN_ERROR;
    bool found = false;
    Student s;
    file.read(reinterpret_cast<char *>(&s), sizeof(s));
    while (!file.eof() && found == false) {
        if (s.roll_no == student.roll_no) {
            std::memcpy(student.name, s.name, sizeof(s.name));
            student.roll_no = s.roll_no;
            student.marksheet.filled = true;
            auto pos = -1 * sizeof(s);
            file.seekg(pos, std::ios::cur);
            file.write(reinterpret_cast<char *>(&student), sizeof(student));
            found = true;
            break;
        }
        file.read(reinterpret_cast<char *>(&s), sizeof(s));
    }
    file.close();
    return Errors::NO_ERROR;
}
