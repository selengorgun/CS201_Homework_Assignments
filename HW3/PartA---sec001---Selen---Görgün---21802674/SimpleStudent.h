#ifndef __SIMPLESTUDENT_H
#define __SIMPLESTUDENT_H

using namespace std;
#include <string>
#include <iostream>

/*
 * Selen Görgün
 * 21802674
 */

class Student{
public:
    Student(const int studentId, const string studentName);
    Student();
    Student& operator=(const Student& s);
    Student(const Student &s);
    int getStudentId();
    void setStudentId(const int studentId);
    string getStudentName();
    void setStudentName(const string studentName);
private:
    string studentName;
    int studentId;
};

#endif