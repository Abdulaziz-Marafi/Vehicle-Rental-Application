#pragma once
#include <iostream>
#include "Rental.h"
#include <iomanip>
#include <fstream>


using namespace std;

// Generic class used to store records.
class RentalManager
{

public:
	RentalManager();
	~RentalManager();
	
	// Array management Methods:
	void push(Rental* value);
	void reSize();
	Rental* get(int index);
	int getSize();

	// Methods to add to the rental class variables:
	void addIncome(int income);
	void addDays(int days);

	// Display methods:
	void menuDisplay() const;
	void rentalDisplay(int index);

	// File management functions (read and write).
	void diskWrite(string regNum);
	void diskRead(string regNum);

private:

	// Variables related to the rental class. 
	double totalIncome;
	int totalDaysRented;
	

	int size;
	int numRecords;
	Rental** rentalRecords;
};

// Takes in an object/item. Checks if the array is full and stores the item in the array.
inline void RentalManager::push(Rental* value)
{
	// Check if array is full, if so then resize.
	if ((numRecords + 1) == size)
	{
		reSize();
	}
	rentalRecords[numRecords] = value;
	numRecords++;
}


// Return a pointer to the object at said index.
inline Rental* RentalManager::get(int index) {
	if (index < 0 || index >= numRecords) {
		throw out_of_range("Index out of range.");
	}
	return rentalRecords[index];
}

// Return number of items in array.
inline int RentalManager::getSize()
{
	return numRecords;
}

inline void RentalManager::addIncome(int income)
{
	totalIncome += income;
}

inline void RentalManager::addDays(int days)
{
	totalDaysRented += days;
}
