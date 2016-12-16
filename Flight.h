#ifndef Flight_H 
#define Flight_H
#include <string>
using namespace std;

class Airline;

class Flight {
public:
	Flight() {}
	virtual ~Flight() {}

	virtual string getName() = 0; // should have the airline name and 2 more letters or digits identfying the flight

	virtual string getOrigin() = 0;
	virtual string getDestination() = 0;
	virtual string getDeparture() = 0;       // in hhmm (24 hour) format
	virtual float getDuration() = 0;
	virtual int numAvailableSeats() = 0;

	virtual float getDistance() = 0; // distance of flight for this route

	virtual Airline& getAirline() = 0;

};
#endif