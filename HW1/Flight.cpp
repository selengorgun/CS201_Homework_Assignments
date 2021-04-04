#include <iostream>
#include <string>
#include "Flight.h"

using namespace std;

Flight::Flight(const int flightNo = 0, const int rowNo = 0, const int columnNo = 0){
    flightNum = flightNo;
    columnNum = columnNo;
    rowNum = rowNo;
    numOfAvailableSeats = rowNo*columnNo;
    
    airCraft = new char*[columnNo];
    for(int i = 0; i < rowNo; i++){
        airCraft[i] = new char[rowNo];
    }
    for(int a = 0; a < columnNo; a++){
        for(int b = 0; b < rowNo; b++){
            airCraft[a][b] = 'o';
        }
    }
}
Flight::Flight(){
    flightNum = 0;
    rowNum = 0;
    columnNum = 0;
    airCraft = NULL;
    numOfAvailableSeats= 0;
}
Flight::~Flight(){
    if(airCraft != NULL){
        cout<< "t" << endl;
        for (int i = 0; i < columnNum; i++){
            cout<< "j" << endl;
            delete[] airCraft[i];
            cout<< "k" << endl;
        }
        delete[] airCraft;
        cout<< "m" << endl;
    }
    airCraft = NULL;
}
Flight& Flight::operator=(const Flight& f){
    if(this == &f){
        return *this;
    }
    if(airCraft != NULL){
        for (int i = 0; i < columnNum; i++){
            cout<< "a" << endl;
            delete[] airCraft[i];
            cout<< "b" << endl;
        }
        cout<< "c" << endl;
        delete[] airCraft;
        cout<< "d" << endl;
    }
    flightNum = f.flightNum;
    rowNum = f.rowNum;
    columnNum = f.columnNum;
    numOfAvailableSeats = f.numOfAvailableSeats;
    airCraft = new char*[columnNum];
    for(int i = 0; i < rowNum; i++){
        airCraft[i] = new char[rowNum];
    }
    for(int a = 0; a < columnNum; a++){
        for(int b = 0; b < rowNum; b++){
            airCraft[a][b] = 'o';
        }
    }
    return *this;
}
Flight::Flight(const Flight &f){
    flightNum = f.flightNum;
    rowNum = f.rowNum;
    columnNum = f.columnNum;
    numOfAvailableSeats = f.numOfAvailableSeats;
    airCraft = new char*[columnNum];
    for(int i = 0; i < rowNum; i++){
        airCraft[i] = new char[rowNum];
    }
    for(int a = 0; a < columnNum; a++){
        for(int b = 0; b < rowNum; b++){
            airCraft[a][b] = 'o';
        }
    }
}
int Flight::getFlightNum(){
    return flightNum;
}
int Flight::getRowNum(){
    return rowNum;
}
int Flight::getColumnNum(){
    return columnNum;
}
char** Flight::getAirCraft(){
    return airCraft;
}
int Flight::getNumOfAvailableSeats(){
    return numOfAvailableSeats;
}
bool Flight::isAvailable(const int columnNo, const int rowNo){
    bool available = false;
    if(airCraft[columnNo - 1][rowNo - 1] == 'o'){
        available = true;
    }
    return available;
}
void Flight::setNumOfAvailableSeats(const int newSeatNum){
    numOfAvailableSeats = newSeatNum;
}