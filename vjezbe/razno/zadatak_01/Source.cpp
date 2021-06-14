#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

const char* file_name{ "data.txt" };

int main() {
	try {
		std::ifstream file{ file_name };
		if (file.is_open()) {
			//file.seekg(3);
			std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(std::cout));
			std::cout << std::endl;
			file.close();
		}
		else
			throw std::exception{ "FSTREAM::IFSTREAM::could not open file" };
	}
	catch (const std::exception& err){
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}