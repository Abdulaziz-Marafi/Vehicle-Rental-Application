#pragma once
#include <vector>
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"
#include <fstream>
#include <algorithm>

using namespace std;

class Manager
{

public:

	// Singleton reltaed functions.
	static Manager* getInstance();
	static void releaseInstance();
	~Manager();

	// File management functions (read and write).
	void diskWrite();
	void diskRead();

	// Adding vehicle to vector method, and related methods:
	void addVehicle(Vehicle* vehicle);
	bool regNumUniq(string& regNum) const;

	// Vector display methods:
	void displayVec() const;
	void displaySearch() const;

	// Vector Search methods:
	void carSearch(int number, int type);
	void bikeSearch(int number, int type);
	void regNumCheck(string& regNum);

	// Vector Sorting methods.
	void regNumSort();
	void costSort();
	

	// Vector/Vehicle manipulation methods:
	void removeVehicle(int vehicleChoice);

	// Rentals methods:
	void vehicleRentals();


private:
	Manager();

	 vector<Vehicle*> vehicleList;
	 static Manager* singleton;

	 // vector used to hold temporary vehicles
	 vector<Vehicle*> tempList;


};

// Singleton related functions:
// Create an instance if it does not exist, otherwise return itself.
inline Manager* Manager::getInstance()
{
	if (singleton == nullptr)
	{
		singleton = new Manager();
	}
	return singleton;
}

inline void Manager::releaseInstance()
{
	// add method to iterate and delete/nullptr all objects
	delete singleton;
	singleton = nullptr;
	
}
// TODO: Delete every item from vector properly.

// Pushback vehicle into vector. 
inline void Manager::addVehicle(Vehicle* vehicle)
{
	vehicleList.push_back(vehicle);
}

// Sorting Functions:

// Function that sorts the vehicles in the vector by registration number order.
// TODO: check why the overload does not work.
inline void Manager::regNumSort()
{
	sort(vehicleList.begin(), vehicleList.end(), [](Vehicle* LHS, Vehicle* RHS){return LHS->regNumComp(RHS);});
}
// Function that sorts the vehicles in the vector by cost.
inline void Manager::costSort()
{
	sort(vehicleList.begin(), vehicleList.end(), [](Vehicle* LHS, Vehicle* RHS) {return LHS->getCost() < RHS->getCost();});
}


