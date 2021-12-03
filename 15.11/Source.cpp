#include <iostream>
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include "arrays.h"


int main() {

	if (testfill2DWithConstant(5, 5) && !testfill2DWithConstant(3, 5)) {
		std::cout << "passed\n";
	}
	else {
		std::cout << "failed\n";
	}

	if (testInitIdMatrix()) {
		std::cout << "passed\n";
	}
	else {
		std::cout << "failed\n";
	}

	std::cout << "Enter a number of rows and columns:\n";
	int rows = 3;
	int cols = 4;
	std::cin >> rows >> cols;
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

	return 0;
}