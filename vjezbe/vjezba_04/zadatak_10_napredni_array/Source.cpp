#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string.h>
#include "Array.h"

const char* FILE_NAME_O = "players.dat";
const char* FILE_NAME_I = "mlb_players.csv";

struct Player {
	Player(
		const char* name, 
		const char* team, 
		const char* pos, 
		int height, 
		int weight, 
		double age
	)
		: height_{ height }, weight_{ weight }, age_{ age } {
		strcpy_s(name_, name);
		strcpy_s(team_, team);
		strcpy_s(pos_, pos);
	}

	friend std::ostream& operator<<(std::ostream& os, const Player& p) {
		os << p.name_ << " " << p.team_ << " " << p.pos_;
		return os;
	}

	char name_[30]{};
	char team_[5]{};
	char pos_[15]{};
	int height_;
	int weight_;
	double age_;
};

class FileAccessError : public std::exception {
public:
	FileAccessError() noexcept = default;
	~FileAccessError() = default;
	virtual const char* what() const noexcept {
		return "FSTREAM::could not access file";
	}
};

std::size_t CountLinesInTextFile(const char*&);
void ReadDataFromTextFile(const char*&, Array<Player>&);
void WriteDataToConsole(Array<Player>&);
void WriteDataToBinaryFile(const char*&, Array<Player>&);
Array<Player> ReadDataFromBinaryFile(const char*&);

int main() {
	try {
		const std::size_t count{ CountLinesInTextFile(FILE_NAME_I) };
		Array<Player> arr{ count };
		ReadDataFromTextFile(FILE_NAME_I, arr);
		WriteDataToBinaryFile(FILE_NAME_O, arr);

		try {
			Array<Player> new_arr{ ReadDataFromBinaryFile(FILE_NAME_O) };
			WriteDataToConsole(new_arr);
		}
		catch (const std::exception& err) {
			std::cerr << err.what() << std::endl;
			return 2;
		}
	}
	catch (const FileAccessError& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}

std::size_t CountLinesInTextFile(const char*& file_name) {
	std::ifstream file{ file_name };
	if (file.is_open()) {
		std::size_t res{
			static_cast<unsigned>(
				std::count(
					std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>(),
					'\n'
				)
			)
		};
		file.close();
		return res - 1;
	}
	else
		throw FileAccessError();
}

void ReadDataFromTextFile(const char*& file_name, Array<Player>& arr) {
	std::ifstream file{ file_name };
	if (file.is_open()) {
		std::string line{};
		std::getline(file, line);
		std::stringstream sstr{};
		std::string temp{};
		char name[30];
		char team[5];
		char pos[15];
		int height{};
		int weight{};
		double age{};
		for (std::size_t i{ 0 }; i < arr.Capacity(); ++i) {
			std::getline(file, line);
			sstr.str(line);
			sstr.getline(name, 30, ';');
			sstr.getline(team, 5, ';');
			sstr.getline(pos, 15, ';');
			std::getline(sstr, temp, ';');
			height = std::stoi(temp);
			std::getline(sstr, temp, ';');
			weight = std::stoi(temp);
			std::getline(sstr, temp);
			age = std::stod(temp);
			arr.EmplaceBack(name, team, pos, height, weight, age);
			sstr.clear();
		}
		file.close();
	}
	else
		throw FileAccessError();
}

void WriteDataToConsole(Array<Player>& arr) {
	std::for_each(
		arr.begin(),
		arr.end(),
		[](const Player& p) -> void {
			std::cout << p << std::endl;
		}
	);
}

void WriteDataToBinaryFile(const char*& file_name, Array<Player>& arr) {
	std::ofstream file{ file_name, std::ios::binary };
	if (file.is_open()) {
		unsigned count = arr.Size();
		file.write(reinterpret_cast<char*>(&count), sizeof(count));
		file.write(reinterpret_cast<char*>(arr.Data()), sizeof(Player) * static_cast<__int64>(count));
		file.close();
	}
	else
		throw FileAccessError();
}

Array<Player> ReadDataFromBinaryFile(const char*& file_name) {
	std::ifstream file{ file_name, std::ios::binary };
	if (file.is_open()) {
		unsigned count{};
		file.read(reinterpret_cast<char*>(&count), sizeof(count));
		Array<Player> arr{ count };
		file.read(reinterpret_cast<char*>(arr.Data()), sizeof(Player) * static_cast<__int64>(count));
		arr.SetSize(count);
		file.close();
		return arr;
	}
	else
		throw FileAccessError();
}