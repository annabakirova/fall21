#pragma once

void fillArrayRandomly(int* a, int size);

void fill2DArrayRandomly(int** a, int rows, int cols);

int** create2DArray(int r, int c);

void print2Darray(int** array, int r, int c);

void initIdMatrix(int** a, int rows, int cols);

bool testInitIdMatrix();

void transposeMatrix(int* matrix, bool* isSwapped, int rows, int columns);

void getSumArray(int** image, int rows, int columns);

int binarySearch(int* a, int num, int start, int end);

void printDiagonal(int** d, int rows, int cols);

void printSpiral(int** d, int rows, int cols);

bool testfill2DWithConstant(int value, int testValue);