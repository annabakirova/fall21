#include <iostream>

//int readInt() {
//	std::cout << "Enter a number:";
//	int n;
//	std::cin >> n;
//	while (std::cin.fail() || (static_cast<int>(n) != n) || n < 0) {
//		std::cout << "Wrong input, try again:\n";
//		std::cin.clear();
//		std::cin.ignore(256, '\n');
//		std::cin >> n;
//	}
//	return n;
//}

int main()
{
	std::cout << sizeof(12345.1234);
	return 0;
}