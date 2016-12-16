#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Route.h"
#include "Portal5047.h"
#include "PortalFlightToSort.h"
#include "Airline.h"
#include "Flight.h"

class PortalFlightToSort;
class Airline;
class Flight;
class Route;

using namespace std;

// initializing route information by reading in input file with government data/guidelines
void Portal5047::initRoutes(string routeInfo) {

	fstream inp(routeInfo.c_str(),fstream::in);
	while (!inp.eof()) {
		string origin, destination;
		float distance, duration, minRatePerKM, maxRatePerKM, durationTolerance;
		inp >> origin >> destination >> distance >> duration >> minRatePerKM >> maxRatePerKM >> durationTolerance;
		if( inp.eof() ) break;
		Route *route = new Route(origin, destination, distance, duration, minRatePerKM, maxRatePerKM, durationTolerance);
		routes.push_back(route);
	}
}

// Getting route info based on origin and destination

void Portal5047::routeInfo(string origin, string destination, float& dist, float& duration, float& minPrice, float& maxPrice, float& timeVariation) {
	float distance_;
	for (int i=0; i<routes.size(); i++) {
		if (!(origin.string::compare(routes[i]->Route::getOrigin())) && !(destination.string::compare(routes[i]->Route::getDestination()))) {
			*(&dist) = routes[i]->Route::getDistance();
			*(&duration) = routes[i]->Route::getDuration();
			*(&minPrice) = routes[i]->Route::getMinRatePerKM();
			*(&maxPrice) = routes[i]->Route::getMaxRatePerKM();
			*(&timeVariation) = routes[i]->Route::getDurationTolerance();
		}
	}
}

// processing user input (Sorting and Buying)

void Portal5047::processUserInput(string inputFileName) {

	fstream inp(inputFileName.c_str(),fstream::in);
	inp >> originToBuy >> destinationToBuy;
	showFlights(originToBuy, destinationToBuy, Airlines, Ascending);
	while (!inp.eof()) {
		string option, sortField, sortOrder, buyOption, airlineName;
		inp >> option;
		if( inp.eof() ) break;

		// For sorting

		if (option == "sort") {
			inp >> sortField;
			inp >> sortOrder;
			if (sortField == "price") {
				if (sortOrder == "ascending") {
					showFlights(originToBuy, destinationToBuy, Price, Ascending);
				} else {
					showFlights(originToBuy, destinationToBuy, Price, Descending);
				}
			}
			else if (sortField == "time") {
				if (sortOrder == "ascending") {
					showFlights(originToBuy, destinationToBuy, Time, Ascending);
				} else {
					showFlights(originToBuy, destinationToBuy, Time, Descending);
				}
			}
			else if (sortField == "duration") {
				if (sortOrder == "ascending") {
					showFlights(originToBuy, destinationToBuy, Duration, Ascending);
				} else {
					showFlights(originToBuy, destinationToBuy, Duration, Descending);
				}
			}
			else if (sortField == "airline") {
				if (sortOrder == "ascending") {
					showFlights(originToBuy, destinationToBuy, Airlines, Ascending);
				} else {
					showFlights(originToBuy, destinationToBuy, Airlines, Descending);
				}
			}
		}

		// For Buying

		else if (option == "buy") {
			inp >> buyOption;
			inp >> airlineName;
			cout << "To Buy:" << endl;
			cout << "Option - "+buyOption << " ";
			if (airlineName.empty()) {
				if (buyOption == "cheapest") {
					buyTicket(Cheapest);
				} else if (buyOption == "fastest") {
					buyTicket(Fastest);
				} else if (buyOption == "earliest") {
					buyTicket(Earliest);
				} else if (buyOption == "latest") {
					buyTicket(Latest);
				}
			} else {
				cout << ", Airline - " << airlineName << " ";
				if (buyOption == "cheapest") {
					buyTicket(Cheapest, airlineName);
				} else if (buyOption == "fastest") {
					buyTicket(Fastest, airlineName);
				} else if (buyOption == "earliest") {
					buyTicket(Earliest, airlineName);
				} else if (buyOption == "latest") {
					buyTicket(Latest, airlineName);
				}
			}
			break;
		}
	}
}

// Showing flights based on given criteria using functors

void Portal5047::showFlights(string origin, string destination, SortField sortField, SortOrder sortOrder) {

	flightsToSort = getAllFlightsToShow(origin, destination);

	cout << "From '" << origin << "' to '" << destination << "'" << endl; 	

	if (sortField == Duration) {
		cout << "Duration -- ";
		if (sortOrder == Ascending) {
			cout << "Ascending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), duration_sort_asc());
		}
		else {
			cout << "Descending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), duration_sort_desc());
		}
	} 
	else if (sortField == Time) {
		cout << "Time -- ";
		if (sortOrder == Ascending) {
			cout << "Ascending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), departure_sort_asc());
		}
		else {
			cout << "Descending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), departure_sort_desc());
		}
	} else if (sortField == Price) {
		cout << "Price -- ";
		if (sortOrder == Ascending) {
			cout << "Ascending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), price_sort_asc());
		}
		else {
			cout << "Descending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), price_sort_desc());
		}
	} else if (sortField == Airlines) {
		cout << "Airline -- ";
		if (sortOrder == Ascending) {
			cout << "Ascending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), name_sort_asc());
		}
		else {
			cout << "Descending" << endl;
			std::sort(flightsToSort.begin(), flightsToSort.end(), name_sort_desc());
		}
	}

	cout << "Airline Name-Flight No.-Duration-Time-Price-Distance-No.Available" << endl;

	for (int i=0; i<flightsToSort.size(); i++) {
		cout << flightsToSort[i].getAirlineName() << "-";
		cout << flightsToSort[i].getFlight()->getName()<< "-";
		cout << flightsToSort[i].getDuration() << "-";
		cout << flightsToSort[i].getDeparture() << "-";
		cout << flightsToSort[i].getPrice() << "-";
		cout << flightsToSort[i].getFlight()->getDistance() << "-";
		cout << flightsToSort[i].getFlight()->numAvailableSeats() << endl;
	}

}

