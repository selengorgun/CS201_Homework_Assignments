#include "ReservationSystem.h"
#include "Flight.h"
#include "Reservation.h"
#include <iostream>
#include <string>

using namespace std;

ReservationSystem::ReservationSystem(){
    flights = NULL;
    reservations = NULL;
    numOfFlights = 0;
    numOfReservations = 0;
}
ReservationSystem::~ReservationSystem(){
    if(flights != NULL){
        delete[] flights;
    }
    flights = NULL;
    if(reservations != NULL){
        delete[] reservations;
    }
    reservations = NULL;
}
void ReservationSystem::addFlight( const int flightNo, const int rowNo, const int seatNo ){
    bool flightExists = false;
    bool properRowSeat = false;
    for(int a = 0; a < numOfFlights; a++){
        if(flights[a].getFlightNum() == flightNo){
            flightExists = true;
        }
    }
    if(rowNo > 0 && seatNo > 0){
        properRowSeat = true;
    }
    if(!flightExists && properRowSeat){
        if(numOfFlights == 0){
            cout<< "rs1" << endl;
            Flight f(flightNo, rowNo, seatNo);
            cout<< "rs2" << endl;
            numOfFlights++;
            flights = new Flight[numOfFlights];
            cout<< "rs8" << endl;
            flights[numOfFlights - 1] = f;
            cout<< "rs9" << endl;
        }
        else{
            cout<< "rs3" << endl;
            Flight f(flightNo, rowNo, seatNo);
            cout<< "rs4" << endl;
            Flight* copyFlights = new Flight[numOfFlights];
            for(int i = 0; i < numOfFlights; i++){
                copyFlights[i] = flights[i];
            }
            numOfFlights++;
            cout<< "rs5" << endl;
            delete[] flights;
            cout<< "rs6" << endl;
            flights = new Flight[numOfFlights];
            for(int a = 0; a < numOfFlights - 1; a++){
                flights[a] = copyFlights[a];
            }
            flights[numOfFlights - 1] = f;
            delete[] copyFlights;
        }
        cout<< "rs7" << endl;
        cout << "Flight " << flightNo << " has been added." << endl;
    }
    else{
        cout << "Flight " << flightNo << " already exists." << endl;
    }
}

