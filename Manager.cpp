#include "Manager.h"
Manager::Manager() 
{

}

Manager::~Manager()
{
	// Used to clear up the memory in vehicleList 
	// https://stackoverflow.com/questions/12795196/clearing-a-vector-of-pointers refrence.
	for (auto pointer : vehicleList)
	{
		delete pointer;
	}
	vehicleList.clear();
}

Manager* Manager::singleton= new Manager;

// Disk Management Functions:

// Opperator Overloaded the streaming opperator to be used to send all the vehicle info from the vector to the file.
void Manager::diskWrite()
{
	// Accesses the Opens file and iterates through the list and writes down all the data.
	vector<Vehicle*>::iterator it(vehicleList.begin());
	ofstream out("vehicle.txt");
	
	while (it != vehicleList.end()) {
		if (typeid(**it) == typeid(Car)) {
			out << 0 << "\n";
			out << (static_cast<Car*>(*it++));
			
		}
		else {
			out << 1 << "\n";
			out << (static_cast<Bike*>(*it++));
		}
		out << "#\n";
	}
}

void Manager::diskRead()
{
	// Opens file and reads the data in a predetermined manner, and pushes back the data into a vector.
	ifstream in("vehicle.txt");
	int i = 0;
	string line[8];
	while (getline(in, line[i])) {

		// First if statment is to pushback a Car.
		if (line[i] == "#") {
			if (line[i - 7] == "0") {
				// Retrieve all the car data
				int age = stoi(line[i - 6]);
				string regNum = line[i - 5];
				string sMake = line[i - 4];
				char* make = (char*)malloc(sMake.size() + 1);
				strcpy_s(make, sMake.size() + 1, sMake.c_str());
				string model = line[i - 3];
				int numSeats = stoi(line[i - 2]);
				int numDoors = stoi(line[i - 1]);

				// Construct car and push it back to the vehicleList.
				Car* newCar = new Car(age, regNum, make, model, numSeats, numDoors);
				vehicleList.push_back(newCar);

				// reset the line array 
				i = 0;
			}
			// Second one is to pushback a Bike.
			else if (line[i-7] == "1")
			{
				// Retrieve all the bike data
				int age = stoi(line[i - 6]);
				string regNum = line[i - 5];
				string sMake = line[i - 4];
				char* make = (char*)malloc(sMake.size() + 1);
				strcpy_s(make, sMake.size() + 1, sMake.c_str());
				string model = line[i - 3];
				int numWheels = stoi(line[i - 2]);
				int numEngine = stoi(line[i - 1]);

				// Construct bike and push it back to the vehicleList.
				Bike* newBike = new Bike(age, regNum, make, model, numWheels, numEngine);
				vehicleList.push_back(newBike);

				// reset the line array 
				i = 0;
			}

		}
		else 
		{
			i++;
		}
	
	}
}


// Search and Display Functions: 

// Method to search using the registration number. 
void Manager::regNumCheck(string& regNum)
{
	bool found = false;
	vector<Vehicle*>::const_iterator it(vehicleList.begin());
	while (it != vehicleList.end())
	{
		if (static_cast<Vehicle*>(*it)->regNumCheck(regNum))
		{
			tempList.push_back(*it);
			
			found = true;
		}
		it++;
	}
	// Display no results?
	if (!found)
	{
		cout << "No vehicle exist with that registration number."<< endl;
	}
	else
	{
		vehicleRentals();
	}
}

// Used to check if the user entered registration number is unique (when creating a vehicle).
bool Manager::regNumUniq(string& regNum) const
{
	vector<Vehicle*>::const_iterator it(vehicleList.begin());
	while (it != vehicleList.end())
	{
		if (static_cast<Vehicle*>(*it)->regNumCheck(regNum))
		{
			cout << "\nThe vehicle registration number entered is not unique." << endl;
			return true;
		}
		it++;
	}
	return false;
}

// Iteratre through the list and display the set format (using displayMenu()) depending if it's a car or bike.
void Manager::displayVec() const
{
	vector<Vehicle*>::const_iterator it(vehicleList.begin());
	while (it != vehicleList.end())
	{
		if (typeid(**it) == typeid(Car))
		{
			static_cast<Car*>(*it++)->displayMenu();
		}
		else
		{
			static_cast<Bike*>(*it++)->displayMenu();
		}
	}

}

