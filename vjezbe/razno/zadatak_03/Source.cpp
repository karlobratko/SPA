#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

const char* file_name{ "array.txt" };

int main() {
	try {
		std::fstream file{ file_name, std::ios::in };
		if (file.is_open()) {
			std::vector<std::string> vec{};
			std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(), std::back_inserter(vec));
			int count = std::count(std::begin(vec), std::end(vec), std::string{ "the" });
			std::cout << "count: " << count << std::endl;
			file.close();
		}
		else
			throw std::exception{ "FSTREAM::IFSTREAM::could not access file" };
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}