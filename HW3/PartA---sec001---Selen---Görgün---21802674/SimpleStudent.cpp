using namespace std;
#include <string>
#include <iostream>
#include "SimpleStudent.h"

/*
 * Selen Görgün
 * 21802674
 */

//Constructor
Student::Student(const int studentId = 0, const string studentName = ""){
    this->studentId = studentId;
    this->studentName = studentName;
}

//Default Constructor
Student::Student(){
    studentId = 0;
    studentName = "";
}

//Assignment Operator
Student& Student::operator=(const Student& s){
    if(this == &s){
        return *this;
    }
    
    studentId = s.studentId;
    studentName = s.studentName;
    
    return *this;
}

//Copy Constructor
Student::Student(const Student &s){
    studentId = s.studentId;
    studentName = s.studentName;
}
int Student::getStudentId(){
    return studentId;
}
void Student::setStudentId(const int studentId){
    this->studentId = studentId;
}
string Student::getStudentName(){
    return studentName;
}
void Student::setStudentName(const string studentName){
    this->studentName = studentName;
}