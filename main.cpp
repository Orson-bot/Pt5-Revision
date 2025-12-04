#include <iostream> // used for input & output streams
#include <ctime> // used for random number generator
#include <conio.h> // used for getch()
#include <limits> // used for garbage input
#include "sorter.h" // includes the sorter file and its function
#include "logger.h" // includes the logger file and its function

#define SORT_ASCENDED true // used for file readability
#define DASH_LINE "----------\n"

const int LIMIT = 1000; // set a limit for the range of numbers that will never be changed on runtime

// using namespaces to shorten SPECIFIC use cases of std
using std::cout;
using std::cin;

// Declaring Functions
bool determineSortOrder();
void sortLogger(Logger* Logs, bool sortAscended, int numberList[], int arraySize);
void displayOptions();
void fillList(int nums[], int size);


// Main Function
int main()
{
	Logger* Logs = new Logger(); // using dynamic memory allocation to create the logger file so we can delete it when necesarry
	srand(time(NULL)); // generate a random seed for this session
	
	int arraySize = 50; 
	int* numberList = new int[arraySize]; // dynamically create an array with the array size of 50
	bool sortAscended;
	
	fillList(numberList, arraySize); // fill the numberList array
	bool running = true;
	
	char userInput;
	bool loggedSession = askSessionLog(); 
	
	if(loggedSession == true)
	{
		cout << "Your actions in this session will be logged.\n";
	}
	else
	{
		delete Logs; // free up memory at Logs
		cout << "Your actions in this session will not be logged.\n";
	}
	
	cout << "---------------=================---------------\n";
	cout << "               ALGORITHM PROGRAM               \n"; // cool title sequence
	cout << "---------------=================---------------\n";
	
	do
	{
		displayOptions();
		cin >> userInput;
		cout << DASH_LINE;
		
		std::cin.clear(); // clear any error flags at cin.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip to new line and proceed with the program for no further issues.
		
		switch(userInput)
		{
			case '1': // Sort Through Bubble Sort Algorithm
				sortAscended = determineSortOrder();
				
				bubbleSort(numberList, sortAscended, arraySize); // Start the Sorting Algorithm
				if(loggedSession) {sortLogger(Logs,sortAscended,numberList,arraySize); } // Create Logs if Permitted
				
				viewNumbers(numberList,arraySize);
				break;
			case '2': // Sort Through Merge Sort Algorithm
				sortAscended = determineSortOrder();
				sortAscended == true ? std::cout << "--SORTING THROUGH ASCENDED--\n" : std::cout << "--SORTING THROUGH DESCENDED--\n"; // if sortAscended == true, then we'll output we're ascending it; vice versa.

				mergeSort(numberList, sortAscended, 0, arraySize - 1); // Start the Sorting Algorithm
				if(loggedSession) {sortLogger(Logs,sortAscended,numberList,arraySize); } // Create Logs if Permitted
				
				viewNumbers(numberList, arraySize);
				break;
			case '3': // View Numbers
				viewNumbers(numberList,arraySize);
				break;
			case '4': // Generate A New Number List
				// Free Memory
				delete[] numberList;
				cout << "How much numbers would you like to generate? (10-999): ";
				
				// Make the user give a valid input from 10 -> 999
				do{
					cin >> arraySize;
					std::cin.clear(); // clear any error flags at cin.
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip to new line and proceed with the program for no further issues.
					arraySize < 10 || arraySize > 999 ? cout << "\nError, please input a valid number from 10-999: " : cout << "";
				}while(arraySize < 10 || arraySize > 999);
				
				// Fill the list.
				numberList = new int[arraySize];
				fillList(numberList, arraySize);
				
				// Create Logs
				if(loggedSession)
				{
					Logs->createNewLog(Logs->getTimeStamp().append("Generated a new set of numbers: \n"));
					Logs->createNewLog("", true, numberList, arraySize);
				}
				
				// View List Once Process is Complete
				viewNumbers(numberList,arraySize);
				break;
			case '5': // Exit Program
				running = false;
				break;
			default: // User did not input a valid value
				cout << "Invalid input! Please input the following:\n";
				break;
		}
	}while(running);
	
	// Free up all used memory in the program
	delete[] numberList;
	if(loggedSession)
	{
		delete Logs;
	}
	cout << "------------------========================------------------\n";
	cout << "                  ENDING ALGORITHM PROGRAM                  \n";
	cout << "------------------========================------------------\n";
	
	getch();
	return 0;
}

bool determineSortOrder()
{
	// Ask the user for their input
	char input;
	cout << "Type 'A' if you'd like to sort through ascended. Type any other key to sort through descended:\n";
	cout << "User Input: ";
	cin >> input;
	
	// If input is either 'A' or 'a' then return this bool as true
	if(input == 'A' || input == 'a')
	{
		return true;
	}
	
	return false;
}

void sortLogger(Logger* Logs, bool sortAscended, int numberList[], int arraySize)
{
	if(sortAscended)
	{
		// Create two log files in which it will display the action done, and the numbers themselves
		Logs->createNewLog(Logs->getTimeStamp().append("Reorganized numbers in ascending order: \n"));
		Logs->createNewLog("", true, numberList, arraySize);
	}
	else
	{
		// Create two log files in which it will display the action done, and the numbers themselves
		Logs->createNewLog(Logs->getTimeStamp().append("Reorganized numbers in descending order: \n"));
		Logs->createNewLog("", true, numberList, arraySize);
	}
}

void displayOptions()
{
	cout << "Type 1 to Sort Through Bubble Sort Algorithm\n";
	cout << "Type 2 to Sort Through Merge Sort Algorithm\n";
	cout << "Type 3 to View Numbers\n";
	cout << "Type 4 to Generate New Numbers\n";
	cout << "Type 5 to Exit Program\n";
	cout << DASH_LINE;
	cout << "User Input: ";
}

void fillList(int nums[], int size)
{
	// Generate New Numbers
	cout << "Generating numbers...\n";
	for(int i = 0; i < size; ++i)
	{
		nums[i] = (rand() % LIMIT) + 1;
	}
}