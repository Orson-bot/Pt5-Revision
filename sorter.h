#ifndef SORTER_HELPER
#define SORTER_HELPER

	// Declaring functions to be used in sorter.cpp
	void bubbleSort(int numberList[], bool sortAscended, int size);
	void mergeSort(int numberList[], bool sortAscended, int low, int high);
	void merge(int numberList[], int low, int high, int mid, bool sortAscended);
	void viewNumbers(int numList[], int size);

#endif