#include <iostream>
#include <algorithm>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <chrono>

const char* file_name_I{ "kontakti.txt" };
const char* file_name_O{ "data.dat" };

class Contact {
public:
	Contact(const char* name = "", const char* surname = "") {
		strcpy_s(name_, name);
		strcpy_s(surname_, surname);
	}

	const char* GetName() const {
		return name_;
	}

	const char* GetSurname() const {
		return surname_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& c) {
		std::cout << c.name_ << " " << c.surname_;
		return os;
	}
private:
	char name_[20]{};
	char surname_[20]{};
};

class Benchmarker {
public:
	Benchmarker() : start_{ std::chrono::high_resolution_clock::now() } {}
	~Benchmarker() {
		end_ = std::chrono::high_resolution_clock::now();
		std::cout 
			<< "time taken: "
			<< std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count() 
			<< std::endl;
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_, end_;
};

std::size_t CountLinesInTextFile(const char*&);
std::vector<Contact> InitializeVector(const std::size_t&);
void ReadDataFromTextFile(const char*&, std::vector<Contact>&);
void WriteDataToConsole(const std::vector<Contact>&);
void WriteDataToBinaryFile(const char*&, std::vector<Contact>&);
std::vector<Contact> ReadDataFromBinaryFile(const char*&);
char ReadCharFromConsole();

template <typename F>
std::vector<Contact> FilterContacts(F predicate, std::vector<Contact> vec) {
	std::vector<Contact> res{};
	res.reserve(vec.size());
	std::copy_if(
		std::begin(vec),
		std::end(vec),
		std::back_inserter(res),
		predicate
	);
	return res;
}


int main() {
	try {
		const std::size_t size{ CountLinesInTextFile(file_name_I) };
		std::vector<Contact> vec{ InitializeVector(size) };
		ReadDataFromTextFile(file_name_I, vec);
		WriteDataToBinaryFile(file_name_O, vec);

		try {
			std::vector<Contact> new_vec{ ReadDataFromBinaryFile(file_name_O) };
			char c{ ReadCharFromConsole() };
			std::vector<Contact> filtered_vec{ 
				FilterContacts(
					[c](const Contact& contact) -> bool {
						return contact.GetName()[0] == c || contact.GetSurname()[0] == c;
					},
					vec
				)
			};
			WriteDataToConsole(filtered_vec);
		}
		catch (const std::exception& err) {
			std::cerr << err.what() << std::endl;
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

std::vector<Contact> InitializeVector(const std::size_t& size) {
	std::vector<Contact> vec{};
	vec.reserve(size);
	return vec;
}

void ReadDataFromTextFile(const char*& file_name, std::vector<Contact>& vec) {
	std::ifstream file{ file_name };
	if (file.is_open()) {
		std::string line{};
		std::stringstream sstr{};
		char name[30], surname[30];
		for (std::size_t i{ 0 }; i < vec.capacity(); ++i) {
			std::getline(file, line);
			sstr.str(line);
			sstr.getline(name, 30, ';');
			sstr.getline(surname, 30, ';');
			vec.emplace_back(name, surname);
			sstr.clear();
		}
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMTEXTFILE::IFSTREAM::could not open file");
}

void WriteDataToConsole(const std::vector<Contact>& vec) {
	std::for_each(
		vec.begin(),
		vec.end(),
		[](const Contact& c) -> void {
			std::cout << c << std::endl;
		}
	);
}

void WriteDataToBinaryFile(const char*& file_name, std::vector<Contact>& vec) {
	std::ofstream file{ file_name, std::ios::binary };
	if (file.is_open()) {
		unsigned size{ vec.size() };
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(reinterpret_cast<char*>(vec.data()), sizeof(Contact) * static_cast<__int64>(size));
		file.close();
	}
	else
		throw std::runtime_error("WRITEDATATOBINARYFILE::OFSTREAM::could not open file");
}

std::vector<Contact> ReadDataFromBinaryFile(const char*& file_name) {
	std::ifstream file{ file_name, std::ios::binary };
	if (file.is_open()) {
		unsigned size{};
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		std::vector<Contact> vec(size);
		file.read(reinterpret_cast<char*>(vec.data()), sizeof(Contact) * static_cast<__int64>(size));
		file.close();
		return vec;
	}
	else
		throw std::runtime_error("READDATAFROMBINARYFILE::IFSTREAM::could not open file");
}

char ReadCharFromConsole() {
	char c{};
	std::cout << "Enter fist letter of name or surname: " << std::endl;
	std::cin >> c;
	return c;
}