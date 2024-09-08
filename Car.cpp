#include "Car.h"


Car::Car(int age, string registrationNum, const char* make, string model, int numSeats, int numDoors) : Vehicle( age, registrationNum, make, model), numSeats(numSeats), numDoors(numDoors)
{

}
Car::~Car()
{

}

// Method to gather all parameters to create a car.
Car* Car::addCar(string& regNum)
{
		string model, sMake;
		int age, seats, doors;
		
		cout << "Please enter the car age: " << endl;
		cin >> age;

		cout << "Please enter the car make: " << endl;
		cin >> sMake;
		char* make=(char*) malloc(sMake.size() + 1);
		strcpy_s(make, sMake.size()+1,sMake.c_str());

		cout << "Please enter a car model: " << endl;
		cin >> model;

		cout << "Please enter the number of seats in the car: " << endl;
		cin >> seats;

		cout << "Please enter the number of doors in the vehicle: " << endl;
		cin >> doors;

		Car* newCar = new Car(age, regNum, make, model, seats, doors);

		return newCar;
	
}

// Display Functions:

void Car::displayMenu() 
{
	this->Vehicle::displayMenu();
	this->displayCost();
	cout << setw(12) << "Car" << endl;
}

// Used to display cost.
void Car::displayCost() const
{
	if (getCost() >= 1000)
	{
		// would doing it in string instead be better?
		double cost = (getCost() / 100.0);
		cout << "$" << fixed << setprecision(2) << cost;
	}
	else
	{
		int cost = 10;
		cout << "$" << cost << ".00";
	}
}

