#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <iomanip>
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"
#include "Manager.h"
#include <crtdbg.h>

using namespace std;

void addVehicle();
void searchCar();
void searchBike();
void removeVehicle();
void addCar();
void addBike();

int main()
{
#ifdef _DEBUG
	 _CrtSetBreakAlloc(417);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	// start coding here
	srand((int)time(nullptr));

	// Calling the function to load vehicles from disk
	Manager::getInstance()->diskRead();

	// Creating the main menu 

	int userChoice = 0;

	while (true) 
	{
	// Main menu display 
		cout << "Vehicle Rental System" << endl;
		cout << "---------------------\n" << endl;
		cout << "Registration Number" << setw(15) << "Cost Per Day" << setw(15) << "Vehicle Type" << std::endl;
		cout << "-------------------" << setw(15) << "------------" << setw(15) << "------------" << std::endl;
		// Method to display list of rental vehicles from disk.
		Manager::getInstance()->displayVec();

		cout << "\n";
		cout << "1) Add vehicle" << endl;
		cout << "2) Remove vehicle" << endl;
		cout << "3) Search for car" << endl;
		cout << "4) Search for bike" << endl;
		cout << "5) Sort vehicles by registration number" << endl;
		cout << "6) Sort by cost per day" << endl;
		cout << "9) Exit" << endl;
		cout << "\nPlease choose an option:" << endl;
		cin >> userChoice;
		cout << "\n\n\n" << endl;

		switch (userChoice) {
		case 1:
			// Contains variables to store vehicle data, method to create vehicle, and a method to store vehicle in vector.
			addVehicle();
			break;
		case 2:
			removeVehicle();
			break;
		case 3:
			searchCar();
			break;
		case 4:
			searchBike();
			break;
		case 5:
			Manager::getInstance()->regNumSort();
			cout << "\nVehicles have been sorted by the registration number." << endl;
			break;
		case 6:
			Manager::getInstance()->costSort();
			cout << "\nVehicles have been sorted by cost." << endl;
			break;
		case 9:
			Manager::getInstance()->diskWrite();
			Manager::releaseInstance(); // Free up all the data that needs to be freed.
			return 0;
		}
	}

}
void addCar()
{
	string regNum;
	bool unique = true;

	// Check if registration number is unique.
	do {
		regNum = Vehicle::createRegNum();
		unique = Manager::getInstance()->regNumUniq(regNum);
		
	} while (unique);

	// If unique create bike.
	Car* newCar(Car::addCar(regNum));
	Manager::getInstance()->addVehicle(newCar);
}
void addBike()
{
	string regNum;
	bool unique = true;

	// Check if registration number is unique.
	do {
		regNum = Vehicle::createRegNum();
		unique = Manager::getInstance()->regNumUniq(regNum);

	} while (unique);

	// If unique create bike.
	Bike* newBike(Bike::addBike(regNum));
	Manager::getInstance()->addVehicle(newBike);
}
void addVehicle()
{
	int userChoice = 0;

	while (userChoice != 9)
	{
		// Vehicle menu display
		cout << "Add a vehicle:" << endl;
		cout << "-------------\n" << endl;
		cout << "1) Add a car" << endl;
		cout << "2) Add a bike" << endl;
		cout << "9) Return to the main menu" << endl;
		cout << "\nPlease choose an option:" << endl;
		cin >> userChoice;
		cout << "\n\n\n" << endl;

		switch (userChoice)
		{
		case 1:
		{			
			addCar();
			break;
		}
		case 2:
		{
			addBike();
			break;
		}
		}
	}
}

void removeVehicle()
{
	int userChoice = -1;

	while (userChoice != 0)
	{
		// Vehicle removal menu display.
		cout << "Select a vehicle to remove:" << endl;
		cout << "---------------------------\n" << endl;
		cout << "   " << "Registration Number" << setw(15) << "Cost Per Day" << setw(15) << "Make" << setw(15) << "Model" << std::endl;
		cout << "   " << "-------------------" << setw(15) << "------------" << setw(15) << "----" << setw(15) << "-----" << std::endl;

		// Call manager function to display all the vehicle information.
		Manager::getInstance()->displaySearch();
		cout << "\nPlease choose an option or enter 0 to go back to the main menu:" << endl;

		cin >> userChoice;
		if (userChoice != 0)
		{
			Manager::getInstance()->removeVehicle(userChoice);
		}

		cout << "\n\n\n";
	}
}

void searchCar()
{
	int userChoice = 0;
	int num;
	string regNum;

	while (userChoice!=9) 
	{
		// Car search menu display.
		cout << "Search for a car by:" << endl;
		cout << "--------------------\n" << endl;
		cout << "1) Registration number" << endl;
		cout << "2) Number of seats" << endl;
		cout << "3) Number of doors" << endl;
		cout << "9) Return to main menu" << endl;
		cout << "\nPlease choose an option:" << endl;
		cin >> userChoice;
		cout << "\n\n\n" << endl;

		switch (userChoice) 
		{
		case 1:
			// If placed in a class in the future make sure to code deal with the code duplication.
			regNum = Vehicle::createRegNum();
			Manager::getInstance()->regNumCheck(regNum);
			break;
		case 2:
			// Use the same logic for seach for cars and doors to display the correct vehicles with the parameters set.
			cout << "Please enter the number of seats: " << endl;
			cin >> num;
			Manager::getInstance()->carSearch(num, 0);
			break;
		case 3:
			cout << "Please enter the number of doors: " << endl;
			cin >> num;
			Manager::getInstance()->carSearch(num, 1);
			break;
		case 9:

			break;
		}
	}
}

void searchBike()
{
	int userChoice = 0;
	int num;
	string regNum;

	while (userChoice != 9)
	{
		// car search menu display 
		cout << "Search for a bike by:" << endl;
		cout << "--------------------\n" << endl;
		cout << "1) Registration number" << endl;
		cout << "2) Size of engine" << endl;
		cout << "3) Number of wheels" << endl;
		cout << "9) Return to main menu" << endl;
		cout << "\nPlease choose an option:" << endl;
		cin >> userChoice;
		cout << "\n\n\n" << endl;
		switch (userChoice)
		{
		case 1:
			regNum = Vehicle::createRegNum();
			Manager::getInstance()->regNumCheck(regNum);

			break;
		case 2:
			cout << "Please enter the size of the engine: " << endl;
			cin >> num;
			Manager::getInstance()->bikeSearch(num, 0);
			break;
		case 3:
			//TODO: Check why it's not displaying the right ones.
			cout << "Please enter the number of wheels: " << endl;
			cin >> num;
			Manager::getInstance()->bikeSearch(num, 1);
			break;
		case 9:

			break;
		}
	}
}
