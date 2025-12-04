#include <iostream>
#include <conio.h>
#include "sorter.h"

// sorter.cpp
// Simple sorting utilities used in the project: Bubble Sort and Merge Sort
// Each function operates in-place on a plain C-style integer array.

// NOTE: This file intentionally preserves the original algorithm implementations.
// The changes here are comment/clarity-only; no algorithmic behavior was altered.

// Bubble Sort
// - Parameters:
//   - numberList: array of integers to sort (modified in-place)
//   - sortAscended: if true, sort ascending; if false, sort descending
//   - size: number of elements in `numberList`
// - Complexity: O(n^2) time, O(1) extra space
void bubbleSort(int numberList[], bool sortAscended, int size)
{
	// Print which direction we're sorting in.
	if (sortAscended)
		std::cout << "--SORTING THROUGH ASCENDED--\n";
	else
		std::cout << "--SORTING THROUGH DESCENDED--\n";

	int temp; // temporary value used for swapping two elements

	// Outer loop: perform `size` passes. Each pass moves the next largest/smallest
	// element into its correct position at the end of the (unsorted) section.
	for (int i = 0; i < size; i++)
	{
		// Inner loop: compare adjacent pairs up to the last unsorted element.
		for (int j = 0; j < size - i - 1; j++)
		{
			if (sortAscended && numberList[j] > numberList[j + 1])
			{
				// For ascending sort: if current > next, swap them.
				temp = numberList[j];
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
			else if (!sortAscended && numberList[j] < numberList[j + 1])
			{
				// For descending sort: if current < next, swap them.
				temp = numberList[j];
				numberList[j] = numberList[j + 1];
				numberList[j + 1] = temp;
			}
		}
	}
}

// Merge Sort
// - Parameters:
//   - numberList: array of integers to sort (modified in-place)
//   - sortAscended: if true, sort ascending; if false, sort descending
//   - low: index of the start of the section to sort
//   - high: index of the end of the section to sort
// - Complexity: O(n log n) time, O(n) additional space for merging
// This function is the recursive divide-and-conquer driver; it splits the
// array and then merges sorted halves via `merge()` below.
void mergeSort(int numberList[], bool sortAscended, int low, int high)
{    
	if (low < high)
	{
		// Middle point to divide the array into two halves.
		int mid = (low + high) / 2;

		// Recursively sort the lower half and the upper half.
		mergeSort(numberList, sortAscended, low, mid);
		mergeSort(numberList, sortAscended, mid + 1, high);

		// Merge the two sorted halves back together.
		merge(numberList, low, high, mid, sortAscended);
	}

	// When low >= high, the section is size 0 or 1 and already sorted.
	return;
}

// merge(): helper that merges two consecutive sorted subarrays inside `numberList`.
// - The first subarray is numberList[low..mid] and the second is numberList[mid+1..high].
// - The function writes merged results into a temporary array and copies them back.
// Note: the original implementation used a fixed-size local array; the existing
// code preserves that behavior and only improves the comments for clarity.
void merge(int numberList[], int low, int high, int mid, bool sortAscended)
{
	// Temporary array used for merging the section [low..high].
	// The original code declares `tempArray[high]` which relies on a compiler
	// extension (variable-length arrays). We keep the same declaration here
	// to avoid changing the runtime behavior; however, be aware this is not
	// standard ISO C++ and may not compile on all toolchains.
	int i, j, k, tempArray[high];

	// i: current index in the left subarray (low..mid)
	// j: current index in the right subarray (mid+1..high)
	// k: current index in the temporary array (we reuse the same indices)
	i = low;
	k = low;
	j = mid + 1;

	// Merge elements from the two subarrays into tempArray in the desired order.
	while (i <= mid && j <= high)
	{
		if (sortAscended)
		{
			if (numberList[i] < numberList[j])
			{
				tempArray[k++] = numberList[i++];
			}
			else
			{
				tempArray[k++] = numberList[j++];
			}
		}
		else
		{
			if (numberList[i] > numberList[j])
			{
				tempArray[k++] = numberList[i++];
			}
			else
			{
				tempArray[k++] = numberList[j++];
			}
		}
	}

	// Copy any remaining elements from the left subarray.
	while (i <= mid)
	{
		tempArray[k++] = numberList[i++];
	}

	// Copy any remaining elements from the right subarray.
	while (j <= high)
	{
		tempArray[k++] = numberList[j++];
	}

	// Copy the merged content back into the original array.
	for (i = low; i < k; i++)
	{
		numberList[i] = tempArray[i];
	}
}

// viewNumbers(): simple utility to print the contents of an integer array.
// - numList: array of integers
// - size: number of elements in the array
void viewNumbers(int numList[], int size)
{
	std::cout << "Viewing all numbers:\n";

	for (int i = 0; i < size; i++)
	{
		// Print a comma after each element except the last for nicer formatting.
		if (i == size - 1)
			std::cout << numList[i];
		else
			std::cout << numList[i] << ", ";
	}

	std::cout << '\n';
	std::cout << "**********************************************\n";
}