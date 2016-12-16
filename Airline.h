
#ifndef AIRLINE_H
#define AIRLINE_H

#include <vector>
#include <string>
using namespace std;

class Flight;
class Portal;

class Airline {
public:
	Airline(Portal *pl):portal(pl) {}
	virtual ~Airline() {}

	// reads in the input file for the airline and initializes its
	// information about routes, capacity etc
	virtual void init(string ifile) = 0;

	virtual string getName() = 0; // the name of the airline. Should have the last 4 digits of the roll no.

	// return the list of flights for this airline between origin and destination cities
	// The list of flights is appended to the vector flights that is passed in.
	// Input vector flights will not be a null reference
	virtual void findFlights(string origin, string destination,
				             vector<Flight *>& flights) {}

	// get the current price for a specified flight of this airline
	virtual float getPrice(Flight *flight) = 0;

	// buy a ticket from this airline for a particular flight
	// Returns true if the ticket can be issues (i.e. there are seats available on the flight
	virtual bool issueTicket(Flight *flight) = 0;

	// number of tickets sold today
	virtual int getNumSold() = 0;

	// get total revenue and passenger km for the day
	virtual void getSalesStats(float& revenue, float& passKm) {}

protected:
	Portal *getPortal() {return portal;}

private:
	Portal *portal;
};

#endif
