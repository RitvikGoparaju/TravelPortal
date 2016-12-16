#include <string>
using namespace std;

class BusService;

class Bus {
public:
	Bus() {}
	virtual ~Bus() {}

	virtual string getName() = 0; // should have the bus service name and 2 more letters or digits identfying the bus

	virtual string getOrigin() = 0;
	virtual string getDestination() = 0;
	virtual string getDeparture() = 0;       // in hhmm (24 hour) format
	virtual float getDuration() = 0;
	virtual int numAvailableSeats() = 0;

	virtual float getDistance() = 0; // distance of flight for this route

	virtual BusService& getBusService() = 0;

};

