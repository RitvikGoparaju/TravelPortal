#ifndef Portal_H 
#define Portal_H
#include <string>
#include <vector>

using namespace std;

class Airline;

class Portal {
public:
	Portal() {}
	virtual ~Portal() {}

	enum SortField {Airlines, Time, Duration, Price};
	enum SortOrder {Ascending, Descending};
	enum BuyOption {Cheapest, Fastest, Earliest, Latest};

	// initialize route information by reading in input file with government data/guidelines
	virtual void initRoutes(string routeInfo) {}

	// add an airline to the list of airlines that are part of this portal
	// This is to be called by the constructor of the relevant Airline class,
	// and the derived class of Portal should decide how to use this
	virtual void addAirline(Airline *airline) {}

	// return constraints/guidelines for a given origin+destination combination
	// Please note: the first two arguments are input to the function, which then returns the
	// required information by modifying the remaining arguments
	virtual void routeInfo(string origin, string destination, float& dist, float& duration,
						   float& minPrice, float& maxPrice, float& timeVariation) {}

	// Process user input by reading in the input file
	// Take appropriate actions based on contents of each line of the input
	// At the end, should print out the number of tickets, revenue and passenger-km sold by each airline
	virtual void processUserInput(string inputFileName) {}

protected:
	// The methods below are intended to be called only by processUserInput
	// Need to be implemented by the derived classes of Portal

	// display (to cout) the list of flights with available seats between origin and destination
	// List is to be shown in sorted order, based on sortField and sortOrder
	// sortField is one of the values of enum SortField
	// sortOrder is one of values of enum SortOrder
	virtual void showFlights(string origin, string destination, SortField sortField = Airlines,
					 SortOrder sortOrder = Descending) {}

	// purchase a ticket based on BuyOption criteria, optionally specifying a preferred airline
	// This will be for the last selected origin+destination combination
	virtual bool buyTicket(BuyOption cirteria, string airline = "") = 0;

};
#endif

