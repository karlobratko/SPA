#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <stdexcept>

std::size_t CountSpacesInFile(const std::string& file_name) {
	std::ifstream file_reader{ file_name };
	if (!file_reader)
		throw std::runtime_error("COUNTLINESINFILE::IFSTREAM::RUNTIMEERROR::could not open file");

	std::size_t count{};
	std::string s{};
	while (file_reader >> s)
		++count;
	file_reader.close();

	return count;
}

void FileToArray(std::array<std::string, 250>& arr, std::string file_name) {
	std::ifstream file_reader{ file_name };
	if (!file_reader)
		throw std::runtime_error("FILETOARRAY::IFSTREAM::RUNTIMEERROR::could not open file");

	std::size_t i{ 0 };
	std::string s{};
	while (file_reader >> s)
		arr[i++] = s;
	file_reader.close();
}

int main() {
	std::string file_name{};
	std::cout << "file name: ";
	std::getline(std::cin, file_name);
	
	std::string word{};
	std::cout << "word: ";
	std::getline(std::cin, word);

	// std::size_t len = CountSpacesInFile(file_name);
	std::array<std::string, 250> arr{};
	try {
		FileToArray(arr, file_name);
	}
	catch (const std::exception& except) {
		std::cout << except.what() << std::endl;
	}

	// std::for_each(arr.begin(), arr.end(), [](const std::string& s) -> void { std::cout << s << std::endl; });

	std::cout << std::count(arr.begin(), arr.end(), word) << std::endl;

	std::cin.get();
}