void Manager::displaySearch() const
{
	// Iterate through the vehicle vector and display the vehicles using the display search method.
	vector<Vehicle*>::const_iterator it(vehicleList.begin());
	int i = 1;
	while (it != vehicleList.end())
	{
		cout << i << ")" << setw(10);
		(*it++)->displaySearch();
		
		i++;
	}
}


void Manager::carSearch(int number, int type) 
{
	// Iterate through the vehicle vector and display the vehicles using the parameters set.
	vector<Vehicle*>::iterator it(vehicleList.begin());

	while (it != vehicleList.end())
	{
		if (type == 1)
		{
			if (typeid(**it) == typeid(Car) && static_cast<Car*>(*it)->doorCheck(number))
			{
				tempList.push_back(*it++);
			}
			else
			{
				it++;
			}
		}
		else if (type == 0)
		{
			if (typeid(**it) == typeid(Car) && static_cast<Car*>(*it)->seatCheck(number))
			{
				tempList.push_back(*it++);
			}
			else
			{
				it++;
			}
		}		
	}
	cout << "\n";

	vehicleRentals();

}

void Manager::bikeSearch(int number, int type)
{
	// Iterate through the vehicle vector and display the vehicles using the parameters set.
	vector<Vehicle*>::iterator it(vehicleList.begin());
	int i = 1;
	while (it != vehicleList.end())
	{
		if (type == 1)
		{
			if (typeid(**it) == typeid(Bike) && static_cast<Bike*>(*it)->wheelCheck(number))
			{
				tempList.push_back(*it++);
			}
			else
			{				
				it++;
			}
		}
		else if (type == 0)
		{
			
			if (typeid(**it) == typeid(Bike) && static_cast<Bike*>(*it)->engCheck(number))
			{
				tempList.push_back(*it++);
				i++;
			}
			else
			{
				it++;
			}
		}

	}
	vehicleRentals();
}

// Data Manipulation Functions:

// Takes in the choice from the user by using a search function to guide the user to pick an appropriate option.
void Manager::removeVehicle(int vehicleChoice)
{
	// Use size of function to check if vehicle in the list then remove said vehicle.
	// TODO: check if is pointer good
	if (vehicleChoice > vehicleList.size() || vehicleChoice < 0)
	{
		cout << "The vehicle number entered is not one of the options.";
	}
	else
	{
		int i = 1;
		vector<Vehicle*>::const_iterator it(vehicleList.begin());
		while (it != vehicleList.end())
		{
			if (i == vehicleChoice)
			{
				delete static_cast<Car*>(*it);
				it = vehicleList.erase(it);
				cout << "Vehicle successfully deleted!" << endl;
			}
			else {
				it++;
			}
			i++;
		}
	}
}

// Asks the user for a number and retrieves vehicle at the index position of said number. Checks if valid and access the record main menu.
// Clears the temporary list after.
void Manager::vehicleRentals()
{
	// Display the vehicles.
	int userChoice = 0;
	cout << "   " << "Registration Number" << setw(15) << "Cost Per Day" << setw(15) << "Make" << setw(15) << "Model" << std::endl;
	cout << "   " << "-------------------" << setw(15) << "------------" << setw(15) << "----" << setw(15) << "-----" << std::endl;
	
	for (int i = 0; i < tempList.size(); i++)
	{
		cout << (i+1) << ")" << setw(10);
		tempList.at(i)->displaySearch();
	}
	cout << "\n";

	do	
	{
		cout << "Enter number to choose vehicle or 0 to return to main menu: " << endl;
		cin >> userChoice;
		if (userChoice < 0 || userChoice > tempList.size())
		{
			cout << "The entered number is not one of the options." << endl;
		}
		else if (userChoice != 0)
		{
			tempList.at((userChoice - 1))->recordMainMenu();
			userChoice = 0;
		}
	} while (userChoice != 0);

	// Clear tempVec to be used in another search method.
	tempList.clear();

}


