#pragma once
#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
// class used to create an instance of a rental record.


using namespace std;

class Rental
{

public:

	Rental();
	Rental(int rentalDays, double totalCost, string& startDate, string& endDate, string& customerName, string& address, string& customerNum);
	~Rental();

	// Rental instance creation methods
	static int createDays();
	static Rental* createRental(double totalCost, int days);

	// Operator overloads
	Rental& operator=(const Rental& rhs);
	friend ostream& operator<<(ostream& os, Rental* rhs);

	// Display method
	void displaySelf() const;

	

private:
	
	// Vehicle record instance related members.
	int rentalDays;
	double totalCost; 
	string startDate;
	string endDate;
	string customerName;
	string address;
	string customerNum;


};


// Copy operator overload; making sure that it is not a shallow copy. 
inline Rental& Rental::operator=(const Rental& rhs)
{
	if (this != &rhs)
	{
		// copy data members
		rentalDays = rhs.rentalDays;
		totalCost = rhs.totalCost;
		startDate = rhs.startDate;
		endDate = rhs.endDate;
		customerName = rhs.customerName;
		address = rhs.address;
		customerNum = rhs.customerNum;

		
	}
	return *this;
}

// Stream overload to transfer the data to a txt file.
inline ostream& operator<<(ostream& os, Rental* rhs)
{
	string sDays = to_string(rhs->rentalDays);
	string sCost = to_string(rhs->totalCost);
	return os << sDays + "\n" + sCost + "\n" + rhs->startDate + "\n" + rhs->endDate + "\n" + rhs->customerName + "\n" + rhs->address + "\n" + rhs->customerNum + "\n";
}




