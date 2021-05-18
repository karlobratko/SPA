#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <numeric>
#include <functional>

const char* file_name_I{ "scientists.csv"			};
const char* file_name_O{ "scientists_bin.dat" };

class file_except_t : public std::exception {
public:
	file_except_t() noexcept		= default;
	~file_except_t()						= default;
	virtual const char* what() const noexcept {
		return "FSTREAM::could not access file";
	}
};

class country_t {
public:
	country_t() {}
	country_t(const country_t& country) {
		std::copy(std::begin(country.name_), std::end(country.name_), std::begin(name_));
		std::copy(std::begin(country.sci_count_), std::end(country.sci_count_), std::begin(sci_count_));
	}
	int accumulateScientists() const {
		return std::accumulate(std::begin(sci_count_), std::end(sci_count_), 0);
	}
	friend std::istream& operator>>(std::istream& is, country_t& country) {
		std::string line{};
		std::getline(is, line);
		if (!is.eof()) {
			std::istringstream iss{ line };
			iss.getline(country.name_, 30, ';');
			std::string temp{};
			for (std::size_t i{ 0 }; i < 10; ++i) {
				std::getline(iss, temp, ';');
				country.sci_count_[i] = (temp == "" ? 0 : std::stoi(temp));
			}
			if (iss.fail()) is.setstate(iss.rdstate());
		}
		else is.setstate(std::ios::eofbit);
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const country_t& country) {
		std::ostringstream oss{};
		oss
			<< std::left	<< std::setw(30)	<< country.name_ << "|"
			<< std::right << std::setw(20)	<< country.accumulateScientists();
		if (!oss) os.setstate(oss.rdstate());
		else os << oss.str();
		return os;
	}
	bool operator<(const country_t& country) const {
		return accumulateScientists() < country.accumulateScientists();
	}
	static bool hasScientists(country_t& country) {
		return country.accumulateScientists();
	}

private:
	char name_[30]{};
	unsigned sci_count_[10]{};
};

void ReadDataFromTextFile(std::fstream& file, std::vector<country_t>& vec) {
	file.open(file_name_I, std::ios::in);
	if (file.is_open()) {
		{ std::string temp{};
		std::getline(file, temp);
		}
		std::copy(std::istream_iterator<country_t>(file), std::istream_iterator<country_t>(), std::back_inserter(vec));
		file.close();
	}
	else throw file_except_t{};
}

void WriteDataToBinaryFile(std::fstream& file, std::vector<country_t>& vec) {
	file.open(file_name_O, std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(vec.data()), sizeof(country_t) * static_cast<__int64>(vec.size()));
		file.close();
	}
	else throw file_except_t{};
}

void ReadDataFromBinaryFile(std::fstream& file, std::vector<country_t>& vec) {
	file.open(file_name_O, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		{ file.seekg(0, std::ios::end);
			vec.resize(static_cast<int>(file.tellg()) / sizeof(country_t));
			file.seekg(0, std::ios::beg);
		}
		file.read(reinterpret_cast<char*>(vec.data()), sizeof(country_t) * static_cast<__int64>(vec.size()));
		file.close();
	}
	else throw file_except_t{};
}

void CopyDataByPredicate(std::vector<country_t>& vec_from, std::set<country_t>& set_to, std::function<bool(country_t&)> predicate) {
	std::copy_if(std::begin(vec_from), std::end(vec_from), std::inserter(set_to, std::begin(set_to)), predicate);
}

void WriteHeaderToConsole() {
	std::cout
		<< std::left	<< std::setw(30) << "COUNTRY NAME"			<< "|"
		<< std::right << std::setw(20) << "SCIENTISTS COUNT"	<< std::endl;
}

template <typename _Ctr, typename _Ty>
void WriteDataToConsole(_Ctr& countries) {
	WriteHeaderToConsole();
	std::copy(std::begin(countries), std::end(countries), std::ostream_iterator<_Ty>(std::cout, "\n"));
	std::cout << std::endl;
}

int main() {
	try	{
		std::fstream file{};

		std::vector<country_t> countries{};
		ReadDataFromTextFile(file, countries);
		WriteDataToBinaryFile(file, countries);

		std::vector<country_t> new_countries{};
		ReadDataFromBinaryFile(file, new_countries);
		//WriteDataToConsole<std::vector<country_t>, country_t>(new_countries);

		std::set<country_t> sci_countries{};
		CopyDataByPredicate(new_countries, sci_countries, country_t::hasScientists);
		WriteDataToConsole<std::set<country_t>, country_t>(sci_countries);
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}