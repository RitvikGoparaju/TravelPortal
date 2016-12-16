#ifndef Flight5047_H 
#define Flight5047_H
#include <string>
#include "Flight.h"
using namespace std;

class Airline;

class Flight5047: public Flight {
public:
	Flight5047() {}
	Flight5047(std::string  name_, std::string origin_, std::string destination_, std::string departure_, float distance_, float duration_, float price_, int numSeats_, Airline* airline);
	virtual ~Flight5047() {}

	virtual string getName() {return name;}
	virtual string getOrigin() {return origin;}
	virtual string getDestination() {return destination;}
	virtual string getDeparture()  {return departure;}
	virtual float getDuration()  {return duration;}
	virtual int numAvailableSeats() {return numSeats;}
	virtual float getDistance() {return distance;}
	virtual Airline& getAirline() {return *airline;};

	//my methods
	float getPrice() {return price;}
	void setNumSold(int numSold_) {numSold = numSold_;}	
	void decrementNumAvailableSeats() {numSeats--;}
	void incrementNumSold() {numSold++;}
	void incrementPassKM() {passKm = passKm + distance;}
	void incrmentRevenue() {revenue = revenue + price;}	
	int getNumSold() {return numSold;}
	int getPassKm () {return passKm;}
	float getRevenue() {return revenue;}
	string getNameConst() const {return name;}
private:
	std::string name;
	std::string origin;
	std::string destination;	
	std::string departure;
	float distance;
	float duration;
	float price;
	int numSeats;
	int numSold;
	Airline* airline;
	float passKm;
	float revenue;
};
#endif