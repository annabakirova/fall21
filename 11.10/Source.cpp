#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

bool checkSumOfDistances(double x1, double y1, double x2, double y2, double x, double y) {
	double dist1 = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
	double dist2 = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
	double eps = 1.0e-10;
	if (abs(dist1 + dist2 - 10.0) < eps) {
		return true;
	}
	else {
		return false;
	}
}

bool checkDistancesWithoutRoot(double x1, double y1, double x2, double y2, double x, double y) {
	double d1 = (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y);
	double d2 = (x2 - x) * (x2 - x) + (y2 - y) * (y2 - y);
	double d3 = (100.0 - d1 - d2) * (100.0 - d1 - d2);
	double d4 = 4 * ((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)) 
		* ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
	double eps = 1.0e-10;
	return (abs(d3 - d4) < eps);
}

int countIntDotsInCircle(double r) {
	double eps = 1.0e-10;
	r = abs(r);
	int num = 0;
	int repeated = 0;
	for (int i = 0; i <= (int)r; i++) {
		for (int j = 0; j <= (int)r; j++) {
			int distSquared = i * i + j * j;
			if (static_cast<int>(distSquared) - r * r < eps) {
				num++;
				if (i < eps || j < eps) {
					repeated++;
				}
			}
		}
	}
	return 4 * (num - repeated) + repeated * 2 - 1;
}

double computePi(int accuracy) {
	double pi = 0.0;
	int sign = 1;
	for (int i = 1; i < accuracy; i += 2) {
		pi += (sign * 1.0) / i;
		sign *= -1;
	}
	return pi * 4;
}

double getSumOfNestedSinX(double x, int accuracy) {
	double sum = 0;
	for (int i = 1; i <= accuracy; i++) {
		x = sin(x);
		sum += x;
	}
	return sum;
}

double getSinX(int n, double x) {
	double sinx = x;
	double part = x;
	int sign = 1;
	for (int i = 1; i <= n; i++) {
		sign *= -1;
		part *= (sign * x * x) / ((2.0 * i) * (2.0 * i + 1.0));
		sinx += part;
	}
	return sinx;
}

int main()
{
	//check if dist(a,b) + dist(c,b) = 10
	double x1, x2, y1, y2, x, y;
	std::cout << "Enter three pairs of real numbers:\n";
	std::cin >> x1 >> y1 >> x2 >> y2 >> x >> y;
	if (checkSumOfDistances(x1, y1, x2, y2, x, y) 
		&& checkDistancesWithoutRoot(x1, y1, x2, y2, x, y)) {
		std::cout << "true\n";
	}
	else {
		std::cout << "false\n";
	}

	//количество целых точек в круге
	double r;
	std::cout << "Enter a radius:\n";
	std::cin >> r;
	std::cout << countIntDotsInCircle(r) << " integer points\n";

	//ducks & rabbits
	int paws;
	std::cout << "Enter a positive integer:\n";
	std::cin >> paws;
	for (int i = 0; i <= paws; i += 2) {
		std::cout << i << " rabbits, " << (paws - i) << " ducks" << "\n";
	}

	//compute pi with given accuracy
	std::cout << "Enter a positive integer:\n";
	int accuracy;
	std::cin >> accuracy;
	std::cout << computePi(accuracy) << "\n";

	//compute a partial sum of sin(...sin(sin(x)))
	std::cout << "Enter an accuracy and x:\n";
	std::cin >> accuracy >> x;
	std::cout << getSumOfNestedSinX(x, accuracy) << "\n";

	//x^2 + y^2 - r^2 = 0
	int n;
	std::cout << "Enter a number of trials and a radius:\n";
	std::cin >> n >> r;
	srand(time(NULL));
	int dotsInCircle = 0;
	double eps = 1.0e-10;
	double randomNumber = ((double)rand() / RAND_MAX) * r;
	for (int i = 0; i <= n; i++) {
		double randomX = ((double)rand() / RAND_MAX) * r;
		double randomY = ((double)rand() / RAND_MAX) * r;
		if (randomX * randomX + randomY * randomY <= eps + r * r) {
			dotsInCircle++;
		}
	}
	double ratio = static_cast<double>(dotsInCircle) / n;
	double pi = 4 * ratio;
	std::cout << "a ratio:" << ratio << "\n";
	std::cout << "Length of a side: " << 2 * r << "\n";
	std::cout << "The circle's area: " << ratio * 4 * r * r << "\n";
	std::cout << "value of pi: " << pi << "\n";

	//sin(x) as taylor's series
	std::cout << "Enter one positive integer and one real number:\n";
	std::cin >> n >> x;
	std::cout << "sin(x): " << getSinX(n, x) << " sin(x)(math.h): " << sin(x) << "\n";


	std::cout << "Enter a positive integer:\n";
	std::cin >> n;
	int sumOfDigits = 0;
	int productOfDigits = 1;
	while (n > 0) {
		sumOfDigits += n % 10;
		productOfDigits *= n % 10;
		n /= 10;
	}
	std::cout << "sum of digits: " << sumOfDigits << ", product of digits: " << productOfDigits << "\n";
}