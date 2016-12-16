#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Portal5047.h"
#include "Portal5047LR.h"
#include "Airline5047_1.h"
#include "Airline5047_2.h"
#include "Flight5047.h"
using namespace std;

int main() {

	Portal5047LR portal5047;

	//Initializing my portal with routes
	portal5047.initRoutes("routes.txt");

	//Getting airlines aligned with my portal
	Airline5047_1 airline5047_1(&portal5047);
	airline5047_1.Airline5047_1::init("airline1.txt");
	airline5047_1.Airline5047_1::init("airline2.txt");
	airline5047_1.Airline5047_1::init("airline3.txt");
	Airline5047_2 airline5047_2(&portal5047);
	airline5047_2.Airline5047_2::init("airline4.txt");
	airline5047_2.Airline5047_2::init("airline5.txt");
	airline5047_2.Airline5047_2::init("airline6.txt");	

	//Getting my portal to process user input
	portal5047.processUserInput("userInput.txt");
	/*
	portal5047.processUserInput("userInput1.txt");
	portal5047.processUserInput("userInput2.txt");
	portal5047.processUserInput("userInput3.txt");
	portal5047.processUserInput("userInput4.txt");
	portal5047.processUserInput("userInput5.txt");
	portal5047.processUserInput("userInput6.txt");
	portal5047.processUserInput("userInput7.txt");
	portal5047.processUserInput("userInput8.txt");
	portal5047.processUserInput("userInput9.txt");
	portal5047.processUserInput("userInput10.txt");
	portal5047.processUserInput("userInput11.txt");
	*/
	
	//For Statistics
	float revenue1, passkm1, revenue2, passkm2;
	airline5047_1.getSalesStats(revenue1, passkm1);
	airline5047_2.getSalesStats(revenue2, passkm2);
	cout << "Sales Stats for Airline 5047-A-> Revenue: " <<  revenue1 << "; KMs: " << passkm1 << endl;
	cout << "Sales Stats for Airline 5047-B-> Revenue: " <<  revenue2 << "; KMs: " << passkm2 << endl;

	return 0;
}