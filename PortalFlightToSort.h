#ifndef PortalFlightToSort_H 
#define PortalFlightToSort_H
#include <string>
using namespace std;

class Flight;

//This class is exclusively used by my portal for collecting the flight information for enabling sorting
class PortalFlightToSort {

public:
	PortalFlightToSort(Flight *flight_, string airlineName_, string departure_, float duration_, float price_);
	~PortalFlightToSort() {}
	Flight* getFlight() {return flight;}
	string getAirlineName() const {return airlineName;}
	string getDeparture() const {return departure;}
	float getDuration() const {return duration;}
	float getPrice() const {return price;}
private:
	Flight* flight;
	string airlineName;
	string departure;
	float duration;
	float price;
};
#endif