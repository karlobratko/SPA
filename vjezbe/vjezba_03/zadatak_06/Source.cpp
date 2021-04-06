#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

const std::string T_FILE_NAME{ "Broj_znanstvenika_na_milijun_stanovnika.csv" };
const std::string B_FILE_NAME{ "nazivi_drzava.dat" };
const std::size_t COL_YEARS_COUNT{ 10 };

struct Country {
	char name[30];
	int sci_count[10];

	friend std::ostream& operator<<(std::ostream& os, const Country& c) {
		os << std::setw(30) << c.name << " ";
		for (std::size_t j{ 0 }; j < COL_YEARS_COUNT; ++j)
			os << std::setw(6) << c.sci_count[j] << " ";
		return os;
	}
};
const Country COL{
	"NAZIV",
	{ 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014 }
};

template <typename F>
struct FinalAction {
	F clean_state;
	FinalAction(F f) : clean_state{ f } {}
	~FinalAction() { clean_state(); }
};

template <typename F>
FinalAction<F> Finally(F f) {
	return FinalAction<F>{ f };
}

std::size_t CountLinesInTextFile(std::fstream&, const std::string&);
void ReadDataFromTextFile(std::vector<Country>&, std::fstream&, const std::string&);
void WriteDataToConsole(std::vector<Country>&);
void WriteDataToBinaryFile(std::vector<Country>&, std::fstream&, const std::string&);
void ReadDataFromBinaryFile(std::vector<Country>&, std::fstream&, const std::string&);

int main() {
	std::fstream file{};

	try {
		const std::size_t size{ CountLinesInTextFile(file, T_FILE_NAME) };
		std::vector<Country> c{ size };
		ReadDataFromTextFile(c, file, T_FILE_NAME);
		WriteDataToBinaryFile(c, file, B_FILE_NAME);

		try {
			std::vector<Country> nc{ size };
			ReadDataFromBinaryFile(nc, file, B_FILE_NAME);
			WriteDataToConsole(nc);
		}
		catch (const std::runtime_error& err) {
			std::cerr << err.what() << std::endl;
			return 2;
		}
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	file.close();
	return 0;
}

std::size_t CountLinesInTextFile(std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::size_t count{
			static_cast<std::size_t>(
				std::count(
					std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>(),
					'\n'
				)
			)
		};
		file.close();
		return count - 1;
	}
	else throw std::runtime_error("COUNTLINESINTEXTFILE::FSTREAM::IFSTREAM::unable to open file");
}

void ReadDataFromTextFile(std::vector<Country>& vec, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::string line{};
		std::getline(file, line);
		std::stringstream sstr{};
		std::string data{};
		for (std::size_t i{ 0 }; i < vec.size(); ++i) {
			std::getline(file, line);
			sstr.str(line);
			std::getline(sstr, data, ';');
			std::copy(data.begin(), data.end(), vec[i].name);
			for (std::size_t j{ 0 }; j < COL_YEARS_COUNT; ++j) {
				std::getline(sstr, data, ';');
				vec[i].sci_count[j] = (data == "" ? 0 : std::stoi(data));
			}
		}
		file.close();
	}
	else throw std::runtime_error("READDATAFROMTEXTFILE::FSTREAM::IFSTREAM::unable to open file");
}

void WriteDataToConsole(std::vector<Country>& vec) {
	std::cout << COL << std::endl;
	std::for_each(
		vec.begin(),
		vec.end(),
		[](const auto& c) {
			std::cout << c << std::endl;
		}
	);
}

void WriteDataToBinaryFile(std::vector<Country>& vec, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(vec.data()), sizeof(Country) * static_cast<__int64>(vec.size()));
		file.close();
	}
	else throw std::runtime_error("WRITEDATATOBINARYFILE::FSTREAM::OFSTREAM::unable to open file");
}

void ReadDataFromBinaryFile(std::vector<Country>& vec, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		file.read(reinterpret_cast<char*>(vec.data()), sizeof(Country) * static_cast<__int64>(vec.size()));
		file.close();
	}
	else throw std::runtime_error("READDATAFROMBINARYFILE::FSTREAM::IFSTREAM::unable to open file");
}