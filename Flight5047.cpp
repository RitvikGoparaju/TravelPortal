#include <string>
#include <iostream>
#include "Flight5047.h"
//#include "Airline.h"
using namespace std;

// Custom Flight Constructor
Flight5047::Flight5047(std::string  name_, std::string origin_, std::string destination_, std::string departure_, float distance_, float duration_, float price_, int numSeats_, Airline* airline_) {
	name = name_;
	origin = origin_;
	destination = destination_;
	departure = departure_;
	duration = duration_;
	price = price_;
	numSeats = numSeats_;
	numSold = 0;
	passKm = 0.0;
	revenue = 0.0;
	distance = distance_;
	airline = airline_;
}