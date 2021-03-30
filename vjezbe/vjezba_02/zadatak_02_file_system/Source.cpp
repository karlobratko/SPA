#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>

void ReadFile(std::string file_name) {
	std::ifstream file_reader{ file_name };
	if (!file_reader)
		throw std::runtime_error("READFILE::IFSTREAM::could not open file");
	std::string line;
	while (std::getline(file_reader, line))
		std::cout << line << std::endl;
	file_reader.close();
}

int main() {
	std::string file_name{};
	std::cout << "file name: ";
	std::getline(std::cin, file_name);
	try {
		ReadFile(file_name);
	}
	catch (std::runtime_error except) {
		std::cout << except.what() << std::endl;
	}

	std::cin.get();
}