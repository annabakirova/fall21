#include <iostream>
#include <cstdlib>
#include <string.h>
#include <algorithm>


void printArray(int* a, int size);
void printArray(char* a, int size);

int findMax(int* a, int size) {
	int max = a[0];
	for (int i = 0; i < size; ++i) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;
}

void fillArrayRandomly(int* a, int size) {
	for (int i = 0; i < size; ++i) {
		a[i] = rand() % 100;
	}
}

void printArray(int* a, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << "\n";
}

void printArray(char* a, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << a[i];
	}
	std::cout << "\n";
}

void printIndexesOfMax(int* a, int size) {
	int max = findMax(a, size);
	for (int i = 0; i < size; ++i) {
		if (a[i] == max) {
			std::cout << i << " ";
		}
	}
	std::cout << "\n";
}

double findMean(int* a, int size) {
	double mean = 0.0;
	for (int i = 0; i < size; ++i) {
		mean += static_cast<double>(a[i]) / size;
	}
	return mean;
}

char* makeRandomHex(char* hexNumber, int size) {
	char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9', 'a', 'b', 'c', 'd', 'e', 'f' };

	for (int i = 0; i < size; ++i) {
		hexNumber[i] = hexDigits[rand() % 16];
	}
	return hexNumber;
}

template<class Type>
Type reverseArray(Type array, size_t size) {
	for (int i = 0; i < size / 2; ++i) {
		size_t temp = array[i];
		array[i] = array[size - i - 1];
		array[size - i - 1] = temp;
	}
	return array;
}

void reverseArrayAroundMean(int* array, int size) {
	double mean = findMean(array, size);
	int i = 0;
	int j = size - 1;
	double eps = 1.0E-20;
	while (i < j) {
		while (static_cast<double>(array[i]) < mean) {
			i++;
		}
		while (static_cast<double>(array[j]) > mean) {
			j--;
		}
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
		i++;
		j--;
	}
}

void printTheMostFrequentElement(int* a, int size) {
	int current = 0;
	int maxFrequent = 0;
	int maxFrequency = 1;
	int currFrequency = 1;
	for (int i = 1; i < size; ++i) {
		if (a[i] == current) {
			currFrequency++;
			if (currFrequency > maxFrequency) {
				maxFrequency = currFrequency;
				maxFrequent = i;
			}
		}
		else {
			current = a[i];
			currFrequency = 1;
		}
	}
	std::cout << "the most frequent element: " << a[maxFrequent] << 
		", number of occurences: " << maxFrequency << "\n";
}

void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void mergeSort(int* array, int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void fillDoubleArray(int* first, int* second, int* a, int size) {
	for (int i = 0; i < size; i++) {
		a[2 * i] = first[i];
		a[2 * i + 1] = second[i];
	}
}

void printArrayAsMatrix(int* matrix, int rows, int columns) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			printf("%3d ", matrix[i * columns + j]);
		}
		std::cout << "\n";
	}
}

void transposeMatrix(int* matrix, bool* isSwapped, int rows, int columns) {
	int swapped = 0;
	int currentIndex = 1;
	int currentValue = matrix[currentIndex];
	int nextIndex;
	int nextValue;
	while (swapped <= rows * columns - 2) {
		nextIndex = currentIndex / columns + rows * (currentIndex % columns);
		nextValue = matrix[nextIndex];
		matrix[nextIndex] = currentValue;
		isSwapped[currentIndex] = true;
		currentIndex = nextIndex;
		currentValue = nextValue;
		++swapped;
		while (isSwapped[currentIndex] && currentIndex < rows * columns - 1) {
			currentIndex++;
			currentValue = matrix[currentIndex];
		}
	}
}

int main() {

	int n;
	std::cin >> n;
	int *a = new int[n];
	std::fill(a, a + n, 0);
	printArray(a, n);
	fillArrayRandomly(a, n);
	printArray(a, n);
	std::cout << findMax(a, n) << "\n";
	printIndexesOfMax(a, n);
	std::cout << findMean(a, n) << "\n";
	reverseArrayAroundMean(a, n);
	printArray(a, n);
	delete[] a;

	char* hexNumber = new char[n];
	hexNumber = makeRandomHex(hexNumber, n);
	printArray(hexNumber, n);
	reverseArray<char*>(hexNumber, n);
	printArray(hexNumber, n);
	delete[] hexNumber;

	int* a2 = new int[n];
	fillArrayRandomly(a2, n);
	std::cout << "A2:\n";
	printArray(a2, n);
	mergeSort(a2, 0, n - 1);
	printArray(a2, n);
	printTheMostFrequentElement(a2, n);
	delete[] a2;

	int* a3 = new int[n];
	fillArrayRandomly(a3, n);
	int* a4 = new int[n];
	fillArrayRandomly(a4, n);
	printArray(a3, n);
	printArray(a4, n);
	int* a5 = new int[2 * n];
	fillDoubleArray(a3, a4, a5, n);
	printArray(a5, 2 * n);
	delete[] a3;
	delete[] a4;
	delete[] a5;


	std::cout << "Enter a number of rows and columns:\n";
	int rows;
	int columns;
	std::cin >> rows >> columns;
	int* matrix = new int[rows * columns];
	bool* isSwapped = new bool[rows * columns];
	for (int i = 0; i < rows * columns; ++i) {
		isSwapped[i] = false;
	}

	fillArrayRandomly(matrix, rows * columns);
	printArray(matrix, rows * columns);
	std::cout << "A:\n";
	printArrayAsMatrix(matrix, rows, columns);
	std::cout << "\n";
	transposeMatrix(matrix, isSwapped, rows, columns);
	std::cout << "A^T:\n";
	printArrayAsMatrix(matrix, columns, rows);

	return 0;
}