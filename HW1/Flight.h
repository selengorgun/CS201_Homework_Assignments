#ifndef __FLIGHT_H
#define __FLIGHT_H

using namespace std;
#include <string>
#include <iostream>

/*
 *Name: Selen 
 *Surname: Görgün
 *ID: 21802674
 */
 
 class Flight{
public:
    Flight(const int flightNo, const int rowNo, const int seatNo);
    Flight();
    ~Flight();
    Flight& operator=(const Flight& f);
    Flight(const Flight &f);
    int getNumOfAvailableSeats();
    int getFlightNum();
    int getRowNum();
    int getColumnNum();
    char** getAirCraft();
    bool isAvailable(const int columnNo, const int rowNo);
    void setNumOfAvailableSeats(const int newSeatNum);
private:
    int rowNum;
    int columnNum;
    int flightNum;
    int numOfAvailableSeats;
    char** airCraft;
 };
 
 #endif