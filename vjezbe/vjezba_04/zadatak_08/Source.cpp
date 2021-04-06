#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include "IpAddress.h"

const char* file_name_I = "ip_adrese.txt";
const char* file_name_O = "adrese.dat";

std::size_t CountLinesInTextFile(const char*&);
std::vector<IPAddress> InitializeVector(const std::size_t&);
void ReadDataFromTextFile(const char*&, std::vector<IPAddress>&);
void WriteDataToConsole(const std::vector<IPAddress>&);
void WriteDataToBinaryFile(const char*&, std::vector<IPAddress>&);
std::vector<IPAddress> ReadDataFromBinaryFile(const char*&);
std::map<char, unsigned> MapIPAddressClasses(const std::vector<IPAddress>&);
void WriteIPCassesMapToConsole(const std::map<char, unsigned>&);

int main() {
	try {
		const std::size_t size{ CountLinesInTextFile(file_name_I) };
		std::vector<IPAddress> vec{ InitializeVector(size) };
		ReadDataFromTextFile(file_name_I, vec);
		WriteDataToBinaryFile(file_name_O, vec);

		try {
			std::vector<IPAddress> new_vec{ ReadDataFromBinaryFile(file_name_O) };
			//WriteDataToConsole(new_vec);
			WriteIPCassesMapToConsole(
				MapIPAddressClasses(new_vec)
			);
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
		throw std::runtime_error{ "COUNTLINESINTEXTFILE::IFSTREAM::could not open file"};
}

std::vector<IPAddress> InitializeVector(const std::size_t& size) {
	std::vector<IPAddress> res{};
	res.reserve(size);
	return res;
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
		throw std::runtime_error{ "READDATAFROMTEXTFILE::IFSTREAM::could not open file"};
}

void WriteDataToConsole(const std::vector<IPAddress>& vec) {
	std::for_each(
		std::begin(vec),
		std::end(vec), 
		[](const IPAddress& ip) { std::cout << ip << std::endl; }
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
		throw std::runtime_error{ "WRITEDATATOBINARYFILE::OFSTREAM::could not open file" };
}

std::vector<IPAddress> ReadDataFromBinaryFile(const char*& file_name) {
	std::ifstream file{ file_name, std::ios::binary };
	if (file.is_open()) {
		unsigned size{};
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		std::vector<IPAddress> res(size);
		file.read(reinterpret_cast<char*>(res.data()), sizeof(IPAddress) * static_cast<__int64>(size));
		file.close();
		return res;
	}
	else
		throw std::runtime_error{ "READDATAFROMBINARYFILE::IFSTREAM::could not open file" };
}

std::map<char, unsigned> MapIPAddressClasses(const std::vector<IPAddress>& vec) {
	std::map<char, unsigned> classes{
		{ 'A', 0 },
		{ 'B', 0 },
		{ 'C', 0 },
		{ 'D', 0 },
		{ 'E', 0 }
	};
	std::for_each(
		std::begin(vec),
		std::end(vec),
		[&classes](const IPAddress& ip) -> void {
			try {
				++classes.at(ip.DetermineClass());
			}
			catch (const std::out_of_range&) {
			}
		}
	);
	return classes;
}

void WriteIPCassesMapToConsole(const std::map<char, unsigned>& map) {
	std::for_each(
		std::begin(map),
		std::end(map),
		[](const std::pair<char, unsigned>& pair) -> void {
			std::cout << "Class " << pair.first << ": ";
			for (std::size_t i{ 0 }; i < pair.second; ++i)
				std::cout << "#";
			std::cout << " (" << pair.second << ")" << std::endl;
		}
	);
}