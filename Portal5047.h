#ifndef RealPortal5047_H 
#define RealPortal5047_H
#include <string>
#include <vector>
#include <algorithm>
#include "Portal.h"
#include "PortalFlightToSort.h"
using namespace std;

class Airline;
class PortalFlightToSort;
class Route;

class Portal5047: public Portal {
public:
	Portal5047(): Portal() {}
	~Portal5047() {};
	virtual void initRoutes(string routeInfo);
	virtual void routeInfo(string origin, string destination, float& dist, float& duration,
	float& minPrice, float& maxPrice, float& timeVariation);
	virtual void addAirline(Airline *airline) {airlines.push_back(airline);}
	virtual void processUserInput(string inputFileName);
protected:
	virtual void showFlights(string origin, string destination, SortField sortField, SortOrder sortOrder);
	virtual bool buyTicket(BuyOption cirteria);
	virtual bool buyTicket(BuyOption criteria, string airline);

	//my additions

	vector<PortalFlightToSort> getAllFlightsToShow(string origin, string destination);
	void getAllFlightsForBuying(string origin, string destination, SortField sortField, SortOrder sortOrder);
	void sortFlightsForBuying(BuyOption buyOption);
	
	//Functors for sorting

	struct duration_sort_asc
	{
		inline bool operator() (const PortalFlightToSort& durationFirst, const PortalFlightToSort& durationNext)
		{
			return (durationFirst.getDuration() < durationNext.getDuration());
		}
	};

	struct duration_sort_desc
	{
		inline bool operator() (const PortalFlightToSort& durationFirst, const PortalFlightToSort& durationNext)
		{
			return (durationFirst.getDuration() > durationNext.getDuration());
		}
	};

	struct departure_sort_asc
	{
		inline bool operator() (const PortalFlightToSort& departureFirst, const PortalFlightToSort& departureNext)
		{
			return (departureFirst.getDeparture() < departureNext.getDeparture());
		}
	};

	struct departure_sort_desc
	{
		inline bool operator() (const PortalFlightToSort& departureFirst, const PortalFlightToSort& departureNext)
		{
			return (departureFirst.getDeparture() > departureNext.getDeparture());
		}
	};

	struct price_sort_asc
	{
		inline bool operator() (const PortalFlightToSort& priceFirst, const PortalFlightToSort& priceNext)
		{
			return (priceFirst.getPrice() < priceNext.getPrice());
		}
	};

	struct price_sort_desc
	{
		inline bool operator() (const PortalFlightToSort& priceFirst, const PortalFlightToSort& priceNext)
		{
			return (priceFirst.getPrice() > priceNext.getPrice());
		}
	};

	struct name_sort_asc
	{
		inline bool operator() (const PortalFlightToSort& nameFirst, const PortalFlightToSort& nameNext)
		{
			return (nameFirst.getAirlineName() < nameNext.getAirlineName());
		}
	};

	struct name_sort_desc
	{
		inline bool operator() (const PortalFlightToSort& nameFirst, const PortalFlightToSort& nameNext)
		{
			return (nameFirst.getAirlineName() > nameNext.getAirlineName());
		}
	};
private:
	vector <Route*> routes;

	//my additions

	vector <Airline*> airlines;
	string originToBuy;
	string destinationToBuy;
	vector<PortalFlightToSort> flightsToSort;
};
#endif