#ifndef Route_H 
#define Route_H
#include <string>
#include <vector>
using namespace std;

class Route {
public:
	Route() {}
	Route(string origin_, string destination_, float distance_, float duration_, float minRatePerKM_, float maxRatePerKM_, float durationTolerance_);
	~Route();
	string getOrigin();
	string getDestination();
	float getDistance();
	float getDuration();
	float getMinRatePerKM();
	float getMaxRatePerKM();
	float getDurationTolerance();
protected:
	string origin;
	string destination;
	float distance;
	float duration;
	float minRatePerKM;
	float maxRatePerKM;
	float durationTolerance;
};
#endif