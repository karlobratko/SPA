#include "Core.h"

void ClearConsole() {
	std::system("CLS");
}

void WriteHeaderToConsole() {
	std::for_each(PROGRAM_HEADER.begin(), PROGRAM_HEADER.end(), [](const char* c) {
		std::cout << c << std::endl;
		}
	);
}

void WaitUserInput(const std::string& msg) {
	std::cout << msg << std::endl;
	std::cin.get();
	ClearConsole();
}

void ReadProgramStateFromConsole(char& program_state) {
	std::cout
		<< "0 - EXIT" << std::endl
		<< "1 - INPUT FILE PATH" << std::endl
		<< "2 - READ DATA FROM FILE" << std::endl
		<< "3 - WRITE DATA TO CONSOLE" << std::endl
		<< "4 - FIGHT" << std::endl << std::endl;
	std::cin >> program_state;
	std::cin.ignore();
	ClearConsole();
}

void DetermineProgramState(const char& val, ProgramState& program_state) {
	switch (val) {
	case '0':
		program_state = ProgramState::EXIT;
		break;
	case '1':
		program_state = ProgramState::INPUT_PATH;
		break;
	case '2':
		program_state = ProgramState::READ_DATA;
		break;
	case '3':
		program_state = ProgramState::WRITE_DATA;
		break;
	case '4':
		program_state = ProgramState::FIGHT;
		break;
	default:
		program_state = ProgramState::VOID;
		throw std::out_of_range("MANAGESTATE::PROGRAMSTATE::input value out of range\n");
		break;
	}
}

void ManageState(ProgramState& program_state, std::vector<Pokemon>& vec) {
	switch (program_state) {
	case ProgramState::EXIT:
		ManageStateExit(program_state);
		break;
	case ProgramState::INPUT_PATH:
		ManageStateInputPath();
		break;
	case ProgramState::READ_DATA:
		ManageStateReadData(vec);
		break;
	case ProgramState::WRITE_DATA:
		ManageStateWriteData(vec);
		break;
	case ProgramState::FIGHT:
		ManageStateFight(vec);
	case ProgramState::VOID:
		break;
	}
}

void ManageStateExit(ProgramState& program_state) {
	char exit{};
	std::cout << "Do you really want to exit? (1 - YES / 0 - NO)" << std::endl;
	std::cin >> exit;
	std::cin.ignore();
	exit != '0'
		? program_state = ProgramState::EXIT
		: program_state = ProgramState::VOID;
	ClearConsole();
}

void ManageStateInputPath() {
	std::string path{};
	std::cout << "Enter path to Pokemon .csv file." << std::endl;
	std::getline(std::cin, path);
	ClearConsole();

	std::fstream file{ B_PATH_FILE, std::ios::out | std::ios::binary };
	if (file.is_open()) {
		short path_length{ static_cast<short>(path.size()) };
		file.write(reinterpret_cast<char*>(&path_length), sizeof(path_length));
		file.write(path.c_str(), path_length);
		file.close();
	}
	else
		throw std::runtime_error("MANAGESTATEINPUTPATH::FSTREAM::OFSTREAM::unable to open file\n");
	std::stringstream output{};
	output
		<< "Path saved successfully." << std::endl << std::endl
		<< "Press any key to continue...";
	WaitUserInput(output.str());
}

void ManageStateReadData(std::vector<Pokemon>& vec) {
	vec.clear();
	std::fstream file{};
	long long time_taken{};
	if (TestLoadFileExistance(file))
		ReadExistingData(vec, file, time_taken);
	else ReadNewData(vec, file, time_taken);
	file.close();
	ClearConsole();

	std::stringstream output{};
	output
		<< "Data transfered successfully." << std::endl
		<< "Time taken: " << time_taken << " microseconds." << std::endl << std::endl
		<< "Press any key to continue...";
	WaitUserInput(output.str());
}

void ReadExistingData(std::vector<Pokemon>& vec, std::fstream& file, long long& time_taken) {
	char load{};
	std::cout << "Do you want to load existing data? (1 - YES / 0 - NO)" << std::endl;
	std::cin >> load;
	std::cin.ignore();
	{
		Benchmarker bm{};
		if (load != '0') ReadDataFromBinaryFile(vec, file);
		else ReadNewData(vec, file, time_taken);
		time_taken = bm.TimeTaken();
	}
}

void ReadNewData(std::vector<Pokemon>& vec, std::fstream& file, long long& time_taken) {
	{
		Benchmarker bm{};
		std::string file_name{};
		ReadPathFromBinaryFile(file_name, file);
		const std::size_t size{ CountLinesInTextFile(file, file_name) };
		vec = std::vector<Pokemon>{ size };
		ReadDataFromTextFile(vec, size, file, file_name);
		time_taken = bm.TimeTaken();
	}
	WriteDataToBinaryFile(vec, file);
}

bool TestLoadFileExistance(std::fstream& file) {
	file.open(B_DATA_FILE, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		file.close();
		return true;
	}
	return false;
}

