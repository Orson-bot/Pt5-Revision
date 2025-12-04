// logger.cpp
// Implementation of the Logger class functions.
// This file rewrites the original implementation with additional
// explanatory comments; no runtime logic has been changed.

#include <iostream>   // std::cout, std::cin
#include <fstream>    // std::ofstream
#include <filesystem> // std::filesystem::create_directory (used when available)
#if defined(_MSC_VER) || defined(_WIN32)
#include <direct.h> // _mkdir on Windows
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h> // mkdir on POSIX
#define MKDIR(path) mkdir(path, 0755)
#endif
#include <ctime>      // std::time_t, std::localtime, std::ctime
#include <string>     // std::string, std::to_string
#include "logger.h"  // Logger class declaration (project header)

using namespace std;                     // bring common std names into scope
using std::chrono::system_clock;         // use the system clock type directly
using std::cout;                         // bring cout into global scope here

// Constructor: called when a Logger object is instantiated.
// Responsibilities:
// - Grab the current time
// - Create the Logs directory (if it does not already exist)
// - Build a daily filename in the format YYYY-M-D.txt and store
//   the full path in `pathFile` for later use when writing logs.
Logger::Logger()
{
	// Capture the current time as a time_t value.
	tt = system_clock::to_time_t(system_clock::now());

	// Convert the time_t to a C-style string like "Wed Jun 30 21:49:08 1993\n".
	// ctime returns a pointer to an internal static buffer, so we copy
	// into our std::string member for safe, long-lived storage.
	timeStamp = ctime(&tt);

	// Convert time_t to broken-down local time components (year, month, day, etc.).
	tm local_tm = *localtime(&tt);

	// Start building the path where logs are stored. By default the code
	// places logs in a `Logs` directory in the working directory.
	pathFile = "Logs/";

	// Ensure the Logs directory exists. Prefer std::filesystem when
	// available; fall back to a small MKDIR macro for toolchains that
	// lack full filesystem support. MKDIR is a thin wrapper around
	// _mkdir (Windows) or mkdir (POSIX).
	MKDIR("Logs");

	// Echo the human-readable timestamp to the console (same behavior as before).
	cout << timeStamp;

	// Build the file name using the broken-down time components. The year
	// is stored in tm_year as years since 1900, tm_mon is 0-based.
	fileName = to_string(local_tm.tm_year + 1900);
	fileName += '-';                         // separator between parts
	fileName += to_string(local_tm.tm_mon + 1); // month: +1 to convert from 0-based
	fileName += '-';
	fileName += to_string(local_tm.tm_mday); // day of month
	fileName += ".txt";                    // file extension

	// Combine directory and file name to form the full path used by writes.
	pathFile += fileName;
}

// Update the stored timestamp to the current time.
// This method refreshes both the `tt` and `timeStamp` members.
void Logger::setTimeStamp()
{
	tt = system_clock::to_time_t(system_clock::now());
	timeStamp = ctime(&tt);
}

// Return a fresh timestamp string. This calls setTimeStamp so the returned
// value reflects the moment the function is invoked.
std::string Logger::getTimeStamp()
{
	setTimeStamp();      // refresh internal timestamp state
	return timeStamp;    // return the (C-string-copy) representation
}

// Append a message to the current log file. The function supports two modes:
// - When `getNumberList` is true, it expects a number list in `numList` and
//   delegates to `displayNumberList` to format and write that list.
// - Otherwise, it appends the provided `message` text directly to the log file.
// Parameters:
// - message: textual content to append to the log file when not handling numbers.
// - getNumberList: when true, format and log the integer list provided below.
// - numList: pointer to an array of integers (used when getNumberList == true).
// - size: length of the integer array.
void Logger::createNewLog(std::string message, bool getNumberList, int numList[], int size)
{
	// Open the file in append mode so we never overwrite previous logs.
	ofstream MyFile(pathFile, std::ios::app);

	// If the file couldn't be opened (e.g. permissions or path problems),
	// safely return without attempting any writes. The caller receives
	// no error code here; this mirrors the original simple behavior.
	if (!MyFile.is_open())
	{
		return;
	}

	// If caller requested number-list handling, pass control to that helper.
	if (getNumberList)
	{
		displayNumberList(numList, size);
		return; // helper handles the write and returns
	}

	// Otherwise, write the provided message into the file.
	MyFile << message;

	// Explicitly close the file to flush buffers and release the handle.
	MyFile.close();
}

// Format an array of integers into a hyphen-separated string and append
// it to the log. Example output for {1,2,3} becomes "1-2-3\n\n".
// This function constructs the formatted text, then calls createNewLog
// to perform the actual append operation (keeps responsibilities separated).
void Logger::displayNumberList(int numList[], int size)
{
	// Build the full hyphen-separated list as a std::string.
	std::string fullList;
	for (int i = 0; i < size; i++)
	{
		fullList += std::to_string(numList[i]);
		if (i != size - 1)
		{
			// Add a hyphen between numbers, but not after the last one.
			fullList += '-';
		}
	}

	// Match original behavior by appending two newlines after the list.
	fullList += "\n\n";

	// Delegate write to createNewLog. Use the same API used elsewhere
	// (pass getNumberList=false so createNewLog writes the message directly).
	createNewLog(fullList, false, nullptr, 0);
}

// Small helper that asks the user whether to record the session. Returns
// true when the user types the single character '1'. The function reads
// from standard input and writes a short prompt to standard output.
bool askSessionLog()
{
	char userInput;
	cout << "Type '1' if you'd like to record this session in the logs." << '\n';
	cin >> userInput;

	if (userInput == '1')
	{
		return true;
	}

	return false;
}