using namespace std;
#include <string>
#include <iostream>
#include "LibrarySystem.h"
#include "Student.h"
#include "Book.h"

/*
 * Selen Görgün
 * 21802674
 */
 
//Constructor
LibrarySystem::LibrarySystem(){
    studentNum = 0;
    checkedBookNum = 0;
    nonCheckedBookNum = 0;
    
    studentHead = NULL;
    checkedBookHead = NULL;
    nonCheckedBookHead = NULL;
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
    
    while(checkedBookNum != 0){
        if(checkedBookNum == 1){
            delete checkedBookHead;
        }
        else{
            BookNode* cur = checkedBookHead;
            checkedBookHead = checkedBookHead->bookNext;
        
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        checkedBookNum--;
    }
    
    while(nonCheckedBookNum != 0){
        if(nonCheckedBookNum == 1){
            delete nonCheckedBookHead;
        }
        else{
            BookNode* cur = nonCheckedBookHead;
            nonCheckedBookHead = nonCheckedBookHead->bookNext;
        
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        nonCheckedBookNum--;
    }
}

//Add the new book to the non-checked list.
void LibrarySystem::addBook(const int bookId, const string bookName, const int bookYear){
    if(bookExists(bookId)){
        cout << "Book " << bookId << " already exists." << endl;
    }
    else{
        BookNode* newBook = new BookNode;
        newBook->b = Book(bookId, bookName, bookYear);
        
        if(nonCheckedBookNum == 0){
            nonCheckedBookHead = newBook;
            newBook->bookNext = NULL;
        }
        else{
            BookNode* prev = findNonCheckedBook(nonCheckedBookNum - 1);
            prev->bookNext = newBook;
            newBook->bookNext = NULL;
        }
        nonCheckedBookNum++;
        cout << "Book " << bookId << " has been added." << endl;
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

LibrarySystem::BookNode* LibrarySystem::findCheckedBook(const int index) const{
    BookNode* cur = checkedBookHead;
    for(int skip = 0; skip < index; skip++){
        cur = cur->bookNext;
    }
    return cur;
}

LibrarySystem::BookNode* LibrarySystem::findNonCheckedBook(const int index) const{
    BookNode* cur = nonCheckedBookHead;
    for(int skip = 0; skip < index; skip++){
        cur = cur->bookNext;
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

//Checks both book lists to find if the student with the given number exists in the system.
bool LibrarySystem::bookExists(const int bookId) const{
    bool exists = false;
    
    for(BookNode* cur = checkedBookHead; cur != NULL; cur = cur->bookNext){
        if(cur->b.getBookId() == bookId){
            exists = true;
            break;
        }
    }
    
    for(BookNode* cur = nonCheckedBookHead; cur != NULL; cur = cur->bookNext){
        if(cur->b.getBookId() == bookId){
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
        
        //Return the student's all books and delete them from student's book list.
        for(int a = 0; a < checkedBookNum; a++){
            if(findStudent(index)->s.bookAdded(findCheckedBook(a)->b.getBookId())){
                findStudent(index)->s.deleteBook(findCheckedBook(a)->b.getBookId());
                returnBook(findCheckedBook(a)->b.getBookId());
                a--;
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

void LibrarySystem::deleteBook(const int bookId){
    if(!bookExists(bookId)){
        cout << "Book " << bookId << " does not exist." << endl;
    }
    else{
        if(checkedOut(bookId)){
            //Returns the book and puts it to the non-checked book list.
            returnBook(bookId);
        }
        int index = 0;
        for(int i = 0; i < nonCheckedBookNum; i++){
            if(findNonCheckedBook(i)->b.getBookId() == bookId){
                index = i;
            }
        }
            
        if(nonCheckedBookNum == 1){
            delete nonCheckedBookHead;
            nonCheckedBookHead = NULL;
        }
        else{
            BookNode* cur;
            if(index == 0){
                cur = nonCheckedBookHead;
                nonCheckedBookHead = nonCheckedBookHead->bookNext;
            }
            else{
                BookNode* prev = findNonCheckedBook(index - 1);
                cur = prev->bookNext;
                prev->bookNext = cur->bookNext; 
            }
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        nonCheckedBookNum--;
        cout << "Book " << bookId << " has been deleted." << endl;
    }
}

void LibrarySystem::checkoutBook(const int bookId, const int studentId){
    if(!bookExists(bookId)){
        cout << "Book " << bookId << " does not exist for checkout." << endl;
    }
    else if(checkedOut(bookId)){
        cout << "Book " << bookId << " has been already checked out by another student." << endl;
    }
    else if(!studentExists(studentId)){
        cout << "Student " << studentId << " does not exist." << endl;
    }
    else{
        int year = 0;
        string name = "";
        for(BookNode* cur = nonCheckedBookHead; cur != NULL; cur = cur->bookNext){
            if(cur->b.getBookId() == bookId){
                name = cur->b.getBookName();
                year = cur->b.getBookYear();
            }
        }
        
        for(int i = 0; i < studentNum; i++){
            if(findStudent(i)->s.getStudentId() == studentId){
                findStudent(i)->s.addBook(bookId, name, year);
                break;
            }
        }
        toggleBook(bookId); //Makes the checked out book returned. 
        cout << "Book " << bookId << " has been checked out by student " << studentId << endl;
    }
}

//Makes the book checked if the book is non-checked and non-checked if the book checked-out.
void LibrarySystem::toggleBook(const int bookId){
    if(checkedOut(bookId)){
        int checkedIndex = 0; 
        int year = 0;
        string name = "";
        for(int i = 0; i < checkedBookNum; i++){
            if(findCheckedBook(i)->b.getBookId() == bookId){
                checkedIndex = i;
            }
        }
        
        name = findCheckedBook(checkedIndex)->b.getBookName();
        year = findCheckedBook(checkedIndex)->b.getBookYear();
        
        //Add to the unchecked list
        BookNode* newB = new BookNode;
        newB->b = Book(bookId, name, year);
        if(nonCheckedBookNum == 0){
            nonCheckedBookHead = newB;
            newB->bookNext = NULL;
        }
        else{
            BookNode* prev = findNonCheckedBook(nonCheckedBookNum - 1);
            prev->bookNext = newB;
            newB->bookNext = NULL; 
        }
        
        //Remove from the checked list
        if(checkedBookNum == 1){
            delete checkedBookHead;
            checkedBookHead = NULL;
        }
        else{
            BookNode* cur;
            if(checkedIndex == 0){
                cur = checkedBookHead;
                checkedBookHead = checkedBookHead->bookNext;
            }
            else{
                BookNode* prev = findCheckedBook(checkedIndex - 1);
                cur = prev->bookNext;
                prev->bookNext = cur->bookNext; 
            }
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        nonCheckedBookNum++;
        checkedBookNum--;
        
    }
    else{
        int nonCheckedIndex = 0; 
        int year = 0;
        string name = "";
        for(int i = 0; i < nonCheckedBookNum; i++){
            if(findNonCheckedBook(i)->b.getBookId() == bookId){
                nonCheckedIndex = i;
            }
        }
        
        name = findNonCheckedBook(nonCheckedIndex)->b.getBookName();
        year = findNonCheckedBook(nonCheckedIndex)->b.getBookYear();
        
        //Add to the checked list
        BookNode* newB = new BookNode;
        newB->b = Book(bookId, name, year);
        if(checkedBookNum == 0){
            checkedBookHead = newB;
            newB->bookNext = NULL;
        }
        else{
            BookNode* prev = findCheckedBook(checkedBookNum - 1);
            prev->bookNext = newB;
            newB->bookNext = NULL; 
        }
        
        //Remove from the non-checked list
        if(nonCheckedBookNum == 1){
            delete nonCheckedBookHead;
            nonCheckedBookHead = NULL;
        }
        else{
            BookNode* cur;
            if(nonCheckedIndex == 0){
                cur = nonCheckedBookHead;
                nonCheckedBookHead = nonCheckedBookHead->bookNext;
            }
            else{
                BookNode* prev = findNonCheckedBook(nonCheckedIndex - 1);
                cur = prev->bookNext;
                prev->bookNext = cur->bookNext; 
            }
            cur->bookNext = NULL;
            delete cur;
            cur = NULL;
        }
        nonCheckedBookNum--;
        checkedBookNum++;
    }
}

void LibrarySystem::returnBook(const int bookId){
    if(!bookExists(bookId)){
        cout << "Book " << bookId << " does not exist." << endl; 
    }
    else if(!checkedOut(bookId)){
        cout << "Book " << bookId << " has not been checked out." << endl;
    }
    else{
        //Deletes the book from the student's book list
        for(StudentNode* cur = studentHead; cur != NULL; cur = cur->studentNext){
            if(cur->s.bookAdded(bookId)){
                cur->s.deleteBook(bookId);
            }
        }
        toggleBook(bookId); //Makes the book non-checked
        cout << "Book " << bookId << " has been returned." << endl;
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
                cout << "Student " << studentId << " has checked out the following books:" << endl;
                cur->s.showBooks();
            }
        }
    }
}

//Finds if the book with the given id checked out by someone.
bool LibrarySystem::checkedOut(const int bookId) const{
    bool checkedOut = false;
    
    for(BookNode* cur = checkedBookHead; cur != NULL; cur = cur->bookNext){
        if(cur->b.getBookId() == bookId){
            checkedOut = true;
            break;
        }
    }
    return checkedOut;
}

void LibrarySystem::showBook(const int bookId) const{
    if(!bookExists(bookId)){
        cout << "Book " << bookId << " does not exist." << endl;
    }
    else{
        if(checkedOut(bookId)){
            for(BookNode* cur = checkedBookHead; cur != NULL; cur = cur->bookNext){
                if(cur->b.getBookId() == bookId){
                    cout << bookId << "     " << cur->b.getBookName() << "     " << cur->b.getBookYear() << "     ";
                }
            }
            
            for(StudentNode* cur = studentHead; cur != NULL; cur = cur->studentNext){
                if(cur->s.bookAdded(bookId)){
                    cout << "Checked out by student " << cur->s.getStudentId() << endl;
                }
            }
        }
        else{
            for(BookNode* cur = nonCheckedBookHead; cur != NULL; cur = cur->bookNext){
                if(cur->b.getBookId() == bookId){
                    cout << bookId << "     " << cur->b.getBookName() << "     " << cur->b.getBookYear() << "     ";
                }
            }
            cout << "Not checked out." << endl;
        }
    }
}

void LibrarySystem::showAllBooks() const{
    cout << "Book id   " << "Book name       " << "Year  " << "Status" << endl;
    for(int i = 0; i < nonCheckedBookNum; i++){
        showBook(findNonCheckedBook(i)->b.getBookId());
    }
    for(int i = 0; i < checkedBookNum; i++){
        showBook(findCheckedBook(i)->b.getBookId());
    }
}