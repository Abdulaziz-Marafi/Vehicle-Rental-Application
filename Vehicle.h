#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "RentalManager.h"



//#include <cstring>
// Base class created to be then inherited by the car & bike class.

using namespace std;

class Vehicle
{
public:
	
	 Vehicle(int age, string& registrationNum, const char* make, string& model); 
	~Vehicle();
	
	// Cost method to be overwritten in sub classes.
	virtual void displayCost() const;
	virtual int getCost() const;
	
	// Display related methods.
	virtual void displayMenu();
	void displaySearch();

	// Registration Number relted functions:
	bool regNumCheck(string& regNum) const;
	static string createRegNum();
	bool regNumComp(Vehicle* RHS) const;

	// Rental Record related functions:
	//readfile(regnum)
	//writefile(regnum)
	void recordMainMenu();
	void recordsDisplayMenu(RentalManager* recordArray);

	

protected:
	// Getter to be used in the cost calculations 
	int getAge() const;
	
	// Functions used for the stream operator and overloads.
	friend ostream& operator<<(std::ostream& os, Vehicle* rhs);
	string returnVehicle();

	void addRental(RentalManager* recordArray);

private:

	const int age;
	const string registrationNum;  
	const char* make;	
	const string model;

	// Rental record heap array class.
	RentalManager* recordArray;

};

// Used to retrieve private vehicle data without the use of getters.
inline string Vehicle::returnVehicle()
{
	// Returns a string of all the vehicle private data
	string convertedAge = to_string(age);
	string privVecData = convertedAge + "\n" + registrationNum + "\n" + make + "\n" + model;
	return privVecData;
}

// Ostream method to be overloaded.
inline ostream& operator<<(ostream& os, Vehicle* rhs)
{
	string convertedAge = to_string(rhs->age);
	return os << convertedAge + "\n" + rhs->registrationNum + "\n" + rhs->make + "\n" + rhs->model;
}

inline int Vehicle::getAge() const
{
	return age;
}

// Sorting related boolian check methods:

inline bool Vehicle::regNumCheck(string& regNum) const
{
	return regNum == this->registrationNum;
}

inline bool Vehicle::regNumComp(Vehicle* RHS) const  
{
	return this->registrationNum < RHS->registrationNum;
}

// Virtual function to be overloaded.
inline int Vehicle::getCost() const
{
	return 10;
}

inline void Vehicle::displayCost() const
{
	cout << 10;
}

