#ifndef __STUDENT_H
#define __STUDENT_H

using namespace std;
#include <string>
#include <iostream>
#include "Book.h"

/*
 * Selen Görgün
 * 21802674
 */

class Student{
public:
    Student(const int studentId, const string studentName);
    Student();
    ~Student();
    Student& operator=(const Student& s);
    Student(const Student &s);
    int getStudentId();
    void setStudentId(const int studentId);
    string getStudentName();
    void setStudentName(const string studentName);
    int getBookNum();
    void setBookNum(const int bookNum);
    void addBook(const int bookId, const string bookName, const int bookYear);
    void deleteBook(const int bookId);
    void showBooks();
    bool bookAdded(const int bookId);
private:
    string studentName;
    int studentId;
    
    struct BookNode{
        Book b;
        BookNode* bookNext;
    };
    BookNode* bookHead;
    
    int bookNum;
    BookNode* findBook(const int index) const;
};

#endif