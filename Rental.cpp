#include "Rental.h"

Rental::Rental()
{

}

Rental::Rental(int rentalDays, double totalCost, string& startDate, string& endDate, string& customerName, string& address, string& customerNum) : rentalDays(rentalDays), totalCost(totalCost), startDate(startDate), endDate(endDate), customerName(customerName), address(address), customerNum(customerNum)
{

}

Rental::~Rental()
{

}

// Function to collect all the parameters neccessary to create a rental instance.
Rental* Rental::createRental(double totalCost, int days)
{
	string start, end, name, adr, num;

	cout << "Please enter your name: " << endl;
	cin.ignore();
	getline(cin, name);

	cout << "Please enter your address: " << endl;
	getline(cin, adr);

	cout << "Please enter your phone number: " << endl;
	getline(cin, num);

	// Change to chrono if you have the time
	cout << "Please enter the date you will be renting the vehicle: (dd/mm/yyyy) / NO SPACES" << endl;
	cin >> start;

	cout << "Please enter the date you will be returning the vehicle: (dd/mm/yyyy) / NO SPACES " << endl;
	cin >> end;

	Rental* newRental = new Rental(days, totalCost, start, end, name, adr, num);

	return newRental;

}

int Rental::createDays()
{
	int rentDays;
	cout << "Please enter the number of days you will be renting the vehicle for:" << endl;
	cin >> rentDays;
	return rentDays;
}

void Rental::displaySelf() const
{
	cout << "Date From:" << setw(23) << startDate << endl;
	cout << "Date To:" << setw(25) << endDate << endl;
	cout << "Rental Days:" << setw(21) << rentalDays << endl;
	cout << "Total Cost:" << setw(22) << totalCost << endl;
	cout << "Customer Name:" << setw(19) << customerName<< endl;
	cout << "Customer Adress:" << setw(17) << address << endl;
	cout << "Customer Number:" << setw(17) << customerNum << endl;

}


