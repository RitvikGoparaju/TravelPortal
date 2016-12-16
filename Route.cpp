#include "Route.h"
#include <string>
#include <vector>
using namespace std;

Route::Route(string origin_, string destination_, float distance_, float duration_, float minRatePerKM_, float maxRatePerKM_, float durationTolerance_) {
	origin = origin_;
	destination = destination_;
	distance = distance_;
	duration = duration_;
	minRatePerKM = minRatePerKM_;
	maxRatePerKM = maxRatePerKM_;
	durationTolerance = durationTolerance_;
}

Route::~Route() {
}

string Route::getOrigin() {
	return origin;
}

string Route::getDestination() {
	return destination;
}
float Route::getDistance(){
	return distance;
}
float Route::getDuration(){
	return duration;
}
float Route::getMinRatePerKM(){
	return minRatePerKM;
}
float Route::getMaxRatePerKM(){
	return maxRatePerKM;
}
float Route::getDurationTolerance(){
	return durationTolerance;
}