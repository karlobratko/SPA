#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

const std::string I_FILE_NAME{ "Broj_znanstvenika_na_milijun_stanovnika.csv" };
const std::string O_FILE_NAME{ "nazivi_drzava.dat" };

typedef std::string* StringPtr;

std::size_t CountLinesInFile(std::fstream&, const std::string&);
StringPtr AllocateArrayMemory(const std::size_t&);
void DeallocateArrayMemory(StringPtr&);
void ReadDataFromTextFile(StringPtr const, const std::size_t&, std::fstream&, const std::string&);
void WriteDataToConsole(const StringPtr const, const std::size_t&);
void WriteDataToBinaryFile(const StringPtr const, const std::size_t&, std::fstream&, const std::string&);
void ReadDataFromBinaryFile(std::fstream&, const std::string&);


int main() {
	std::fstream file{};
	StringPtr arr{ nullptr };
	std::size_t size{};
	try {
		size = CountLinesInFile(file, I_FILE_NAME);
		arr = AllocateArrayMemory(size);
		ReadDataFromTextFile(arr, size, file, I_FILE_NAME);
		WriteDataToBinaryFile(arr, size, file, O_FILE_NAME);
		ReadDataFromBinaryFile(file, O_FILE_NAME);
	}
	catch (const std::runtime_error& err) {
		if (arr) DeallocateArrayMemory(arr);
		std::cerr << err.what() << std::endl;
		return 1;
	}
	DeallocateArrayMemory(arr);
	file.close();
	return 0;
}

std::size_t CountLinesInFile(std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::size_t r = static_cast<std::size_t>(
			std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n')
			);
		file.close();
		return r - 1;
	}
	else throw std::runtime_error("COUNTLINESINFILE::FSTREAM::IFSTREAM::file could not be open");
}

StringPtr AllocateArrayMemory(const std::size_t& size) {
	return new std::string[size]{};
}

void DeallocateArrayMemory(StringPtr& arr) {
	delete[] arr;
	arr = nullptr;
}

void ReadDataFromTextFile(StringPtr const arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::string line{};
		std::getline(file, line);
		std::stringstream sstr{};
		std::string data{};
		for (std::size_t i{ 0 }; i < size; ++i) {
			std::getline(file, line);
			sstr.str(line);
			std::getline(sstr, data, ';');
			arr[i] = data;
		}
		file.close();
	}
	else throw std::runtime_error("READDATAFROMTEXTFILE::FSTREAM::IFSTREAM::file could not be open");
}

void WriteDataToConsole(const StringPtr const arr, const std::size_t& size) {
	for (std::size_t i{ 0 }; i < size; ++i)
		std::cout << arr[i] << std::endl;
}

void WriteDataToBinaryFile(const StringPtr const arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		short str_len{};
		for (std::size_t i{ 0 }; i < size; ++i) {
			str_len = arr[i].size();
			file.write(reinterpret_cast<char*>(&str_len), sizeof(str_len));
			file.write(arr[i].c_str(), str_len);
		}
		file.close();
	}
	else throw std::runtime_error("WRITEDATATOBINARYFILE::FSTREAM::OFSTREAM::file could not be open");
}

void ReadDataFromBinaryFile(std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		short str_len{};
		std::string str{};
		while (true) {
			if (file.read(reinterpret_cast<char*>(&str_len), sizeof(str_len))) {
				char* c_str{ new char[str_len] };
				file.read(c_str, str_len);
				str.assign(c_str, str_len);
				delete[] c_str;
				std::cout << str << std::endl;
			}
			else break;
		}
		file.close();
	}
	else throw std::runtime_error("READDATAFROMBINARYFILE::FSTREAM::IFSTREAM::file could not be open");
}