// Getting flights for buying based on given criteria using functors (Same as previous but without display statements

void Portal5047::getAllFlightsForBuying(string origin, string destination, SortField sortField, SortOrder sortOrder) {

	flightsToSort = getAllFlightsToShow(origin, destination);

	cout << "From '" << origin << "' to '" << destination << "'" << endl; 	

	if (sortField == Duration) {
		if (sortOrder == Ascending) {
			std::sort(flightsToSort.begin(), flightsToSort.end(), duration_sort_asc());
		}
		else {
			std::sort(flightsToSort.begin(), flightsToSort.end(), duration_sort_desc());
		}
	} 
	else if (sortField == Time) {
		if (sortOrder == Ascending) {
			std::sort(flightsToSort.begin(), flightsToSort.end(), departure_sort_asc());
		}
		else {
			std::sort(flightsToSort.begin(), flightsToSort.end(), departure_sort_desc());
		}
	} else if (sortField == Price) {
		if (sortOrder == Ascending) {
			std::sort(flightsToSort.begin(), flightsToSort.end(), price_sort_asc());
		}
		else {
			std::sort(flightsToSort.begin(), flightsToSort.end(), price_sort_desc());
		}
	} else if (sortField == Airlines) {
		if (sortOrder == Ascending) {
			std::sort(flightsToSort.begin(), flightsToSort.end(), name_sort_asc());
		}
		else {
			std::sort(flightsToSort.begin(), flightsToSort.end(), name_sort_desc());
		}
	}
}

//Buying ticket based on criteria specified

bool Portal5047::buyTicket(BuyOption criteria) {

	Flight* flight;
	bool issued = false;
	sortFlightsForBuying(criteria);
	if (flightsToSort.vector::size() > 0) {
		flight = flightsToSort[0].getFlight();
		issued = flight->getAirline().issueTicket(flight);
		return issued;
	} else {
		cout << "Ticket could not be issued" << endl;
		return issued;
	}

}

//Buying ticket based on criteria as well as airline specified (Function overloading)

bool Portal5047::buyTicket(BuyOption criteria, string airline) {
	Flight* flight;
	bool issued = false;
	sortFlightsForBuying(criteria);
	for (int i=0; i < flightsToSort.size(); i++) {
		flight = flightsToSort[i].getFlight();
		if ( flight->getAirline().getName() == airline) {
			issued = flight->getAirline().issueTicket(flight);
			return issued;
		}
	}
	cout << "Ticket could not be issued" << endl;
	return issued;
}

// Getting a vector of custom made class PortalFlightToSort from the 
// flights of all airlines attached to the portal for the specified origin and destination.

vector<PortalFlightToSort> Portal5047::getAllFlightsToShow(string origin, string destination) {

	vector<PortalFlightToSort> flightsToSortReturn;

	for (int i=0; i < airlines.size(); i++) {
		vector<Flight*> flightPtrsToSort;
		airlines[i]->findFlights(origin, destination, flightPtrsToSort);
		for (int j=0; j < flightPtrsToSort.size(); j++) {
			if (flightPtrsToSort[j]->numAvailableSeats() > 0) {
				string nameFlight = airlines[i]->getName();
				string departureFlight = flightPtrsToSort[j]->getDeparture();
				float durationFlight = flightPtrsToSort[j]->getDuration();
				float priceFlight = airlines[i]->getPrice(flightPtrsToSort[j]);
				PortalFlightToSort portalFlightToSort(flightPtrsToSort[j], nameFlight, departureFlight, durationFlight, priceFlight);
				flightsToSortReturn.push_back(portalFlightToSort);
			}
		}
	}
	return flightsToSortReturn;
}

//Sorting flights based on the specified criteria for buying

void Portal5047::sortFlightsForBuying(BuyOption criteria) {

	if (criteria == Cheapest) {
		getAllFlightsForBuying(originToBuy, destinationToBuy, Price, Ascending);
	} else if (criteria == Fastest) {
		getAllFlightsForBuying(originToBuy, destinationToBuy, Duration, Ascending);
	} else if (criteria == Earliest) {
		getAllFlightsForBuying(originToBuy, destinationToBuy, Time, Ascending);
	} else if (criteria == Latest) {
		getAllFlightsForBuying(originToBuy, destinationToBuy, Time, Descending);
	}

}