void ReadPathFromBinaryFile(std::string& path, std::fstream& file) {
	file.open(B_PATH_FILE, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		short path_length{};
		file.read(reinterpret_cast<char*>(&path_length), sizeof(path_length));
		char* path_cstr{ new char[path_length] };
		auto act1 = Finally(
			[&]() -> void { 
				delete[] path_cstr;  
				path_cstr = nullptr;
			}
		);
		file.read(reinterpret_cast<char*>(path_cstr), path_length);
		path.assign(path_cstr, path_length);
		file.close();
	}
	else
		throw std::runtime_error("READPATHFROMBINARYFILE::FSTREAM::IFSTREAM::unable to open file\n");
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
		throw std::runtime_error("COUNTLINESINTEXTFILE::FSTREAM::IFSTREAM::unable to open file\n");
}

void ReadDataFromTextFile(std::vector<Pokemon>& vec, const std::size_t& size, std::fstream& file, const std::string& file_name) {
	file.open(file_name, std::ios::in);
	if (file.is_open()) {
		std::string line{};
		std::getline(file, line);
		for_each(
			vec.begin(), vec.end(),
			[&](Pokemon& p) -> void {
				std::getline(file, line);
				p.SetData(line);
			}
		);
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMTEXTFILE::FSTREAM::IFSTREAM::unable to open file\n");
}

void WriteDataToBinaryFile(std::vector<Pokemon>& vec, std::fstream& file) {
	file.open(B_DATA_FILE, std::ios::out | std::ios::binary);
	if (file.is_open()) {
		short size{ static_cast<short>(vec.size()) };
		file.write(reinterpret_cast<char*>(&size), sizeof(size));
		file.write(reinterpret_cast<char*>(vec.data()), sizeof(Pokemon) * static_cast<__int64>(size));
		file.close();
	}
	else
		throw std::runtime_error("WRITEDATATOBINARYFILE::FSTREAM::OFSTREAM::unable to open file\n");
}

void ReadDataFromBinaryFile(std::vector<Pokemon>& vec, std::fstream& file) {
	file.open(B_DATA_FILE, std::ios::in | std::ios::binary);
	if (file.is_open()) {
		short size{};
		file.read(reinterpret_cast<char*>(&size), sizeof(size));
		vec = std::vector<Pokemon>{ static_cast<std::size_t>(size) };
		file.read(reinterpret_cast<char*>(vec.data()), sizeof(Pokemon) * static_cast<__int64>(size));
		file.close();
	}
	else
		throw std::runtime_error("READDATAFROMBINARYFILE::FSTREAM::IFSTREAM::unable to open file\n");
}

void ManageStateWriteData(std::vector<Pokemon>& vec) {
	Benchmarker bm{};
	WriteDataToConsole(vec);
	long long time_taken{ bm.TimeTaken() };

	std::stringstream output{};
	output
		<< std::endl
		<< "Time taken: " << time_taken << " microseconds." << std::endl << std::endl
		<< "Press any key to continue...";
	WaitUserInput(output.str());
}

void WriteDataToConsole(std::vector<Pokemon>& vec) {
	if (vec.size() == 0)
		throw std::runtime_error("MANAGESTATEWRITEDATA::no data to write to console, empty vector\n");
	std::cout
		<< std::setw(4) << "ID" << " "
		<< std::setw(30) << "NAME" << " "
		<< std::setw(10) << "TYPE 1" << " "
		<< std::setw(10) << "TYPE 2" << " "
		<< std::setw(5) << "TOTAL"
		<< std::endl;
	for_each(
		vec.begin(), vec.end(),
		[](Pokemon& p) -> void {
			std::cout << p << std::endl;
		}
	);
}


void ManageStateFight(std::vector<Pokemon>& vec) {
	WriteDataToConsole(vec);
	std::cout << std::endl;

	std::string attacker_name{};
	std::cout << "Enter attacker name: " << std::endl;
	std::getline(std::cin, attacker_name);
	Pokemon& attacker{ FindPokemonByNameInVector(attacker_name, vec) };

	std::string defender_name{};
	std::cout << "Enter defender name: " << std::endl;
	std::getline(std::cin, defender_name);
	Pokemon& defender{ FindPokemonByNameInVector(defender_name, vec) };

	ClearConsole();

	std::stringstream output{};
	output
		<< "Attacker: " << std::endl << attacker << std::endl << std::endl
		<< "Defender: " << std::endl << defender << std::endl
		<< std::endl
		<< "Winner is: " << defender.Fight(attacker).GetName() << std::endl << std::endl
		<< "Press any key to continue...";
	WaitUserInput(output.str());
}

Pokemon& FindPokemonByNameInVector(const std::string& name, std::vector<Pokemon>& vec) {
	std::vector<Pokemon>::iterator pokemon = std::find_if(
		vec.begin(), vec.end(),
		[&name](const Pokemon& p) -> bool {
			return name == p.GetName();
		}
	);
	if (pokemon == vec.end())
		throw std::runtime_error("MANAGESTATEFIGHT::invalid pokemon name\n");

	return *pokemon;
}