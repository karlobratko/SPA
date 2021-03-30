#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

const std::string T_FILE_NAME{ "Broj_znanstvenika_na_milijun_stanovnika.csv" };
const std::string B_FILE_NAME{ "nazivi_drzava.dat" };
const std::size_t COL_YEARS_COUNT{ 10 };
const std::size_t COL_YEARS[COL_YEARS_COUNT]{ 
	2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014 
};

struct Country {
	char name[30];
	int sci_per_year[10];
};
typedef Country* CountryPtr;

std::size_t CountLinesInTextFile(std::fstream&, const std::string&);
CountryPtr AllocateArrayMemory(const std::size_t&);
void DeallocateArrayMemory(CountryPtr&);
void ReadDataFromTextFile(CountryPtr const, const std::size_t&, std::fstream&, const std::string&);
void WriteDataToConsole(const CountryPtr, const std::size_t&);
void WriteDataToBinaryFile(const CountryPtr, const std::size_t&, std::fstream&, const std::string&);
void ReadDataFromBinaryFile(CountryPtr const, const std::size_t&, std::fstream&, const std::string&);
void PrintCountriesWithNoScientists(const CountryPtr, const std::size_t&);

int main() {
	std::fstream file{};
	CountryPtr arr{ nullptr };
	try {
		const std::size_t size = CountLinesInTextFile(file, T_FILE_NAME);
		arr = AllocateArrayMemory(size);
		ReadDataFromTextFile(arr, size, file, T_FILE_NAME);
		WriteDataToBinaryFile(arr, size, file, B_FILE_NAME);
		DeallocateArrayMemory(arr);

		CountryPtr new_arr{ nullptr };
		try {
			new_arr = AllocateArrayMemory(size);
			ReadDataFromBinaryFile(new_arr, size, file, B_FILE_NAME);
			// WriteDataToConsole(new_arr, size);
			PrintCountriesWithNoScientists(new_arr, size);
			DeallocateArrayMemory(new_arr);
		}
		catch (const std::runtime_error& err) {
			if (new_arr) DeallocateArrayMemory(new_arr);
			std::cerr << err.what() << std::endl;
			return 2;
		}
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

std::size_t CountLinesInTextFile(std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::size_t r{
			static_cast<std::size_t>(
				std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n')	
			)
		};
		file.close();
		return r - 1;
	}
	else
		throw std::runtime_error("COUNTLINESINTEXTFILE::FSTREAM::IFSTREAM::file could not be open");
}

CountryPtr AllocateArrayMemory(const std::size_t& size) {
	return new Country[size]{};
}

void DeallocateArrayMemory(CountryPtr& arr) {
	delete[] arr;
	arr = nullptr;
}

void ReadDataFromTextFile(CountryPtr const arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
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
			std::copy(data.begin(), data.end(), arr[i].name);
			for (std::size_t j{ 0 }; j < COL_YEARS_COUNT; ++j) {
				std::getline(sstr, data, ';');
				arr[i].sci_per_year[j] = (data == "" ? 0 : std::stoi(data));
			}
		}
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMTEXTFILE::FSTREAM::IFSTREAM::file could not be open");
}

void WriteDataToConsole(const CountryPtr arr, const std::size_t& size) {
	for (std::size_t i{ 0 }; i < size; ++i) {
		std::cout << arr[i].name << " ";
		for (std::size_t j{ 0 }; j < COL_YEARS_COUNT; ++j)
			std::cout << arr[i].sci_per_year[j] << " ";
		std::cout << std::endl;
	}
}

void WriteDataToBinaryFile(const CountryPtr arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(arr), sizeof(Country) * static_cast<__int64>(size));
		file.close();
	}
	else throw std::runtime_error("WRITEDATATOBINARYFILE::FSTREAM::OFSTREAM::file could not be open");
}

void ReadDataFromBinaryFile(CountryPtr const arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		file.read(reinterpret_cast<char*>(arr), sizeof(Country) * static_cast<__int64>(size));
		file.close();
	}
	else throw std::runtime_error("READDATATOBINARYFILE::FSTREAM::IFSTREAM::file could not be open");
}

void PrintCountriesWithNoScientists(const CountryPtr arr, const std::size_t& size) {
	bool no_scientists{};
	for (std::size_t i{ 0 }; i < size; ++i) {
		no_scientists = true;
		for (std::size_t j{ 0 }; j < COL_YEARS_COUNT; ++j)
			if (arr[i].sci_per_year[j] != 0) no_scientists = false;
		if (no_scientists) std::cout << arr[i].name << std::endl;
	}
}