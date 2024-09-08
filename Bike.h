#pragma once
#include "Vehicle.h"
class Bike : public Vehicle
{
public:
	//add more parameters as you go
	Bike(int age, string registrationNum, const char* make, string model, int numWheels, int engSize);
	~Bike();

	// Cost Methods:
	void displayCost() const override;
	int getCost() const override;
	int roundEng() const; // Function to round up engine size
	

	// Display related functions
	void displayMenu();
	bool engCheck(int eng);
	bool wheelCheck(int wheels);

	static Bike* addBike(string& regNum); // Static method used to get all the necessary inputs from the user to create a bike.
	friend ostream& operator<<(std::ostream& os, Bike* rhs); // Overidden method.

private:

	const int numWheels;
	const int engSize; // In cc.

};

// The ostream overload for the bike class
inline ostream& operator<<(std::ostream& os, Bike* rhs)
{
	return os << rhs->returnVehicle() << "\n" << rhs->numWheels << "\n" << rhs->engSize << "\n";
}
// Cost Methods:
// Rounding the engine size
inline int Bike::roundEng() const
{
	// integer division to round up to the nearest 100
	int engine = (engSize + 99) / 100 * 100;
	return engine;
}

// Used to display cost.
inline void Bike::displayCost() const
{
	int cost = (getCost()/100);
	cout << "$" << cost << ".00";
}

inline int Bike::getCost() const
{
	return (1500 + roundEng());
}

// Retruns comparison between the engine size to the input.
inline bool Bike::engCheck(int eng)
{
	return eng == this->engSize;
}

// Retruns comparison between the number of wheels to the input.
inline bool Bike::wheelCheck(int wheels)
{
	return wheels == this->numWheels;
}


