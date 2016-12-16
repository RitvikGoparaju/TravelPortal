#ifndef Airline5047_1_H 
#define Airline5047_1_H
#include <vector>
#include <string>
#include "Portal5047.h"
#include "Airline.h"
using namespace std;

class Flight5047;
class Portal;

class Airline5047_1: public Airline {
public:
	Airline5047_1(Portal *pl): Airline(pl) {this->getPortal()->addAirline(this); airlineName = "5047-A";}
	virtual void init(string ifile);
	void setName(string airlineName_) {airlineName = airlineName_;}
	virtual string getName() {return airlineName;}
	virtual void findFlights(string origin_, string destination_, vector<Flight *>& flights_);
	virtual float getPrice(Flight *flight);
	virtual bool issueTicket(Flight *flight);
	virtual int getNumSold();
	virtual void getSalesStats(float& revenue, float& passKm);
private:
	//my members
	string airlineName;
	vector <Flight*> flight5047s;
};
#endif