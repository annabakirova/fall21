#include <iostream>
#include <cstdlib>
#include <string.h>

int findMax(int* a, int size) {
	int max = INT_MIN;
	for (int i = 0; i < size; ++i) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;
}

void fillArrayRandomly(int* a, int size) {
	for (int i = 0; i < size; ++i) {
		a[i] = rand() % 1000;
	}
}

void printArray(int* a, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << a[i] << " ";
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
	delete[] a;



	return 0;
}