#ifndef __BOOK_H
#define __BOOK_H

using namespace std;
#include <string>
#include <iostream>

/*
 * Selen Görgün
 * 21802674
 */

class Book{
public:
    Book(const int bookId, const string bookName, const int bookYear);
    Book();
    Book& operator=(const Book& s);
    Book(const Book &b);
    int getBookId();
    void setBookId(const int bookId);
    string getBookName();
    void setBookName(const string bookName);
    int getBookYear();
    void setBookYear(const int bookYear);
private:
    string bookName;
    int bookId;
    int bookYear;
};

#endif