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

void changeWidthHeight(string pathToBMP) {
	ifstream image;
	image.open(pathToBMP, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(14, ios::beg);    //bitmapinnfoheader is 14 bytes long
		char* biSize = new char[4];
		char* biWidth = new char[4];
		char* biHeight = new char[4];
		image.read(biSize, 4 * sizeof(char));
		image.read(biWidth, 4 * sizeof(char));
		image.read(biHeight, 4 * sizeof(char));
		//if biSize >= 40 => width and height take up 4 bytes each
		image.close();

		ofstream image2;
		image2.open(pathToBMP, ios::binary | ios::in | ios::out);
		if (!image2.is_open()) {
			cout << "failed to open";
		}
		else {
			image2.seekp(18, ios::beg);
			image2.write(biHeight, 4 * sizeof(char));
			image2.seekp(22, ios::beg);
			image2.write(biWidth, 4 * sizeof(char));
			image2.close();
		}
		delete[] biSize;
		delete[] biHeight;
		delete[] biWidth;
	}
}

void printWidthHeight(string pathToBMP) {
	ifstream image;
	image.open(pathToBMP, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(18, ios::beg);
		char* biWidth = new char[4];
		char* biHeight = new char[4];
		image.read(biWidth, 4 * sizeof(char));
		image.read(biHeight, 4 * sizeof(char));
		for (int i = 0; i < 4; i++) {
			printf("%02hhX", (unsigned char)biWidth[i]);
		}
		cout << endl;
		for (int i = 0; i < 4; i++) {
			printf("%02hhX", (unsigned char)biHeight[i]);
		}
		cout << endl;
		image.close();
		delete[] biHeight;
		delete[] biWidth;
	}
}

int main(int argc, char** argv) {
	if (argc >= 2) {
		string in = argv[1];
		cout << "element at row " << 10 << " and column 2 is " << getElementByIndex(in, 10, 2) << endl;
	}
	if (argc >= 3) {
		string pathToBMP = argv[2];
		printWidthHeight(pathToBMP);
		changeWidthHeight(pathToBMP);
		printWidthHeight(pathToBMP);
	}
}