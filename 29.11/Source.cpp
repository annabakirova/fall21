#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char getElementByIndex(string in, int r, int c) {
	ifstream inFile;
	inFile.open(in, ios::binary | ios::in);
	char num;
	if (!inFile.is_open()) {
		cout << "failed to open";
	}
	else {
		int rs = 0;
		int cs = 0;
		inFile.read(&num, sizeof(char));
		while (num != '\r') {
			rs *= 10;
			rs += num - '0';
			inFile.read(&num, sizeof(char));
		}
		inFile.seekg(1, ios_base::cur);

		inFile.read(&num, sizeof(char));
		while (num != '\r') {
			cs *= 10;
			cs += (num - '0');
			inFile.read(&num, sizeof(char));
		}
		//cout << rs << " " << cs << endl;
		inFile.seekg(1, ios_base::cur);
		//cout << "current position: " << inFile.tellg() << "\n";
		int pos = cs * (r - 1) + c - 1;
		inFile.seekg(pos, ios_base::cur);
		//cout << "current position: " << inFile.tellg() << "\n";
		inFile.read(&num, sizeof(char));
		inFile.close();
		return num;
	}
}

void saveEvery4ByteToFile(string in, string out) {
	ifstream inFile;
	ofstream outFile;
	inFile.open(in, ios::binary);
	outFile.open(out, ios::binary);

	size_t size = 1;
	char* buffer = new char[size];
	if (!inFile.is_open() || !outFile.is_open()) {
		cout << "failed to open";
	}
	else {
		while (!inFile.eof()) {
			inFile.read(buffer, size * sizeof(char));
			inFile.seekg(3, ios_base::cur);
			outFile.write(buffer, size * sizeof(char));
			if (inFile.tellg() == -1) {
				break;
			}
		}
		outFile.close();
		inFile.close();
	}
	delete[] buffer;
}

int main(int argc, char** argv) {
	if (argc > 2) {
		cout << argc << endl;
		string in = argv[1];
		cout << in << endl;
		cout << "element at row " << 10 << " and column 2 is " << getElementByIndex(in, 10, 2) << endl;
	}
}