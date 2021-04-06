#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>

const char* file_name_I{ "tocke.txt" };
const char* file_name_O{ "Vector3i.dat" };

class Vector3i {
public:
	Vector3i(int x = 0, int y = 0, int z = 0) 
		: x_{ x }, y_{ y }, z_{ z } {}
	friend std::ostream& operator<<(std::ostream& os, const Vector3i& vec) {
		os << "(" << vec.x_ << "," << vec.y_ << "," << vec.z_ << ")";
		return os;
	}
private:
	int x_, y_, z_;
};

std::size_t CountLinesInTextFile(std::fstream&, const char*&);
std::vector<Vector3i> InitializeVector(const std::size_t&);
void ReadDataFromTextFile(std::fstream&, const char*&, std::vector<Vector3i>&);
void WriteDataToBinaryFile(std::fstream&, const char*&, std::vector<Vector3i>&);
std::vector<Vector3i> ReadDataFromBinaryFile(std::fstream&, const char*&);
void WriteDataToConsole(const std::vector<Vector3i>&);

int main() {
	std::fstream file{};
	try {
		const std::size_t size{ CountLinesInTextFile(file, file_name_I) };
		std::vector<Vector3i> vec{ InitializeVector(size) };
		ReadDataFromTextFile(file, file_name_I, vec);
		WriteDataToBinaryFile(file, file_name_O, vec);

		try {
			std::vector<Vector3i> new_vec{ ReadDataFromBinaryFile(file, file_name_O) };
			WriteDataToConsole(new_vec);
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

std::size_t CountLinesInTextFile(std::fstream& file, const char*& file_name) {
	file.open(file_name, std::ios::in);
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
		throw std::runtime_error("COUNTLINESINTEXTFILE::FSTREAM::IFSTREAM::could not open file");
}

std::vector<Vector3i> InitializeVector(const std::size_t& size) {
	std::vector<Vector3i> temp{};
	temp.reserve(size);
	return temp;
}

void ReadDataFromTextFile(std::fstream& file, const char*& file_name, std::vector<Vector3i>& vec) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::string line{};
		std::stringstream sstr{};
		int x{}, y{}, z{};
		for (std::size_t i{ 0 }; i < vec.capacity(); ++i) {
			std::getline(file, line);
			sstr.str(line);
			sstr >> x >> y >> z;
			vec.emplace_back(x, y, z);
			sstr.clear();
		}
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMTEXTFILE::FSTREAM::IFSTREAM::could not open file");
}

void WriteDataToBinaryFile(std::fstream& file, const char*& file_name, std::vector<Vector3i>& vec) {
	file.open(file_name, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		unsigned size{ vec.size() };
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(reinterpret_cast<char*>(vec.data()), sizeof(Vector3i) * static_cast<__int64>(vec.size()));
		file.close();
	}
	else
		throw std::runtime_error("WRITEDATATOBINARYFILE::FSTREAM::OFSTREAM::could not open file");
}

std::vector<Vector3i> ReadDataFromBinaryFile(std::fstream& file, const char*& file_name) {
	file.open(file_name, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		unsigned size{};
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		std::vector<Vector3i> vec(size);
		file.read(reinterpret_cast<char*>(vec.data()), sizeof(Vector3i) * static_cast<__int64>(size));
		file.close();
		return vec;
	}
	else
		throw std::runtime_error("READDATAFROMBINARYFILE::FSTREAM::IFSTREAM::could not open file");
}

void WriteDataToConsole(const std::vector<Vector3i>& vec) {
	std::for_each(
		vec.begin(),
		vec.end(),
		[](const Vector3i& v) -> void {
			std::cout << v << std::endl;
		}
	);
}