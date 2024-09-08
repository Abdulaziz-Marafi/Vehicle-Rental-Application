#include "Bike.h"
Bike::Bike(int age, string registrationNum, const char* make, string model, int numWheels, int engSize) : Vehicle(age, registrationNum, make, model), numWheels(numWheels), engSize(engSize)
{

}

Bike::~Bike()
{

}


// Method to gather all parameters to create a bike.
Bike* Bike::addBike(string& regNum)
{
	string model, sMake;
	int age, wheels, engine;
	
	cout << "Please enter a vehicle age: " << endl;
	cin >> age;

	cout << "Please enter the vehicle make: " << endl;
	cin >> sMake;
	char* make = (char*)malloc(sMake.size() + 1);
	strcpy_s(make, sMake.size() + 1, sMake.c_str());

	cout << "Please enter the bike model: " << endl;
	cin >> model;

	cout << "Please enter the number of wheels in the bike: " << endl;
	cin >> wheels;

	cout << "Please enter the engine size (in CC): " << endl;
	cin >> engine;

	Bike* newBike = new Bike(age, regNum, make, model, wheels, engine);

	return newBike;
}

// Display Method.
void Bike::displayMenu()
{

	this->Vehicle::displayMenu();
	this->displayCost();
	cout << setw(13) << "Bike" << endl;
}



