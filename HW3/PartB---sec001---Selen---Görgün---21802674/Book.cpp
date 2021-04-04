using namespace std;
#include <string>
#include <iostream>
#include "Book.h"

/*
 * Selen Görgün
 * 21802674
 */

//Constructor
Book::Book(const int bookId = 0, const string bookName = "", const int bookYear = 0){
    this->bookId = bookId;
    this->bookName = bookName;
    this->bookYear = bookYear;
}

//Default Constructor
Book::Book(){
    bookId = 0;
    bookName = "";
    bookYear = 0;
}

//Assignment Operator
Book& Book::operator=(const Book& b){
    if(this == &b){
        return *this;
    }
    
    bookId = b.bookId;
    bookName = b.bookName;
    bookYear = b.bookYear;
    
    return *this;
}

//Copy Constructor
Book::Book(const Book &b){
    bookId = b.bookId;
    bookName = b.bookName;
    bookYear = b.bookYear;
}
int Book::getBookId(){
    return bookId;
}
void Book::setBookId(const int bookId){
    this->bookId = bookId;
}
string Book::getBookName(){
    return bookName;
}
void Book::setBookName(const string bookName){
    this->bookName = bookName;
}
int Book::getBookYear(){
    return bookYear;
}
void Book::setBookYear(const int bookYear){
    this->bookYear = bookYear;
}