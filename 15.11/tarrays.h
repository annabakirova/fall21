#pragma once

template<class T>
T& getElement(T** array, size_t rows, size_t cols,
	size_t r, size_t c, bool& isInside) {
	if (r >= rows || c >= cols) {
		isInside = false;
		return array[0][0];
	}
	return array[r][c];
}

template<class Type>
void fillArrayWithConstant(Type* a, size_t size, size_t c) {
	for (size_t i = 0; i < size; ++i) {
		a[i] = c;
	}
}

template<class Type>
void fill2DArrayWithConstant(Type** a, size_t rows, size_t cols, size_t c) {
	for (size_t i = 0; i < rows; ++i) {
		fillArrayWithConstant(a[i], cols, c);
	}
}

template<class Type>
void printArray(Type array, size_t size) {
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << " ";
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