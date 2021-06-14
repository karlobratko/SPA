#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <functional>
#include <iomanip>

const char* file_name{ "ip_adrese.txt" };

struct ip_t {
public:
	ip_t() {};
	ip_t(const ip_t& ip) : bytes{ ip.bytes } {}

	bool is_valid() const {
		return
			bytes.at(0) >= 1 && bytes.at(0) <= 255 &&
			bytes.at(1) >= 0 && bytes.at(1) <= 255 &&
			bytes.at(2) >= 0 && bytes.at(2) <= 255 &&
			bytes.at(3) >= 0 && bytes.at(3) <= 255;
	}

	char get_class() const {
		if (bytes.at(0) >= 1 && bytes.at(0) <= 126) return 'A';
		else if (bytes.at(0) >= 128 && bytes.at(0) <= 191) return 'B';
		else if (bytes.at(0) <= 223) return 'C';
		else if (bytes.at(0) <= 239) return 'D';
		else if (bytes.at(0) <= 254) return 'E';
	}

	friend std::istream& operator>>(std::istream& is, ip_t& ip) {
		std::string line{};
		std::getline(is, line);
		if (!is.eof()) {
			std::istringstream iss{ line };
			char delim{};
			iss
				>> ip.bytes.at(0) >> delim
				>> ip.bytes.at(1) >> delim
				>> ip.bytes.at(2) >> delim
				>> ip.bytes.at(3);
			if (iss.fail() || !ip.is_valid()) is.setstate(std::ios::failbit);
		}
		else is.setstate(std::ios::eofbit);
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const ip_t& ip) {
		std::ostringstream oss{};
		oss
			<< ip.bytes.at(0) << "."
			<< ip.bytes.at(1) << "."
			<< ip.bytes.at(2) << "."
			<< ip.bytes.at(3);
		if (!oss) os.setstate(os.rdstate());
		else os << oss.str();
		return os;
	}

private:
	std::array<int, 4> bytes{};

};

class file_t {
public:
	explicit file_t(const char* file_name, std::ios_base::openmode open_mode) :
		file_{ file_name, open_mode } {
		if (!file_.is_open())
			throw std::runtime_error("FSTREAM::IFSTREAM::could not access file");
	}
	file_t(const file_t&) = delete;
	file_t(file_t&& other) noexcept : file_{ std::move(other.file_) } {}
	file_t& operator=(const file_t&) = delete;
	file_t& operator=(file_t&& other) noexcept {
		file_ = std::move(other.file_);
		return *this;
	}
	~file_t() {
		file_.close();
	}
	std::fstream* operator->() {
		return &file_;
	}
	std::fstream& operator*() {
		return file_;
	}

private:
	std::fstream file_{};
};

void ReadDataFromTextFile(file_t file, std::vector<ip_t>& vec) {
	std::copy(std::istream_iterator<ip_t>(*file), std::istream_iterator<ip_t>(), std::back_inserter(vec));
}

void WriteDataToConsole(std::vector<ip_t> vec) {
	std::cout << "IP ADDRESSES:" << std::endl;
	std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<ip_t>(std::cout, "\n"));
	std::cout << std::endl;
}

void CountByClass(std::map<char, unsigned>& map, std::vector<ip_t>& vec) {
	std::for_each(
		std::begin(vec),
		std::end(vec),
		[&map](ip_t& ip) -> void {
			++map.at(ip.get_class());
		}
	);
}

namespace std {
	std::ostream& operator<<(std::ostream& os, const std::pair<char, unsigned>& pair) {
		std::ostringstream oss{};
		std::string str(pair.second, '#');
		oss << "CLASS " << pair.first << ": " << str << " (" << pair.second << ")";
		if (!oss) os.setstate(std::ios::failbit);
		else os << oss.str();
		return os;
	}
}

void PrintByClass(std::map<char, unsigned>& map) {
	std::cout << "COUNT BY CLASS:" << std::endl;
	std::copy(std::begin(map), std::end(map), std::ostream_iterator<std::pair<char, unsigned>>(std::cout, "\n"));
}

int main() {
	try {
		std::vector<ip_t> ips{};
		ReadDataFromTextFile(file_t{ file_name, std::ios::in }, ips);
		WriteDataToConsole(ips);

		std::map<char, unsigned> class_count{
			{ 'A', 0 },
			{ 'B', 0 },
			{ 'C', 0 },
			{ 'D', 0 },
			{ 'E', 0 }
		};
		CountByClass(class_count, ips);
		PrintByClass(class_count);
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}


	return 0;
}