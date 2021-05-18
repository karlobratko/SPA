#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

const char* file_name_I{ "LakeHuron.csv" };
const char* file_name_O{ "data.dat" };

class file_except_t : public std::exception {
public:
	file_except_t() noexcept = default;
	~file_except_t() = default;
	virtual const char* what() const noexcept {
		return "FSTREAM::could not access file";
	}
};

class lake_t {
public:
	lake_t() : 
		year_		{ 0 }, 
		height_	{ 0 } {
	}
	lake_t(const lake_t& lake) :
		year_		{ lake.year_		},
		height_	{ lake.height_	} {
	}
	friend std::istream& operator>>(std::istream& is, lake_t& lake) {
		std::string line{};
		std::getline(is, line);
		if (!is.eof()) {
			std::string temp{};
			std::istringstream iss{ line };
			std::getline(iss, temp, ',');
			std::getline(iss, temp, ',');
			lake.year_ = std::stoi(temp);
			std::getline(iss, temp);
			lake.height_ = std::stod(temp);
			if (iss.fail()) is.setstate(iss.rdstate());
		}
		else is.setstate(std::ios::eofbit);
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const lake_t& lake) {
		std::ostringstream oss{};
		oss
			<< std::left
			<< std::setw(4) << lake.year_ << " "
			<< std::setw(8) << lake.height_;
		if (oss.fail()) os.setstate(oss.rdstate());
		else os << oss.str();
		return os;
	}
	bool operator==(const lake_t& lake) const {
		return year_ == lake.year_;
	}
	bool operator==(int year) const {
		return year_ == year;
	}

private:
	int year_;
	double height_;
};

int ReadYearFromConsole() {
	int year;
	std::cout << "enter year: ";
	std::cin >> year;
	std::cin.ignore();
	std::cout << std::endl;
	return year;
}

void WriteDataToConsole(std::vector<lake_t>::iterator begin, std::vector<lake_t>::iterator end) {
	std::copy(begin, end, std::ostream_iterator<lake_t>(std::cout, "\n"));
	std::cout << std::endl;
}

std::vector<lake_t>::iterator FindLakeByYear(std::vector<lake_t>& lakes, int year) {
	return std::find(std::begin(lakes), std::end(lakes), year);
}

int main() {
	try {
		std::fstream file{};
		std::vector<lake_t> lakes{};

		// read - .txt file
		file.open(file_name_I, std::ios::in);
		if (file.is_open()) {
			{	std::string temp{};
				std::getline(file, temp);
			}
			std::copy(std::istream_iterator<lake_t>(file), std::istream_iterator<lake_t>(), std::back_inserter(lakes));
			file.close();
		}
		else throw file_except_t{};
		
		// write - .dat file
		file.open(file_name_O, std::ios::binary | std::ios::out);
		if (file.is_open()) {
			file.write(reinterpret_cast<char*>(lakes.data()), sizeof(lake_t) * static_cast<__int64>(lakes.size()));
			file.close();
		}
		else throw file_except_t{};

		std::vector<lake_t> newlakes{};

		// read - .dat file
		file.open(file_name_O, std::ios::binary | std::ios::in);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			newlakes.resize(file.tellg() / sizeof(lake_t));
			file.seekg(0, std::ios::beg);
			file.read(reinterpret_cast<char*>(newlakes.data()), sizeof(lake_t) * static_cast<__int64>(newlakes.size()));
			file.close();
		}
		else throw file_except_t{};
	
		std::vector<lake_t>::iterator it1 = FindLakeByYear(newlakes, ReadYearFromConsole());
		std::advance(it1, 1);
		WriteDataToConsole(std::begin(newlakes), it1);
		
		std::vector<lake_t>::iterator it2 = FindLakeByYear(newlakes, ReadYearFromConsole());
		std::advance(it2, 1);
		newlakes.erase(std::begin(newlakes), it2);
		WriteDataToConsole(std::begin(newlakes), std::end(newlakes));
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}
	return 0;
}