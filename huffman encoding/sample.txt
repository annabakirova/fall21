#include <fstream>
#include "huffman.h"

int main() {
	std::string path = "sample.txt";
	std::ifstream in;
	in.open(path, std::ios::in);
	if (!in.is_open()) {
		std::cout << "failed to open\n";
	}
	else {
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		std::string buffer(size, ' ');
		in.seekg(0);
		in.read(&buffer[0], size);
		HuffmanTree t{};
		t.encode(buffer);
	}
	return 0;
}