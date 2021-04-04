using namespace std;
#include <string>
#include <iostream>
#include "Student.h"
#include "Book.h"

/*
 * Selen Görgün
 * 21802674
 */
 
//Constructor
Student::Student(const int studentId, const string studentName){
    this->studentId = studentId;
    this->studentName = studentName;
    bookHead = NULL;
    bookNum = 0;
}

//Default Constructor
Student::Student(){
    studentId = 0;
    studentName = "";
    bookNum = 0;
    bookHead = NULL;
}

//Assignment Operator
Student& Student::operator=(const Student& s){
    if(this == &s){
        return *this;
    }
    
    studentId = s.studentId;
    studentName = s.studentName;
    bookNum = s.bookNum;
    
    if(s.bookHead == NULL){
        bookHead = NULL;
    }
    else{
        bookHead = new BookNode;
        bookHead->b = s.bookHead->b;
        
        BookNode* newPtr = bookHead;
        
        for(BookNode* origPtr = s.bookHead->bookNext; origPtr != NULL; origPtr = origPtr->bookNext){
            newPtr->bookNext = new BookNode;
            newPtr = newPtr->bookNext;
            newPtr->b = origPtr->b;
        }
        newPtr->bookNext = NULL;
    }
    
    return *this;
}

//Copy Constructor
Student::Student(const Student& s){
    bookNum = s.bookNum;
    if(s.bookHead == NULL){
        bookHead = NULL;
    }
    else{
        bookHead = new BookNode;
        bookHead->b = s.bookHead->b;
        
        BookNode* newPtr = bookHead;
        
        for(BookNode* origPtr = s.bookHead->bookNext; origPtr != NULL; origPtr = origPtr->bookNext){
            newPtr->bookNext = new BookNode;
            newPtr = newPtr->bookNext;
            newPtr->b = origPtr->b;
        }
        newPtr->bookNext = NULL;
    }
}

//Destructor
Student::~Student(){
    while(bookNum != 0){
        if(bookNum == 1){
            delete bookHead;
        }
        else{
            BookNode* cur = bookHead;
            bookHead = bookHead->bookNext;
        
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        bookNum--;
    }
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

int Student::getBookNum(){
    return bookNum;
}

void Student::addBook(const int bookId, const string bookName, const int bookYear){
        BookNode* newBook = new BookNode;
        newBook->b = Book(bookId, bookName, bookYear);
        if(bookNum == 0){
            bookHead = newBook;
            newBook->bookNext = NULL;
        }
        else{
            BookNode* prev = findBook(bookNum - 1);
            prev->bookNext = newBook;
            newBook->bookNext = NULL;
        }
        bookNum++;
} 

Student::BookNode* Student::findBook(const int index) const{
    BookNode* cur = bookHead;
    for(int skip = 0; skip < index; skip++){
        cur = cur->bookNext;
    }
    return cur;
}

void Student::deleteBook(const int bookId){
        int index = 0;
        for(int i = 0; i < bookNum; i++){
            if(findBook(i)->b.getBookId() == bookId){
                index = i;
            }
        }
        
        if(bookNum == 1){
            delete bookHead;
            bookHead = NULL;
        }
        else{
            BookNode* cur;
            if(index == 0){
                cur = bookHead;
                bookHead = bookHead->bookNext;
            }
            else{
                BookNode* prev = findBook(index - 1);
                cur = prev->bookNext;
                prev->bookNext = cur->bookNext; 
            }
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        bookNum--;
}

void Student::showBooks(){
    if(bookNum == 0){
        cout << "Student " << studentId << " has no books." << endl;
    }
    else{
        cout << "Book id   " << "Book name             " << "Year" << endl;
        for(BookNode* cur = bookHead; cur != NULL; cur = cur->bookNext){
            cout << cur->b.getBookId() << "      " << cur->b.getBookName() <<  "   " << cur->b.getBookYear() << endl;
        }
    }
}

bool Student::bookAdded(const int bookId){
    bool added = false;
    
    for(BookNode* cur = bookHead; cur != NULL; cur = cur->bookNext){
        if(cur->b.getBookId() == bookId){
            added = true;
            break;
        }
    }
    
    return added;
}

