#ifndef LOGGER_HELPER
#define LOGGER_HELPER

	#include <string> // used to create string variables
	#include <chrono> // used to keep track of the time stamps
	
	// Declaring the class variables and functions to be used in logger.cpp
	class Logger
	{
		private:
			// Time Stamp
			std::time_t tt;
			std::string timeStamp;
			
			// File Name
			tm local_tm; // returns the local time stamp
			std::string fileName; 
			std::string pathFile;
		public:
			Logger();
			void setTimeStamp();
			std::string getTimeStamp();
			void createNewLog(std::string message, bool getNumberList = false, int numList[] = {}, int size = 0);
			void displayNumberList(int numList[], int size);
	};
	
	bool askSessionLog();

#endif