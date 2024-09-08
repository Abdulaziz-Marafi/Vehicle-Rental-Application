#include "Vehicle.h"
//add more parameters as you go
Vehicle::Vehicle(int age, string& registrationNum, const char* make, string& model): age(age), registrationNum(registrationNum), make(make), model(model)
{
    
}

Vehicle::~Vehicle()
{
	// do i have to free up reg num, make, model in destructor or does it do it automatically?
	
    // Use free
    free((char*)make);
	make = nullptr;

    delete recordArray;
    recordArray = nullptr;
}

// Method to create a registration number and making sure it is in the correct format.
string Vehicle::createRegNum()
{
    string regNum;
    int i = 0;
    do
    {
        // TODO:  FIX INFINITE WILL LOOP.
        cout << "Please enter a registration number: (Must be 7 letters and numbers) " << endl;
        cin >> regNum;

        // string.lengeth to check if length is 7
        if (regNum.length() != 7)
        {
            cout << "The length of the string is: " << regNum.length() << ". You must enter 7 digits." << endl;
           // cin >> regNum;
            continue;
        }
        
        //check if there are any invalid characters 
        while (regNum[i])
        {
            if (!(isalpha(regNum[i]) || regNum[i] >= '0' && regNum[i] <= '9'))
            {
                cout << "The character: " << regNum[i] << " is not allowed" << endl;
                i = 0;
                break;
            } // turn the lowercase letters to upper case
            else if ((isalpha(regNum[i])))
            {
                regNum[i] = toupper(regNum[i]);
            }
            i++;
        }


    } while (i != 7);

    // Include a space in between the regNum
    regNum.insert(4, 1, ' ');

    return regNum;
}

// Display methods:

void Vehicle::displayMenu() 
{
    cout << registrationNum << setw(15);
}

void Vehicle::displaySearch() 
{
    Vehicle::displayMenu();
    displayCost();
    cout << setw(20) << this->make << setw(15) << model << endl;
}

// Rental record related methods:
 
// This method is used to call the rental creation method and also store the days and cost in the array.
void Vehicle::addRental(RentalManager* recordArray)
{
    int days = Rental::createDays();
    double cost = ((getCost() * days) / 100.0);
    Rental* newRental = Rental::createRental(cost, days);
    recordArray->addDays(days);
    recordArray->addIncome(cost);
    recordArray->push(newRental);
}

// Main menu of the records, it shows the vehicle information.
void Vehicle::recordMainMenu() 
{
    int userChoice = 0;

    // Create rental manager instance.
        this->recordArray = new RentalManager();
    
    // Load record array from file
    recordArray->diskRead(registrationNum);

    while (userChoice != 9)
    {
        cout << registrationNum << ": " << setw(1) << make << setw(2) << model << endl;
        cout << "-----------------" << endl;
        cout << "Cost Per Day:                ";
        displayCost();
        
        
        recordArray->menuDisplay();

        cout << "\n1) Rent Vehicle" << endl;
        cout << "2) View historic rentals" << endl;
        cout << "9) Return to main menu" << endl;
        cout << "\nPlease choose an option:" << endl;
        cin >> userChoice;
        cout << "\n\n\n" << endl;
        switch (userChoice)
        {
        case 1:
        {
            addRental(recordArray);
            break;
        }
        case 2:
        {
            recordsDisplayMenu(recordArray);
            break;
        }
        }
    }
    // Save all changes to disk
    recordArray->diskWrite(registrationNum);
    // TODO: release memory from heap?
   
    delete recordArray;
    recordArray = nullptr;
}

// Menu used to show the individual records.
void Vehicle::recordsDisplayMenu(RentalManager* recordArray)
{
    int position = 0;
    int userChoice = 0;
    while (userChoice != 9) 
    {
        // Rental display portion.
        cout << registrationNum << ": " << setw(1) << make << setw(1) << model << setw(1) << "Rental History" << endl;
        cout << "--------------------------------" << endl;
        recordArray->rentalDisplay(position);

        // User choice portion.
        cout << "\n\n1) View the previous record" << endl;
        cout << "2) View the next record" << endl;
        cout << "9) Return to vehicle information screen" << endl;
        cout << "\nPlease choose an option:" << endl;
        cin >> userChoice;
        cout << "\n\n\n" << endl;
        switch (userChoice)
        {
        case 1:
        {
            position--;
            break;
        }
        case 2:
        {
            position++;
            break;
        }
        }
    }
}



