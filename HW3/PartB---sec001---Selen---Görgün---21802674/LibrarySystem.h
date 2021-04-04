#ifndef __LIBRARYSYSTEM_H
#define __LIBRARYSYSTEM_H

using namespace std;
#include <string>
#include <iostream>
#include "Student.h"
#include "Book.h"

/*
 * Selen Görgün
 * 21802674
 */

class LibrarySystem {
public:
    LibrarySystem();
    ~LibrarySystem();
    void addBook(const int bookId, const string bookName, const int bookYear);
    void deleteBook(const int bookId);
    void addStudent(const int studentId, const string studentName);
    void deleteStudent(const int studentId);
    void checkoutBook(const int bookId, const int studentId);
    void returnBook(const int bookId);
    void showAllBooks() const;
    void showBook(const int bookId) const;
    void showStudent(const int studentId) const;
private:
    struct StudentNode{
        Student s;
        StudentNode* studentNext;
    };
    StudentNode* studentHead;
    int studentNum;
    
    struct BookNode{
        Book b;
        BookNode* bookNext;
    };
    BookNode* checkedBookHead;
    BookNode* nonCheckedBookHead;
    int checkedBookNum;
    int nonCheckedBookNum;
    
    StudentNode* findStudent(const int index) const;
    bool studentExists(const int studentId)const;
    
    BookNode* findCheckedBook(const int index) const;
    BookNode* findNonCheckedBook(const int index) const;
    bool bookExists(const int bookId)const;
    
    bool checkedOut(const int bookId) const;
    void toggleBook(const int bookId);
};


#endif