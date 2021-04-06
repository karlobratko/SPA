#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

const char* file_name_I{ "ip_adrese.txt" };
const char* file_name_O{ "data.dat" };

struct IPAddress {
	int x_, y_, z_, w_;
	IPAddress(int x = 0, int y = 0, int z = 0, int w = 0)
		: x_{ x }, y_{ y }, z_{ z }, w_{ w } {};
	friend std::ostream& operator<<(std::ostream& os, const IPAddress& ip) {
		os << ip.x_ << "." << ip.y_ << "." << ip.z_ << "." << ip.w_;
		return os;
	}
};

std::size_t CountLinesInTextFile(const char*&);
std::vector<IPAddress> InitializeVector(const std::size_t);
void ReadDataFromTextFile(const char*&, std::vector<IPAddress>&);
void WriteDataToConsole(const std::vector<IPAddress>&);
void WriteDataToBinaryFile(const char*&, std::vector<IPAddress>&);
std::vector<IPAddress> ReadDataFromBinaryFile(const char*&);

template <typename F>
std::vector<IPAddress> FilterVector(F predicate, std::vector<IPAddress>& vec) {
	std::vector<IPAddress> res{};
	res.reserve(vec.size());
	std::copy_if(
		vec.begin(),
		vec.end(),
		std::back_inserter(res),
		predicate
	);
	return res;
}

int main() {
	try {
		const std::size_t size{ CountLinesInTextFile(file_name_I) };
		std::vector<IPAddress> vec{ InitializeVector(size) };
		ReadDataFromTextFile(file_name_I, vec);
		WriteDataToBinaryFile(file_name_O, vec);

		try {
			std::vector<IPAddress> new_vec{ ReadDataFromBinaryFile(file_name_O) };
			std::vector<IPAddress> filtered_vec{ 
				FilterVector(
					[](const IPAddress& ip) {
						return ip.x_ >= 192 && ip.x_ <= 223;
					}, 
					new_vec
				) 
			};
			WriteDataToConsole(filtered_vec);
		}
		catch (const std::exception& err) {
			std::cerr << err.what() << std::endl;
			return 2;
		}
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}

std::size_t CountLinesInTextFile(const char*& file_name) {
	std::ifstream file{ file_name };
	if (file.is_open()) {
		std::size_t res{
			static_cast<std::size_t>(
				std::count(
					std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>(),
					'\n'
				)	
			)
		};
		file.close();
		return res;
	}
	else
		throw std::runtime_error("COUNTLINESINTEXTFILE::IFSTREAM::could not open file");
}

std::vector<IPAddress> InitializeVector(const std::size_t size) {
	std::vector<IPAddress> vec{};
	vec.reserve(size);
	return vec;
}

void ReadDataFromTextFile(const char*& file_name, std::vector<IPAddress>& vec) {
	std::ifstream file{ file_name };
	if (file.is_open()) {
		std::string line{};
		std::stringstream sstr{};
		std::string data{};
		int x{}, y{}, z{}, w{};
		for (std::size_t i{ 0 }; i < vec.capacity(); ++i) {
			std::getline(file, line);
			sstr.str(line);
			{
				std::getline(sstr, data, '.');
				x = std::stoi(data);
				std::getline(sstr, data, '.');
				y = std::stoi(data);
				std::getline(sstr, data, '.');
				z = std::stoi(data);
				std::getline(sstr, data);
				w = std::stoi(data);
			}
			vec.emplace_back(x, y, z, w);
			sstr.clear();
		}
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMTEXTFILE::IFSTREAM::could not open file");
}

void WriteDataToConsole(const std::vector<IPAddress>& vec) {
	std::for_each(
		vec.begin(),
		vec.end(),
		[](const IPAddress& ip) -> void {
			std::cout << ip << std::endl;
		}
	);
}

void WriteDataToBinaryFile(const char*& file_name, std::vector<IPAddress>& vec) {
	std::ofstream file{ file_name, std::ios::binary };
	if (file.is_open()) {
		unsigned size{ vec.size() };
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(reinterpret_cast<char*>(vec.data()), sizeof(IPAddress) * static_cast<__int64>(size));
		file.close();
	}
	else
		throw std::runtime_error("WRITEDATATOBINARYFILE::OFSTREAM::could not open file");
}

std::vector<IPAddress> ReadDataFromBinaryFile(const char*& file_name) {
	std::ifstream file{ file_name };
	if (file.is_open()) {
		unsigned size{};
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		std::vector<IPAddress> vec(size);
		file.read(reinterpret_cast<char*>(vec.data()), sizeof(IPAddress) * static_cast<__int64>(size));
		file.close();
		return vec;
	}
	else
		throw std::runtime_error("READDATAFROMBINARYFILE::OFSTREAM::could not open file");
}