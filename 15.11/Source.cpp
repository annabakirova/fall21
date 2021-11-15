#include <iostream>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <cassert>

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


void fill2DArrayRandomly(int** a, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		fillArrayRandomly(a[i], cols);
	}
}

template<class Type>
void printArray(Type array, size_t size) {
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int** create2DArray(int r, int c) {
	int** array;
	array = new int* [r];
	for (int i = 0; i < r; ++i) {
		array[i] = new int[c];
	}
	return array;
}

void print2Darray(int** array, int r, int c) {
	for (int x = 0; x < r; ++x) {
		printArray(array[x], c);
	}
	std::cout << std::endl;
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

void sumArray(int** image, int rows, int columns) {
	for (int i = 1; i < columns; ++i) {
		image[0][i] += image[0][i - 1];
	}

	for (int i = 1; i < rows; ++i) {
		image[i][0] += image[i - 1][0];
	}

	for (int x = 1; x < rows; ++x) {
		for (int y = 1; y < columns; ++y) {
			image[x][y] += image[x - 1][y] + image[x][y - 1] + image[x - 1][y - 1];
		}
	}
}

int binarySearch(int* a, int num, int start, int end) {
	int mid;
	while (start <= end) {
		mid = start + (end - start) / 2;
		if (a[mid] == num)
			return mid;
		if (a[mid] < num)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

void printDiagonal(int** d, int rows, int cols) {
	int r = 0;
	int c = 0;

	if (rows == 1 || cols == 1) {
		print2Darray(d, rows, cols);
	}
	else {
		while (r < rows - 1 || c < cols - 1) {
			std::cout << d[r][c] << " ";
			if (r == 0 && (c % 2) == 0 && c != cols - 1 || r == rows - 1 && (rows - c) % 2 == 0) {
				c++;
			}
			else if (c == 0 && r % 2 == 1 && r != rows - 1 || c == cols - 1 && (cols - r) % 2 == 1) {
				r++;
			}
			else if ((r + c) % 2 == 0) {
				--r;
				++c;
			}
			else if ((r + c) % 2 == 1) {
				++r;
				--c;
			}
		}
		std::cout << d[r][c] << std::endl;
	}
}

void printSpiral(int** d, int rows, int cols) {
	int start = 0;
	int r = rows;
	int c = cols;
	while (r > 0 && c > 0) {
		int i = start;
		int j = start;
		while (j < start + c) {
			std::cout << d[i][j] << " ";
			++j;
		}
		--j;
		++i;
		while (i < start + r) {
			std::cout << d[i][j] << " ";
			++i;
		}
		--i;
		--j;
		while (r > 1 && j >= start) {
			std::cout << d[i][j] << " ";
			--j;
		}
		++j;
		--i;
		while (c > 1 && i > start) {
			std::cout << d[i][j] << " ";
			--i;
		}
		++i;
		++start;
		r -= 2;
		c -= 2;
	}
	std::cout << std::endl;
}

//int findElement(int** image, int index, int rows, int columns, int num) {  //index from which diagonal element to start 
//	int diag = (rows < columns) ? rows : columns;     // a number of diagonals in subarray
//	int i = index;
//
//	if (rows == 1) {
//		return binarySearch(image[rows], num, index, columns);
//	}
//
//	while (i < diag && image[i][i] <= num) {
//		if (image[i][i] == num) {
//			return i;
//		}
//		++i;
//	}
//	if (i > 0) {
//		return findElement(image, index, rows - i + 1, i - 1, num) +
//			+ findElement(image, i - 1, i - 1, columns - i + 1, num) + 1;
//	}
//	return -1;
//	
//}

template<class T> T& getElement(T** array, size_t rows, size_t cols, size_t r, size_t c, bool& isInside) {
	if (r >= rows || c >= cols) {
		isInside = false;
		return array[0][0];
	}
	return array[r][c];
}

bool testCheckValue() {
	int** a = new int*[3];
	for (int i = 0; i < 3; i++) {
		a[i] = new int[3];
		a[i][0] = 3 * i;
		a[i][1] = 3 * i + 1;
		a[i][2] = 3 * i + 2;
	}
	bool isInside = true;
	if (isInside && 2 == getElement(a, 3, 3, 0, 2, isInside) && 6 == getElement(a, 3, 3, 2, 0, isInside)) {
		return true;
	}
	return false;

}


int main() {

	std::cout << testCheckValue() << "\n";

	std::cout << "Enter a number of rows and columns:\n";
	int rows = 3;
	int cols = 4;
	//std::cin >> rows >> cols;
	int** d = create2DArray(rows, cols);
	fill2DArrayRandomly(d, rows, cols);
	print2Darray(d, rows, cols);
	std::cout << "Diagonal form:\n";
	printDiagonal(d, rows, cols);
	std::cout << "Spiral form:\n";
	printSpiral(d, rows, cols);

	for (int i = 0; i < rows; ++i) {
		delete[] d[i];
	}
	delete[] d;

	int** a = new int* [3];
	for (int i = 0; i < 3; i++) {
		a[i] = new int[3];
		a[i][0] = 3 * i;
		a[i][1] = 3 * i + 1;
		a[i][2] = 3 * i + 2;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << a[i][j] << " ";
		}
	}


	return 0;
}