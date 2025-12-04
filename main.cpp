#include <iostream> // I/O streams
#include <ctime>    // srand / time
#include <conio.h>  // getch() on Windows
#include <limits>   // std::numeric_limits used for safe input handling
#include "sorter.h" // bubbleSort, mergeSort, viewNumbers
#include "logger.h" // Logger class and askSessionLog()

// Formatting helpers
#define DASH_LINE "----------\n"

// Upper bound for generated random values (1..LIMIT)
const int LIMIT = 1000;

// Shorten commonly-used std identifiers in this file for readability only.
using std::cout;
using std::cin;

// Forward declarations for helper functions (implemented below)
bool determineSortOrder();
void sortLogger(Logger* Logs, bool sortAscended, int numberList[], int arraySize);
void displayOptions();
void fillList(int nums[], int size);


// main(): program entry point
// - Sets up the logger (optional), generates an initial random list, and
//   presents a simple text menu to run the sorting utilities from `sorter.h`.
// - Important: this program uses dynamic allocation for the number list and
//   for the Logger instance to match the original design; no behavior changed.
int main()
{
	// Create a Logger instance; if the user opts out of logging we will free it.
	Logger* Logs = new Logger();

	// Seed the pseudo-random generator once per run.
	srand(static_cast<unsigned int>(time(NULL)));

	// Default list size and allocation.
	int arraySize = 50;
	int* numberList = new int[arraySize];

	// Fill the list with random numbers.
	fillList(numberList, arraySize);

	bool running = true;
	char userInput;

	// Ask user whether this session should be logged.
	bool loggedSession = askSessionLog();
	if (loggedSession)
	{
		cout << "Your actions in this session will be logged.\n";
	}
	else
	{
		// If not logging, free the Logger instance immediately.
		delete Logs;
		Logs = nullptr;
		cout << "Your actions in this session will not be logged.\n";
	}

	// Title banner
	cout << "---------------=================---------------\n";
	cout << "               ALGORITHM PROGRAM               \n";
	cout << "---------------=================---------------\n";

	// Main menu loop
	do
	{
		displayOptions();
		cin >> userInput;
		cout << DASH_LINE;

		// Clear any leftover input to avoid repeated failures on invalid input.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (userInput)
		{
			case '1':
			{
				// Bubble sort
				bool sortAscended = determineSortOrder();
				bubbleSort(numberList, sortAscended, arraySize);
				if (loggedSession && Logs) sortLogger(Logs, sortAscended, numberList, arraySize);
				viewNumbers(numberList, arraySize);
				break;
			}

			case '2':
			{
				// Merge sort
				bool sortAscended = determineSortOrder();
				mergeSort(numberList, sortAscended, 0, arraySize - 1);
				if (loggedSession && Logs) sortLogger(Logs, sortAscended, numberList, arraySize);
				viewNumbers(numberList, arraySize);
				break;
			}

			case '3':
				// Display current list without modifying it.
				viewNumbers(numberList, arraySize);
				break;

			case '4':
			{
				// Generate a new list with user-specified size.
				delete[] numberList;
				cout << "How many numbers would you like to generate? (10-999): ";

				// Validate the input size from 10..999 inclusive.
				do
				{
					cin >> arraySize;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (arraySize < 10 || arraySize > 999)
						cout << "\nError, please input a valid number from 10-999: ";
				} while (arraySize < 10 || arraySize > 999);

				numberList = new int[arraySize];
				fillList(numberList, arraySize);

				if (loggedSession && Logs)
				{
					Logs->createNewLog(Logs->getTimeStamp().append("Generated a new set of numbers: \n"));
					Logs->createNewLog("", true, numberList, arraySize);
				}

				viewNumbers(numberList, arraySize);
				break;
			}

			case '5':
				// Exit the program loop
				running = false;
				break;

			default:
				cout << "Invalid input! Please input the following:\n";
				break;
		}

	} while (running);

	// Cleanup dynamic allocations before exiting.
	delete[] numberList;
	if (loggedSession && Logs)
	{
		delete Logs;
	}

	cout << "------------------========================------------------\n";
	cout << "                  ENDING ALGORITHM PROGRAM                  \n";
	cout << "------------------========================------------------\n";

	getch();
	return 0;
}


// determineSortOrder(): asks the user whether they want ascending order.
// Returns true for ascending, false for descending.
bool determineSortOrder()
{
	char input;
	cout << "Type 'A' if you'd like to sort ascending. Type any other key to sort descending:\n";
	cout << "User Input: ";
	cin >> input;

	return (input == 'A' || input == 'a');
}


// sortLogger(): utility that writes a timestamped message and the array contents
// to the Logger instance depending on the chosen sort direction.
void sortLogger(Logger* Logs, bool sortAscended, int numberList[], int arraySize)
{
	if (!Logs) return; // defensive: nothing to do when no logger available

	if (sortAscended)
	{
		Logs->createNewLog(Logs->getTimeStamp().append("Reorganized numbers in ascending order: \n"));
	}
	else
	{
		Logs->createNewLog(Logs->getTimeStamp().append("Reorganized numbers in descending order: \n"));
	}

	// Write the actual numbers (second log entry).
	Logs->createNewLog("", true, numberList, arraySize);
}


// displayOptions(): prints the interactive menu to the console.
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


// fillList(): populates `nums[0..size-1]` with pseudo-random values in 1..LIMIT
void fillList(int nums[], int size)
{
	cout << "Generating numbers...\n";
	for (int i = 0; i < size; ++i)
	{
		nums[i] = (rand() % LIMIT) + 1;
	}
}