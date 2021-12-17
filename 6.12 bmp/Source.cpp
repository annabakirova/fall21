#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

void printBiBitCount(string pathToBMP) {
	ifstream image;
	image.open(pathToBMP, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(28, ios::beg);
		char* biBitCount = new char[2];
		image.read(biBitCount, 2 * sizeof(char));
		for (int i = 0; i < 2; i++) {
			printf("%02hhX", (unsigned char)biBitCount[i]);
		}
		cout << endl;
		image.close();
		delete[] biBitCount;
	}
}

void printWidthHeight2(string pathToBMP) {
	ifstream image;
	image.open(pathToBMP, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(18, ios::beg);
		int biWidth;
		int biHeight;
		image.read((char*)&biWidth, sizeof(int));
		image.read((char*)&biHeight, sizeof(int));
		cout << biWidth << endl;
		cout << biHeight << endl;
		image.close();
	}
}

int getBfOffBits(string pathToBMP) {
	ifstream image;
	image.open(pathToBMP, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(10, ios::beg);
		int bfOffBits;
		image.read((char*)&bfOffBits, sizeof(int));
		image.close();
		return bfOffBits;
	}
}

void copyChangedFile(string in, string out) {
	ifstream inFile;
	ofstream outFile;
	inFile.open(in, ios::binary);
	outFile.open(out, ios::binary);

	size_t size = 32;
	char* buffer = new char[size];
	if (!inFile.is_open() || !outFile.is_open()) {
		cout << "failed to open";
	}
	else {

		inFile.read(buffer, 18 * sizeof(char));
		outFile.write(buffer, 18 * sizeof(char));
		outFile.flush();

		inFile.seekg(4, ios_base::cur);
		inFile.read(buffer, sizeof(int));
		outFile.write(buffer, sizeof(int));
		outFile.flush();

		inFile.seekg(-8, ios_base::cur);
		inFile.read(buffer, sizeof(int));
		outFile.write(buffer, sizeof(int));
		outFile.flush();

		inFile.seekg(4, ios_base::cur);
		while (!inFile.eof()) {
			inFile.read(buffer, sizeof(int));
			outFile.write(buffer, sizeof(int));
			outFile.flush();
		}

		outFile.close();
		inFile.close();
	}
	delete[] buffer;
}

void print8BitPixelArray(string path) {
	int start = getBfOffBits(path);
	ifstream image;
	image.open(path, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(18, ios::beg);
		int width;
		int widthInBytes;
		image.read((char*)&width, sizeof(int));
		image.seekg(0, ios::beg);
		if (width % 32 != 0) {
			width = width + 32 - (width % 32);
		}
		cout << "new width: " << width << endl;
		widthInBytes = width / 8;
		unsigned char* buffer = new unsigned char[widthInBytes];
		image.seekg(start, ios::beg);
		int count = 0;
		while (image.tellg() != -1) {
			image.read((char*)buffer, widthInBytes * sizeof(char));
			for (int i = 0; i < widthInBytes; i++) {
				unsigned char mask = 0x80;
				for (int j = 0; j < 8; mask >>= 1, j++) {
					string out = ((buffer[i] & mask) == 0) ? " " : "x";
					cout << out;
					count++;
				}
			}
			if (count % width == 0) {
				cout << endl;
			}
		}
		delete[] buffer;
		image.close();
	}
}

void print24BitPixelArray(string path) {
	int start = getBfOffBits(path);
	ifstream image;
	image.open(path, ios::binary | ios::in);
	if (!image.is_open()) {
		cout << "failed to open";
	}
	else {
		image.seekg(18, ios::beg);
		int width;
		image.read((char*)&width, sizeof(int));
		image.seekg(start, ios::beg);
		if (width % 32 != 0) {
			width = width + 32 - (width % 32);
		}
		cout << "new width: " << width << endl;
		unsigned char* buffer = new unsigned char[3];
		int count = 0;
		while (image.tellg() != -1) {
			image.read((char*)buffer, 3 * sizeof(char));
			cout << (int)buffer[0] << " " << (int)buffer[1] << " " << (int)buffer[2] << " ";
			count++;
			if (count % width == 0) {
				cout << endl;
			}
		}
		delete[] buffer;
		image.close();
	}
}

void changeRedBlue24Bit(string path, string path2) {
	int start = getBfOffBits(path);
	ifstream image;
	ofstream image2;
	image.open(path, ios::binary | ios::in | ios::out);
	image2.open(path2, ios::binary | ios::in | ios::out | ios::trunc);
	if (!image.is_open() && !image2.is_open()) {
		cout << "failed to open";
	}
	else {
		unsigned char* buffer = new unsigned char[start];
		image.read((char*)buffer, start * sizeof(char));
		image2.write((char*)buffer, start * sizeof(char));
		buffer = new unsigned char[3];
		while (image.tellg() != -1) {
			image.read((char*)buffer, 3 * sizeof(char));
			image2.write((char*)&buffer[2], sizeof(char));
			image2.write((char*)&buffer[1], sizeof(char));
			image2.write((char*)&buffer[0], sizeof(char));
			image2.flush();
		}
		delete[] buffer;
		image.close();
		image2.close();
	}
}

