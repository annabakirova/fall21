#include <iostream>

int readInt() {
	std::cout << "Enter a number:";
	int n;
	std::cin >> n;
	while (std::cin.fail() || (static_cast<int>(n) != n) || n < 0) {
		std::cout << "Wrong input, try again:\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> n;
	}
	return n;
}

int main()
{
	int n = readInt();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			std::cout << "*";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int i = n; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			std::cout << "*";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int i = n; i > 0; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			std::cout << " ";
		}
		for (int j = i - 1; j < n; j++)
		{
			std::cout << "*";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			std::cout << " ";
		}
		for (int j = 0; j < 2*i - 1; j++)
		{
			std::cout << "*";
		}
		std::cout << "\n";
	}
	for (int i = n; i > 0; i--)
	{
		for (int j = 0; j < n - i; j++)
		{
			std::cout << " ";
		}
		for (int j = 0; j < 2 * i - 1; j++)
		{
			std::cout << "*";
		}
		std::cout << "\n";
	}
	return 0;
}