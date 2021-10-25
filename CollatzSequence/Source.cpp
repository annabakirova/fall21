#include <iostream>

unsigned long long readULL() {
	std::cout << "Enter a number:";
	unsigned long long n;
	std::cin >> n;
	while (std::cin.fail() || (static_cast<unsigned long long>(n) != n)) {
		std::cout << "Wrong input, try again:\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> n;
	}
	return n;
}

int main() {
	unsigned long long x;
	x = readULL();
	while (x > 1) {
		if (x & 1) {
			x += x << 1;
			x++;
			std::cout << x << " ";
		}
		else {
			x >>= 1;
			std::cout << x << " ";
		}
	}
	std::cout << "\n";
	return 0;
}