#include <vector>
#include <string>
using namespace std;

class Bus;
class Portal;

class BusService{
public:
	BusService(Portal *pl):portal(pl) {}
	virtual ~BusService() {}

	// reads in the input file for the Bus Service and initializes its
	// information about routes, capacity etc
	virtual void init(string ifile) = 0;

	virtual string getName() = 0; // the name of the Bus Service. Should have the last 4 digits of the roll no.

	// return the list of buses for this service between origin and destination cities
	// The list of buses is appended to the vector buses that is passed in.
	// Input vector buses will not be a null reference
	virtual void findBuses(string origin, string destination,
				             vector<Bus *>& buses) {}

	// get the current price for a specified bus of this service
	virtual float getPrice(Bus *bus) = 0;

	// buy a ticket from this Service for a particular bus
	// Returns true if the ticket can be issued (i.e. there are seats available on the bus
	virtual bool issueTicketBus *bus) = 0;

	// number of tickets sold today
	virtual int getNumSold() = 0;

	// get total revenue and passenger km for the day
	virtual void getSalesStats(float& revenue, float& passKm) {}

protected:
	Portal *getPortal() {return portal;}

private:
	Portal *portal;
};

