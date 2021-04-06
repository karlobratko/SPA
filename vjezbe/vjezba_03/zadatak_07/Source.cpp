#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <functional>

const std::string T_FILE_NAME{ "Broj_znanstvenika_na_milijun_stanovnika.csv" };
const std::string B_FILE_NAME{ "nazivi_drzava.dat" };
const std::size_t COL_COUNT{ 10 };

struct Country {
	char name[30];
	int sci_count[10];

	friend std::ostream& operator<<(std::ostream& os, const Country& c) {
		os << std::setw(30) << c.name << " ";
		for (std::size_t i{ 0 }; i < COL_COUNT; ++i)
			os << std::setw(6) << c.sci_count[i] << " ";
		return os;
	}
};
typedef Country* CountryPtr;
const Country COL{
	"COUNTRY NAME",
	{ 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014 }
};

template <typename F>
struct FinalAction {
	F clean_state;
	FinalAction(F f) : clean_state{ f } {}
	~FinalAction() { clean_state();	}
};

template <typename F>
FinalAction<F> Finally(F f) {
	return FinalAction<F>{ f };
}

std::size_t CountLinesInTextFile(std::fstream&, const std::string&);
CountryPtr AllocateArrayMemory(const std::size_t&);
void DeallocateArrayMemory(CountryPtr&);
void ReadDataFromTextFile(CountryPtr const, const std::size_t&, std::fstream&, const std::string&);
void WriteDataToConsole(const CountryPtr, const std::size_t&);
void WriteDataToBinaryFile(const CountryPtr, const std::size_t&, std::fstream&, const std::string&);
void ReadDataFromBinaryFile(CountryPtr const, const std::size_t&, std::fstream&, const std::string&);

int main() {
	std::fstream file{};
	auto act1 = Finally([&]() -> void { file.close(); });
	try {
		const std::size_t size{ CountLinesInTextFile(file, T_FILE_NAME) };
		CountryPtr arr{ AllocateArrayMemory(size) };
		auto act2 = Finally([&]() -> void { DeallocateArrayMemory(arr); });
		ReadDataFromTextFile(arr, size, file, T_FILE_NAME);
		WriteDataToBinaryFile(arr, size, file, B_FILE_NAME);
		
		CountryPtr new_arr{ AllocateArrayMemory(size) };
		auto act3 = Finally([&]() -> void { DeallocateArrayMemory(new_arr); });
		ReadDataFromBinaryFile(new_arr, size, file, "");
		WriteDataToConsole(new_arr, size);

	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}

std::size_t CountLinesInTextFile(std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::size_t size{
			static_cast<std::size_t>(
				std::count(
					std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>(),
					'\n'
				)
			)
		};
		file.close();
		return size - 1;
	}
	else 
		throw std::runtime_error("COUNTLINESINTEXTFILE::FSTREAM::IFSTREAM::unable to open file");
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
			for (std::size_t j{ 0 }; j < COL_COUNT; ++j) {
				std::getline(sstr, data, ';');
				arr[i].sci_count[j] = (data == "" ? 0 : std::stoi(data));
			}
		}
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMTEXTFILE::FSTREAM::IFSTREAM::unable to open file");
}

void WriteDataToConsole(const CountryPtr arr, const std::size_t& size) {
	std::cout << COL << std::endl;
	for (std::size_t i{ 0 }; i < size; ++i)
		std::cout << arr[i] << std::endl;
}

void WriteDataToBinaryFile(const CountryPtr arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(arr), sizeof(Country) * static_cast<__int64>(size));
		file.close();
	}
	else
		throw std::runtime_error("WRITEDATATOBINARYFILE::FSTREAM::OFSTREAM::unable to open file");
}

void ReadDataFromBinaryFile(CountryPtr const arr, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		file.read(reinterpret_cast<char*>(arr), sizeof(Country) * static_cast<__int64>(size));
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMBINARYFILE::FSTREAM::IFSTREAM::unable to open file");
}