void ReservationSystem::showAllFlights(){
    if(numOfFlights != 0){
        cout << "Flights currently operated:" << endl;
        for(int a = 0; a < numOfFlights; a++){
            cout << "Flight " << flights[a].getFlightNum() << " ( " << flights[a].getNumOfAvailableSeats() << " available seats)" << endl;
        }
    }
    else{
        cout << "No flights exist." << endl;
    }
}
void ReservationSystem::showFlight(const int flightNo){
    bool flightExists = false;
    int index = 0;
    for(int a = 0; a < numOfFlights; a++){
        if(flights[a].getFlightNum() == flightNo){
            flightExists = true;
            index = a;
            break;
        }
    }
    
    if(!flightExists){
        cout << "Flight does not exist." << endl;
    }
    else{
        int column = flights[index].getColumnNum();
        cout << "Flight " << flightNo << " has " << flights[index].getNumOfAvailableSeats() << " available seats." << endl;
        cout << "  ";
        for(char a = 'A'; a <= 'Z' && column > 0; a++ ){
            cout << a << " ";
            column--;
        }
        cout << endl;
        for(int a = 0; a < flights[index].getRowNum(); a++){
            cout << (a+1) << " ";
            for(int i = 0; i < flights[index].getColumnNum(); i++){
                cout << flights[index].getAirCraft()[i][a] << " ";
            }
            cout << endl;
        }
    }
}
int ReservationSystem::makeReservation(const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol ){
    bool flightExists = false;
    int reserveCode = -1;
    int indexOfFlight = 0;
    int index = 0;
    string* nonAvailables;
    int numOfNonAvailables = 0;
    
    for(int a = 0; a < numOfFlights; a++){
        if(flights[a].getFlightNum() == flightNo){
            flightExists = true;
            indexOfFlight = a;
            break;
        }
    }
    
    for(int a = 0; a < numPassengers; a++){
        if(!flights[indexOfFlight].isAvailable((int)(seatCol[a]) - 64, seatRow[a])){
            numOfNonAvailables++;
        }
    }
    
    if(flightExists){
        if(numOfNonAvailables == 0){
            Reservation r(flightNo, numPassengers, seatRow, seatCol);
            if(numOfReservations == 0){
                reservations = new Reservation[1];
                numOfReservations++;
                reservations[0] = r;
            }
            else{
                Reservation* temp = new Reservation[numOfReservations];
                for(int a = 0; a < numOfReservations; a++){
                    temp[a] = reservations[a];
                }
                numOfReservations++;
                delete[] reservations;
                reservations = new Reservation[numOfReservations];
                for(int i = 0; i < numOfReservations; i++){
                    reservations[i] = temp[i];
                }
                reservations[numOfReservations - 1] = r;
                delete[] temp;
            }
            for(int a = 0; a < numPassengers; a++){
                if(flights[indexOfFlight].isAvailable((int)(seatCol[a]) - 64, seatRow[a])){
                    flights[indexOfFlight].getAirCraft()[(int)(seatCol[a]) - 65][seatRow[a] - 1] = 'x';
                    flights[indexOfFlight].setNumOfAvailableSeats(flights[indexOfFlight].getNumOfAvailableSeats() - 1);
                }
            }
            reserveCode = reservations[numOfReservations - 1].getResCode();
        }
        else{
            nonAvailables = new string[numOfNonAvailables];
            for(int i = 0; i < numPassengers; i++){
                if(!flights[indexOfFlight].isAvailable((int)(seatCol[i]) - 64, seatRow[i])){
                    nonAvailables[index] = seatCol[i] + seatRow[i];
                    index++;
                }
            }
            for(int i = 0; i < numOfNonAvailables; i++){
                cout << nonAvailables[i] << " is not available." << endl;
            }
        }
    }
    else{
        cout << "Flight " << flightNo << " does not exist." << endl; 
    }
    return reserveCode;
}
void ReservationSystem::showReservation(const int resCode){
    bool exists = false;
    int index = 0;
    for(int a = 0; a < numOfReservations; a++){
        if(reservations[a].getResCode() == resCode){
            exists = true;
            index = a;
            break;
        }
    }
    if(exists){
        cout << "Reservations under Code " << resCode << " in Flight " << reservations[index].getFlightNum() << ": ";
        for(int i = 0; i < reservations[index].getNumPassengers(); i++){
            cout << reservations[index].getRows()[i] << reservations[index].getColumns()[i] << " ";
        }
    }
    else{
        cout << "No reservations under Code " << resCode << endl;
    }
}
void ReservationSystem::cancelReservation(const int resCode){
    bool exists = false;
    int indexOfRes = 0;
    int indexOfFlight = 0;
    for(int a = 0; a < numOfReservations; a++){
        if(reservations[a].getResCode() == resCode){
            exists = true;
            indexOfRes = a;
            break;
        }
    }
    if(exists){
        cout << "Reservations for the seats ";
        for(int i = 0; i < reservations[indexOfRes].getNumPassengers(); i++){
            cout << reservations[indexOfRes].getRows()[i] << reservations[indexOfRes].getColumns()[i] << " ";
        }
        cout << "are cancelled in Flight " << reservations[indexOfRes].getFlightNum() << endl;
        
        for(int i = 0; i < reservations[indexOfRes].getNumPassengers(); i++){
            flights[indexOfFlight].getAirCraft()[(int)(reservations[indexOfRes].getColumns()[i]) - 65][reservations[indexOfRes].getRows()[i] - 1] = 'o';
            flights[indexOfFlight].setNumOfAvailableSeats(flights[indexOfFlight].getNumOfAvailableSeats() + 1);
        }
        
        if(numOfReservations == 1){
            delete[] reservations;
            reservations = NULL;
            numOfReservations--;
        }
        else{
            Reservation* temp = new Reservation[numOfReservations];
            for(int i = 0; i < numOfReservations; i++){
                temp[i]  = reservations[i];
            }
            numOfReservations--;
            delete[] reservations;
            reservations = new Reservation[numOfReservations];
            for(int a = 0; a < indexOfRes; a++){
                reservations[a] = temp[a];
            }
            for(int a = indexOfRes; a < numOfReservations; a++){
                reservations[a] = temp[a + 1];
            }
            delete[] temp;
        }
        for(int a = 0; a < numOfReservations; a++){
            if(reservations[a].getFlightNum() == reservations[indexOfRes].getFlightNum()){
                indexOfFlight = a;
            }
        }
        
    }
    else{
        cout << "No reservations are found under code " << resCode << endl;
    }
}
void ReservationSystem::cancelFlight(const int flightNo){
    bool exists = false;
    int index = 0;
    for(int i = 0; i < numOfFlights; i++){
        if(flights[i].getFlightNum() == flightNo){
            exists = true;
            index = i;
        }
    }
    if(exists){
        if(numOfFlights == 1){
            delete[] flights;
            flights = NULL;
            numOfFlights--;
        }
        else{
            for(int i = 0; i < numOfReservations; i++){
                if(reservations[i].getFlightNum() == flightNo){
                    cancelReservation(reservations[i].getResCode());
                    i--;
                }
            }
            Flight* temp = new Flight[numOfFlights];
            for(int a = 0; a < numOfFlights; a++){
                temp[a] = flights[a];
            }
            numOfFlights--;
            delete[] flights;
            flights = new Flight[numOfFlights];
            for(int a = 0; a < index; a++){
                flights[a] = temp[a];
            }
            for(int a = index; a < numOfFlights; a++){
                flights[a] = temp[a + 1];
            }
            delete[] temp;
        }
        cout << "Flight " << flightNo << " and all of its reservations are cancelled." << endl;
    }
    else{
        cout << "Flight " << flightNo << " does not exist." << endl;
    }
}