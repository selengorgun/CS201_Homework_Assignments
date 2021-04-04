using namespace std;
#include <string>
#include <iostream>
#include "SimpleLibrarySystem.h"

/*
 * Selen Görgün
 * 21802674
 */
 
//Constructor
LibrarySystem::LibrarySystem(){
    studentNum = 0;
    studentHead = NULL;
}

//Copy Constructor
LibrarySystem::LibrarySystem(const LibrarySystem& ls){
    studentNum = ls.studentNum;
    if(ls.studentHead == NULL){
        studentHead = NULL;
    }
    else{
        studentHead = new StudentNode;
        studentHead->s = ls.studentHead->s;
        
        StudentNode* newPtr = studentHead;
        
        for(StudentNode* origPtr = ls.studentHead->studentNext; origPtr != NULL; origPtr = origPtr->studentNext){
            newPtr->studentNext = new StudentNode;
            newPtr = newPtr->studentNext;
            newPtr->s = origPtr->s;
        }
        newPtr->studentNext = NULL;
    }
}

//Destructor
LibrarySystem::~LibrarySystem(){
    while(studentNum != 0){
        if(studentNum == 1){
            delete studentHead;
        }
        else{
            StudentNode* cur = studentHead;
            studentHead = studentHead->studentNext;
        
            cur->studentNext = NULL;
            delete cur;
            cur = NULL;
        }
        studentNum--;
    }
}

void LibrarySystem::addStudent(const int studentId, const string studentName){
    if(studentExists(studentId)){
        cout << "Student " << studentId << " already exists." << endl;
    }
    else{
        StudentNode* newStu = new StudentNode;
        newStu->s = Student(studentId, studentName);
        if(studentNum == 0){
            studentHead = newStu;
            newStu->studentNext = NULL;
        }
        else{
            StudentNode* prev = findStudent(studentNum - 1);
            prev->studentNext = newStu;
            newStu->studentNext = NULL;
        }
        studentNum++;
        cout << "Student " << studentId << " has been added." << endl;
    }
} 

LibrarySystem::StudentNode* LibrarySystem::findStudent(const int index) const{
    StudentNode* cur = studentHead;
    for(int skip = 0; skip < index; skip++){
        cur = cur->studentNext;
    }
    return cur;
}

bool LibrarySystem::studentExists(const int studentId) const{
    bool exists = false;
    for(StudentNode* cur = studentHead; cur != NULL; cur = cur->studentNext){
        if(cur->s.getStudentId() == studentId){
            exists = true;
            break;
        }
    }
    return exists;
}

void LibrarySystem::deleteStudent(const int studentId){
    if(!studentExists(studentId)){
        cout << "Student " << studentId << " does not exist." << endl;
    }
    else{
        int index = 0;
        for(int i = 0; i < studentNum; i++){
            if(findStudent(i)->s.getStudentId() == studentId){
                index = i;
            }
        }
        
        if(studentNum == 1){
            delete studentHead;
            studentHead = NULL;
        }
        else{
            StudentNode* cur;
            if(index == 0){
            cur = studentHead;
            studentHead = studentHead->studentNext;
            }
            else{
                StudentNode* prev = findStudent(index - 1);
                cur = prev->studentNext;
                prev->studentNext = cur->studentNext; 
            }
            cur->studentNext = NULL;
            delete cur;
            cur = NULL;
        }
        studentNum--;
        cout << "Student " << studentId << " has been deleted." << endl;
    }
}

void LibrarySystem::showStudent(const int studentId) const{
    if(!studentExists(studentId)){
        cout << "Student " << studentId << " does not exist." << endl;
    }
    else{
        for(StudentNode* cur = studentHead; cur != NULL; cur = cur->studentNext){
            if(cur->s.getStudentId() == studentId){
                cout << "Student id: " << cur->s.getStudentId() << " Student name: " << cur->s.getStudentName() << endl;
            }
        }
    }
}