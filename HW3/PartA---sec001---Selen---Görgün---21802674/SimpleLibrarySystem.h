#ifndef __SIMPLELIBRARYSYSTEM_H
#define __SIMPLELIBRARYSYSTEM_H

using namespace std;
#include <string>
#include <iostream>
#include "SimpleStudent.h"

/*
 * Selen Görgün
 * 21802674
 */

class LibrarySystem{
public:
    LibrarySystem();
    LibrarySystem(const LibrarySystem &ls);
    ~LibrarySystem();
    void addStudent(const int studentId, const string studentName); 
    void deleteStudent(const int studentId);
    void showStudent(const int studentId) const;
private:
    struct StudentNode{
        Student s;
        StudentNode* studentNext;
    };
    StudentNode* studentHead;
    int studentNum;
    StudentNode* findStudent(const int index) const;
    bool studentExists(const int studentId)const;
};

#endif