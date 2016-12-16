#ifndef Airline5047_2_H 
#define Airline5047_2_H
#include <vector>
#include <string>
#include "Airline.h"
#include "Portal5047.h"
using namespace std;

class Flight5047;
class Portal;

class Airline5047_2: public Airline {
public:
	Airline5047_2(Portal *pl): Airline(pl) {this->getPortal()->addAirline(this); airlineName = "5047-B";}
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
	vector <Flight5047*> flight5047s;
};
#endif