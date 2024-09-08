#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{

public:
	Car(int age, string registrationNum, const char* make, string model, int numSeats, int numDoors);
	~Car();

	static Car* addCar(string& regNum); //static method used to get all the necessary inputs from the user to create a car.

	// Cost Methods:
	void displayCost() const override;
	int getCost() const override;
	// Display related methods
	
	void displayMenu() override;
	bool doorCheck(int numDoors);
	bool seatCheck(int numSeats);

	// TODO: ask about if there is other methed (other than getters)
	inline friend ostream& operator<<(std::ostream& os, Car* rhs); //overidden method.


private:

	const int numSeats;
	const int numDoors;
};

// ostream overload.
inline ostream& operator<<(std::ostream& os, Car* rhs) 
{
	return os << rhs->returnVehicle() << "\n" << rhs->numSeats << "\n" << rhs->numDoors <<"\n";
}

// Cost methods:
inline int Car::getCost() const
{
	double cost = ceil(2500 - (getAge() * 150) - (numDoors * 200));
	return cost;
}



// Retruns comparison between this->doors to the input.
inline bool Car::doorCheck(int numDoors)
{
	return numDoors == this->numDoors;
}

// Retruns comparison between this->seats to the input.
inline bool Car::seatCheck(int numSeats)
{
	return numSeats == this->numSeats;
}
