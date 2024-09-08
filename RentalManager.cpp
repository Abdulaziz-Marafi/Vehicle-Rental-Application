#include "RentalManager.h"
// Put all code in header file.

RentalManager::RentalManager(): size(5), numRecords(0), totalIncome(0), totalDaysRented(0)
{
	rentalRecords = new Rental * [5];
	for (int i = 0; i < size; i++) {
		rentalRecords[i] = new Rental;
	}
}


RentalManager::~RentalManager()
{
	for (int i = 0; i < size; i++)
	{
		delete rentalRecords[i];
	}
	delete rentalRecords;
	rentalRecords = nullptr;
}

// Creates a new heap array that is twice the size of the old one.

void RentalManager::reSize() {
	size = (2 * size);
	Rental** newRecords = new Rental * [size];
	// Making a copy of the records in the new array.
	for (int i = 0; i < numRecords; i++) {
		newRecords[i] = rentalRecords[i];
	}
	delete rentalRecords;
	rentalRecords = newRecords;
	
}

// Display methods:

void RentalManager::menuDisplay() const
{
	cout << "\nTotal Rental Income:" << setw(15) << totalIncome <<endl;
	cout << "Total Days Rented:" << setw(17) << totalDaysRented << endl;

}

void RentalManager::rentalDisplay(int index)
{
	//if else check to see if the index == numRecords or below
	if ((index <= (numRecords-1) && index >= 0)) 
	{
		cout << "Rental:" << setw(17) << (index + 1) << " of " << numRecords << endl;
		get(index)->displaySelf();
	}
	else
	{
		cout << "No records here please go back.";
	}
}

// File Management Functions:

void RentalManager::diskWrite(string regNum)
{	
	ofstream out(regNum +".txt");
	out << totalIncome << "\n" << totalDaysRented << "\n" << "/" << "\n";
	for (int i = 0; i < numRecords; i++)
	{
		out << rentalRecords[i];
		out << "#\n";
	}
}

void RentalManager::diskRead(string regNum)
{
	ifstream in(regNum + ".txt");
	// retrive the two parameters 
	// TODO: change the else if since it is inefficient.
	int i = 0;
	string line[8];

	// While loop to collect all the data and pushback a rental record.
	while (getline(in, line[i])) 
	{
		if (line[i] == "#")
		{
			int days = stoi(line[i - 7]);
			double cost = stoi(line[i - 6]);
			string start = line[i - 5];
			string end = line[i - 4];
			string name = line[i - 3];
			string address = line[i - 2];
			string num = line[i - 1];
			Rental* newRental = new Rental(days, cost, start, end, name, address, num);

			push(newRental);

			// Reset the string array.
			i = 0;
		}
		else if (line[i] == "/")
		{
			totalIncome = stoi(line[i - 2]);
			totalDaysRented = stoi(line[i - 1]);
			i = 0;
		}
		else 
		{
			i++;
		}
		
	}

}


