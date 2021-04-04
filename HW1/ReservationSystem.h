#ifndef __RESERVATIONSYSTEM_H
#define __RESERVATIONSYSTEM_H

using namespace std;
#include <string>
#include <iostream>
#include "Flight.h"
#include "Reservation.h"

class ReservationSystem {
public:
    ReservationSystem();
    ~ReservationSystem();
    void addFlight( const int flightNo, const int rowNo, const int seatNo );
    void cancelFlight( const int flightNo );
    void showAllFlights();
    void showFlight( const int flightNo );
    int makeReservation( const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol );
    void cancelReservation( const int resCode );
    void showReservation( const int resCode );
private:
    Flight* flights;
    Reservation* reservations;
    int numOfFlights;
    int numOfReservations;
};

#endif