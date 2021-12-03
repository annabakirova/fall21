#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool testCopyFile(string in, string out) {
	string sample = "12\r\n34\r\n";
	int size = 2; //8 bytes
	ifstream inFile;
	ofstream outFile;
	inFile.open("1.txt", ios::binary);
	outFile.open("2.txt", ios::binary);
}

int main(int argc, char** argv) {
	string in;
	string out;
	if (argc > 0) {
		in = argv[1];
		out = argv[2];
	}
	ifstream inFile;
	ofstream outFile;
	inFile.open(in, ios::binary);
	outFile.open(out, ios::binary);

	/*string line;
	if (myFile1.is_open() && myFile.is_open()) {
		while (getline(myFile1, line)) {
			myFile << line;
		}
		myFile.close();
		myFile1.close();
	}
	else {
		cout << "failed to open";
	}*/


	size_t size = 1;
	size_t counter = 0;
	int r = 1;
	int c = 0;

	char* buffer = new char[size];
	if (inFile.is_open() && outFile.is_open()) {
		while (!inFile.eof()) {
			//cout << inFile.tellg();
			inFile.read(buffer, size * sizeof(char));
			//cout << inFile.gcount() << " ";
			counter += size * sizeof(char);
			inFile.seekg(3, ios_base::cur);
			//cout << inFile.tellg();
			outFile.write(buffer, size * sizeof(char));
			
			if (inFile.tellg() == -1) {
				break;
			}
		}
		outFile.close();
		inFile.close();
	}
	else {
		cout << "failed to open";
	}

	delete[] buffer;

}