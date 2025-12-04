#include <iostream>
#include <conio.h>
#include "sorter.h"

// Bubble Sort Algorithm
void bubbleSort(int numberList[], bool sortAscended, int size)
{
	sortAscended == true ? std::cout << "--SORTING THROUGH ASCENDED--\n" : std::cout << "--SORTING THROUGH DESCENDED--\n"; // if sortAscended == true, then we'll output we're ascending it; vice versa.
	int temp; // create a temporary variable
	
	// Track if every number has been checked
	for(int i = 0; i < size; i++)
	{
		// Compare adjacent elements; since the elements are pushed to the BACK, we do not need to check there anymore.
		for(int j = 0; j < size - i - 1; j++)
		{
			if(sortAscended == true && numberList[j] > numberList[j + 1])
			{
				// The number next to us is LOWER than the current index : we'll switch the numbers. We'll also sort through ascended:
				temp = numberList[j]; // set temporary value to current index value
				
				// Switch the two values
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
			else if(sortAscended == false && numberList[j] < numberList[j + 1])
			{
				// // The number next to us is HIGHER than the current index : we'll switch the numbers. We'll also sort through descended:
				temp = numberList[j]; // set temporary value to current index value
				
				// Switch the two values
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
		}
	}
}

// Merge Sort Algorithm
void mergeSort(int numberList[], bool sortAscended, int low, int high)
{	
	if(low < high)
	{
		// Create a midpoint to split the array
		int mid;
		mid = (low + high)/2;
		
		// Split this array for its lower half
		mergeSort(numberList, sortAscended, low, mid);
		
		// Split this array for its higher half
		mergeSort(numberList, sortAscended, mid+1, high);
		
		// Start to merge the sorted halves array 
		merge(numberList, low, high, mid, sortAscended);
	}
	
	return; // when this is returned, the recursive loop ends as there is no way to split the array any further
}

void merge(int numberList[], int low, int high, int mid, bool sortAscended)
{
	int i,j,k,tempArray[high]; // temporary array size set to be the length needed for this array
	i = low; // index for each half of the array section to be merged. 
	k = low; // index for writing to the temporary array
	j = mid + 1; // index for the other half of the array section to be merged
	
	// Compare and Determine the order of values to copy inside the temporary array. For Example:
	// [0,2 | 1, 3] -> begin to merge by looking at the beginning of each section, then only read the next value if the last value read was lower.
	// READ 0,1 -> 0 is lower, so 0 will be copied first. temp[0], then READ 2 -> 1, 1 is lower so write that to the result, temp[0,1].
	// Then READ 2 -> 3, 2 is lower so write that to the result temp[0,1,2]. By this point the loop will end due to the conditions set.
	while (i <= mid && j <= high)
	{
		if(sortAscended)
		{
			if (numberList[i] < numberList[j])
			{
				// If the number at the section is LESS than the number at the other section, copy it to the temporary array.
				tempArray[k] = numberList[i];
				k++;
				i++;
			}
			else
			{
				// If the number at the section is NOT LESS than the number at the other section, copy the number at the other section to the temporary array.
				tempArray[k] = numberList[j];
				k++;
				j++;
			}
		}
		else
		{
			if(numberList[i] > numberList[j])
			{
				// If the number at the section is GREATER than the number at the other section, copy it to the temporary array.
				tempArray[k] = numberList[i];
				k++;
				i++;
			}
			else
			{
				// If the number at the section is NOT GREATER than the number at the other section, copy the number at the other section to the temporary array.
				tempArray[k] = numberList[j];
				k++;
				j++;
			}			
		}
	}
	
	// If there's any left over values from the lower half, move to the proper position. When this loop executes:
	// That means a value in the lower half was greater than any value in the upper half. Copy the sorted values over. 
	while (i <= mid)
	{
		tempArray[k] = numberList[i];
		k++;
		i++;
	}
	
	// If there's any left over values from the upper half, move to the proper position. When this loop executes:
	// That means a value in the upper half was greater than any value in the lower half. Copy the sorted values over. 
	while (j <= high)
	{
		tempArray[k] = numberList[j];
		k++;
		j++;
	}
	
	// Rewrite the numberList array to be the temporary array value is.
	for (i = low; i < k; i++)
	{
		numberList[i] = tempArray[i];
	}
}

// View Numbers
void viewNumbers(int numList[], int size)
{
	std::cout << "Viewing all numbers:\n";
	
	// Iterate through each integer inside numList, then output it.
	for(int i = 0; i < size; i++)
	{
		if(i == size - 1)
		{
			std::cout << numList[i]; // output this message if i is the last number in the list	
		}
		else
		{
			std::cout << numList[i] << ", " ; // output this message if i is NOT the last number in the list
		}
	}
	
	std::cout << '\n';
	
	std::cout << "**********************************************\n";
}