#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Airline5047_2.h"
#include "Flight5047.h"
//#include "Flight.h"
using namespace std;

//class Flight;
//class Flight5047;
//class Portal;

void Airline5047_2::init(string ifile) {

	int flightsAlreadyInitialized = flight5047s.size();

	string name_, origin_, destination_, departure_;
	int totNumSeatsAvailable, noFlightsInRoute, noSeatsPerFlight, noSeatsLastFlight, latestFlightNo = 0, noFlightsTotal = 0, lastFlightCntr = 0, flightCntr = 0;
	int numSeatsAvailable_;
	float minRate_, maxRate_, distance_, duration_, price_, timeVariation_;

	fstream inp(ifile.c_str(), fstream::in);
	inp >> totNumSeatsAvailable;
	while (!(inp.eof())) {
		inp >> origin_ >> destination_>> noFlightsInRoute;
		//if( inp.eof() ) break;
		noFlightsTotal = noFlightsTotal + noFlightsInRoute;
	}
	lastFlightCntr = noFlightsTotal - 1;
	noSeatsPerFlight = totNumSeatsAvailable / noFlightsTotal;
	noSeatsLastFlight = totNumSeatsAvailable - (noSeatsPerFlight * (noFlightsTotal-1));

	fstream inp1(ifile.c_str(), fstream::in);
	inp1 >> totNumSeatsAvailable;
	while (!inp1.eof()) {
		inp1 >> origin_ >> destination_>> noFlightsInRoute;
		//if( inp1.eof() ) break;
		for (int i=0; i<noFlightsInRoute; i++) {
			int hhmax = 24, hhmin=0, randhh, mmmax = 59, mmmin=0, randmm;
			string hhstring, mmstring, timeDeparture;

			srand (time(NULL)+i);
			randhh = (rand()%(hhmax-hhmin))+hhmin;
			randmm = (rand()%(mmmax-mmmin))+mmmin;

			std::ostringstream oshh, osmm, osno;

			oshh << static_cast<long long>(randhh);
			hhstring = oshh.str();			

			hhstring.insert(hhstring.begin(), 2 - hhstring.size(), '0');

			osmm << static_cast<long long>(randmm);
			mmstring = osmm.str();

			mmstring.insert(mmstring.begin(), 2 - mmstring.size(), '0');
			departure_ = hhstring+":"+mmstring;

			this->Airline::getPortal()->routeInfo(origin_, destination_, distance_, duration_, minRate_, maxRate_, timeVariation_);

			int minRate = minRate_*distance_;
			int maxRate = maxRate_*distance_;
			int randomRate;

			minRate *=100;
			maxRate *=100;

			srand (time(NULL)+(i*10+4));
			randomRate = (rand()%(maxRate-minRate))+minRate;

			price_ = randomRate/100;

			int minDuration = duration_ - timeVariation_;
			int maxDuration = duration_ + timeVariation_;
			int randomDuration;

			minDuration *=100;
			maxDuration *=100;

			srand (time(NULL)+(i*200+24));
			randomDuration = (rand()%(maxDuration-minDuration))+minDuration;

			duration_ = randomDuration/100;

			if (lastFlightCntr == flightCntr) {
				numSeatsAvailable_ = noSeatsLastFlight;
			} else {
				numSeatsAvailable_ = noSeatsPerFlight;
			}

			osno << static_cast<long long>(flightsAlreadyInitialized+flightCntr+1);
			string flightNo = osno.str();
			flightNo.insert(flightNo.begin(), 2 - flightNo.size(), '0');

			name_ = airlineName+flightNo;
			Flight5047* flight5047 = new Flight5047(name_, origin_, destination_, departure_, distance_, duration_, price_, numSeatsAvailable_, this);
			flight5047s.push_back(flight5047);
			flightCntr++;
		}
	}

	int numSeatsDebug = 0;
	for (int i=0; i<flight5047s.size(); i++) {
		 numSeatsDebug += flight5047s[i]->numAvailableSeats();
	}
	cout << "no. Flights - " << flight5047s.size() << endl;
	cout << "no. Seats - " << numSeatsDebug << endl;
}

void Airline5047_2::findFlights(string origin_, string destination_, vector<Flight *>& flights_) {
	
	for (int i = 0; i < flight5047s.size(); i++) {
		if ((origin_ == flight5047s[i]->getOrigin()) && (destination_ == flight5047s[i]->getDestination())) {			
			flights_.push_back(dynamic_cast<Flight*>(flight5047s[i]));
		}
	}

}

float Airline5047_2::getPrice(Flight *flight) {

	Flight5047* flight5047 = dynamic_cast<Flight5047*>(flight);
	float price = flight5047->getPrice();
	return price;

}

bool Airline5047_2::issueTicket(Flight *flight) {

	Flight5047* flight5047 = dynamic_cast<Flight5047*>(flight);

	if (flight5047->numAvailableSeats() > 0) {
		cout << "1 Ticket issued for " + flight5047->getName() << endl;
		int numSold_ = flight5047->getNumSold();
		numSold_++;
		flight5047->incrementNumSold();
		flight5047->decrementNumAvailableSeats();
		flight5047->incrementPassKM();
		flight5047->incrmentRevenue();
		return true;
	}

	cout << "Ticket could not be issued as there is no vacancy" << endl;
	return false;
}

int Airline5047_2::getNumSold() {

	int totalNumSold = 0;
	for (int i=0; i < flight5047s.size(); i++) {
		totalNumSold = totalNumSold + flight5047s[i]->getNumSold();
	}
	return totalNumSold;
}

void Airline5047_2::getSalesStats(float& revenue, float& passKm) {

	float tempRevenue = 0.0;
	float tempPassKM = 0.0;

	for (int i=0; i < flight5047s.size(); i++) {
		tempRevenue = tempRevenue + flight5047s[i]->getRevenue();
		tempPassKM = tempPassKM + flight5047s[i]->getPassKm();		
	}

	*(&revenue) = tempRevenue;
	*(&passKm) = tempPassKM;
}