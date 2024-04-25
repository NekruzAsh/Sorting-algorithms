/*

	CS2028C Lab 13
	
	Group 01
	
	Arvish Pandey
	Nekruz Ashrapov
	
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <chrono>

#include "LinkedList.h"

using namespace std;

typedef std::chrono::high_resolution_clock Clock;
// Function to generate a random integer up to max_val
int generateRandomInt(int max_val) {
	return rand() % (max_val + 1);
}
// Function to generate a random array of given size
int* generateRandomArray(int size) {
	int* array = new int[size];
	for (int i = 0; i < size; ++i) {
		array[i] = generateRandomInt(2 * size); // Generating random numbers within a range
	}
	return array;
}
// Function to print an array	
void printArray(int* array, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}
// Bubble Sort algorithm
void bubbleSort(int* array, int size) {
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if (array[j] > array[j + 1]) {
				std::swap(array[j], array[j + 1]);
			}
		}
	}
}
// Insertion Sort algorithm
void insertionSort(int* array, int size) {
	for (int i = 1; i < size; ++i) {
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
}
// Merge function used in Merge Sort
void merge(int* array, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1; ++i)
		L[i] = array[left + i];
	for (int j = 0; j < n2; ++j)
		R[j] = array[mid + 1 + j];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			array[k] = L[i];
			++i;
		}
		else {
			array[k] = R[j];
			++j;
		}
		++k;
	}

	while (i < n1) {
		array[k] = L[i];
		++i;
		++k;
	}

	while (j < n2) {
		array[k] = R[j];
		++j;
		++k;
	}

	delete[] L;
	delete[] R;
}
// Merge Sort algorithm
void mergeSortHelper(int* array, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSortHelper(array, left, mid);
		mergeSortHelper(array, mid + 1, right);
		merge(array, left, mid, right);
	}
}

void mergeSort(int* array, int size) {
	mergeSortHelper(array, 0, size - 1);
}
// Partition function used in Quick Sort
int partition(int* array, int low, int high) {
	int pivot = array[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; ++j) {
		if (array[j] < pivot) {
			++i;
			std::swap(array[i], array[j]);
		}
	}
	std::swap(array[i + 1], array[high]);
	return i + 1;
}
// Quick Sort algorithm
void quickSortHelper(int* array, int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);
		quickSortHelper(array, low, pi - 1);
		quickSortHelper(array, pi + 1, high);
	}
}

void quickSort(int* array, int size) {
	quickSortHelper(array, 0, size - 1);
}
// Counting Sort algorithm
void countingSort(int* array, int size) {
	int max_val = *std::max_element(array, array + size);
	int min_val = *std::min_element(array, array + size);
	int range = max_val - min_val + 1;

	int* count = new int[range] {};
	int* output = new int[size];

	for (int i = 0; i < size; ++i)
		++count[array[i] - min_val];

	for (int i = 1; i < range; ++i)
		count[i] += count[i - 1];

	for (int i = size - 1; i >= 0; --i) {
		output[count[array[i] - min_val] - 1] = array[i];
		--count[array[i] - min_val];
	}

	for (int i = 0; i < size; ++i)
		array[i] = output[i];

	delete[] count;
	delete[] output;
}
// Radix Sort algorithm
void radixSort(int* array, int size) {
	int max_val = *std::max_element(array, array + size);

	for (int exp = 1; max_val / exp > 0; exp *= 10)
		countingSort(array, size);
}
// Function to measure execution time of sorting algorithms
long long measureExecutionTime(void (*sortingFunc)(int*, int), int* array, int size, int repetitions) {
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < repetitions; ++i) {
		int* temp_array = new int[size];
		std::copy(array, array + size, temp_array);
		sortingFunc(temp_array, size);
		delete[] temp_array;
	}
	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / repetitions;
}
// Function to perform efficiency tests on sorting algorithms
void EfficiencyTest() {
	srand(time(nullptr));

	int sizes[] = { 10, 100, 500, 5000, 25000, 100000 };
	int iterations = 10;

	std::cout << "Execution times in nanoseconds (average of " << iterations << " runs):\n";
	std::cout << "-----------------------------------------------------------\n";

	for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
		int size = sizes[i];
		int* array = generateRandomArray(size);
		std::cout << "Array of size " << size << ":\n";

		// Bubble Sort
		long long bubble_time = measureExecutionTime(bubbleSort, array, size, iterations);
		std::cout << "Bubble Sort: " << bubble_time << " nanoseconds\n";

		// Insertion Sort
		long long insertion_time = measureExecutionTime(insertionSort, array, size, iterations);
		std::cout << "Insertion Sort: " << insertion_time << " nanoseconds\n";

		// Merge Sort
		long long merge_time = measureExecutionTime(mergeSort, array, size, iterations);
		std::cout << "Merge Sort: " << merge_time << " nanoseconds\n";

		// Quick Sort
		long long quick_time = measureExecutionTime(quickSort, array, size, iterations);
		std::cout << "Quick Sort: " << quick_time << " nanoseconds\n";

		// Counting Sort
		long long counting_time = measureExecutionTime(countingSort, array, size, iterations);
		std::cout << "Counting Sort: " << counting_time << " nanoseconds\n";

		// Radix Sort
		long long radix_time = measureExecutionTime(radixSort, array, size, iterations);
		std::cout << "Radix Sort: " << radix_time << " nanoseconds\n";

		std::cout << std::endl;

		delete[] array;
	}
}

int main() {
	std::cout << "Do you want to implement efficiency testing: Y/N: " << std::endl; 
	std::string choice;
	std::cin >> choice;

	if (choice == "Y") EfficiencyTest(); // Perform efficiency testing if chosen

	LinkedList list;

	list.insert(Student("John", "Doe", 123));
	list.insert(Student("Alice", "Smith", 456));
	// Add more students...

	int option;
	bool ascending;
	// Prompting the user for sorting options
	std::cout << "Press 1 to perform Merge Sort by First Name\n";
	std::cout << "Press 2 to perform Quick Sort by Last Name\n";
	std::cout << "Press 3 to perform Insertion Sort by ID Number\n";
	std::cin >> option;

	std::cout << "Press 1 to sort in ascending order\n";
	std::cout << "Press 2 to sort in descending order\n";
	std::cin >> option;

	ascending = (option == 1); // Determining sorting order
	// Switch case to perform selected sorting operation
	switch (option) {
	case 1:
		list.mergeSortFirstName(ascending); // Sort by first name using Merge Sort
		break;
	case 2:
		list.quickSortLastName(ascending); // Sort by last name using Quick Sort
		break;
	case 3:
		list.insertionSortIdNumber(ascending); // Sort by ID number using Insertion Sort
		break;
	default:
		std::cout << "Invalid option\n";
		break;
	}

	list.display(); // Display the sorted linked list
	return 0;
}