void insert8BitBMP(string pathToSmall, string pathToBig) {
	ifstream image1;
	ifstream image2;
	image1.open(pathToSmall, ios::binary | ios::in);
	image2.open(pathToBig, ios::binary | ios::in);
	if (!image1.is_open() || !image2.is_open()) {
		cout << "failed to open";
	}
	else {
		unsigned int width1 = 0;
		unsigned int height1 = 0;
		image1.seekg(18, ios::beg);
		image1.read((char*)&width1, sizeof(int));
		image1.read((char*)&height1, sizeof(int));
		int oldWidth = width1;
		if (width1 % 32 != 0) {
			width1 = width1 + 32 - (width1 % 32);
		}
		unsigned int width2 = 0;
		unsigned int height2 = 0;
		image2.seekg(18, ios::beg);
		image2.read((char*)&width2, sizeof(int));
		image2.read((char*)&height2, sizeof(int));
		if (width2 % 32 != 0) {
			width2 = width2 + 32 - (width2 % 32);
		}
		cout << width1 << " " << height1 << endl;
		cout << width2 << " " << height2 << endl;
		image2.close();

		ofstream image2;
		image2.open(pathToBig, ios::binary | ios::in | ios::out);
		if (!image2.is_open()) {
			cout << "failed to open";
			return;
		}
		int sizeInBytes = oldWidth / 8;
		int sizeInBytes1 = width1 / 8;
		int sizeInBytes2 = width2 / 8;
		char* buffer = new char[sizeInBytes];
		for (int i = 1; i < height1; i++) {
			image1.seekg((-1) * sizeInBytes1 * i, ios::end);
			image1.read(buffer, sizeInBytes * sizeof(char));
			image2.seekp((-1) * sizeInBytes2 * i, ios::end);
			image2.write(buffer, sizeInBytes * sizeof(char));
		}

		delete[] buffer;
		image1.close();
		image2.close();
	}
}

void insert24BitBMP(string pathToSmall, string pathToBig) {
	ifstream image1;
	ifstream image2;
	image1.open(pathToSmall, ios::binary | ios::in);
	image2.open(pathToBig, ios::binary | ios::in);
	if (!image1.is_open() || !image2.is_open()) {
		cout << "failed to open";
	}
	else {
		unsigned int width1 = 0;
		unsigned int height1 = 0;
		image1.seekg(18, ios::beg);
		image1.read((char*)&width1, sizeof(int));
		image1.read((char*)&height1, sizeof(int));
		int oldWidth = width1;
		/*if (width1 % 32 != 0) {
			width1 = width1 + 32 - (width1 % 32);
		}*/
		unsigned int width2 = 0;
		unsigned int height2 = 0;
		image2.seekg(18, ios::beg);
		image2.read((char*)&width2, sizeof(int));
		image2.read((char*)&height2, sizeof(int));
		/*if (width2 % 32 != 0) {
			width2 = width2 + 32 - (width2 % 32);
		}*/
		cout << width1 << " " << height1 << endl;
		cout << width2 << " " << height2 << endl;
		image2.close();


		ofstream image2;
		image2.open(pathToBig, ios::binary | ios::in | ios::out);
		if (!image2.is_open()) {
			cout << "failed to open";
			return;
		}
		int sizeInBytes = oldWidth * 3;
		int sizeInBytes1 = width1 * 3;
		int sizeInBytes2 = width2 * 3;
		char* buffer = new char[sizeInBytes1];
		for (int i = 1; i < height1; i++) {
			image1.seekg((-1) * sizeInBytes1 * i, ios::end);
			image1.read(buffer, sizeInBytes1 * sizeof(char));
			image2.seekp((-1) * sizeInBytes2 * i, ios::end);
			image2.write(buffer, sizeInBytes1 * sizeof(char));
		}

		delete[] buffer;
		image1.close();
		image2.close();
	}
}

int main(int argc, char** argv) {
	if (argc >= 3) {
		string small = argv[1];
		string big = argv[2];
		print8BitPixelArray(big);
		insertBMP(small, big);
		print8BitPixelArray(big);

		//printWidthHeight2(small);
		//printWidthHeight2(big);

		//changeRedBlue24Bit("red.bmp", "red1.bmp");
		//changeRedBlue24Bit("blue.bmp", "blue1.bmp");
		//changeRedBlue24Bit("green.bmp", "green1.bmp");

		//print24BitPixelArray("red.bmp");
		//print24BitPixelArray("blue.bmp");
		//print24BitPixelArray("green.bmp");

		//print8BitPixelArray("e0000.bmp");
		//print8BitPixelArray("e000.bmp");
		//print8BitPixelArray("e00.bmp");
	}
}