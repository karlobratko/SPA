#include "Core.h"

const char* bin_path_file{ "path.dat" };
const char* bin_data_file{ "data.dat" };
const std::vector<const char*> program_header{
	"                                  ,'\\",
	"    _.----.        ____         ,'  _\\   ___    ___     ____",
	"_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.",
	"\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |",
	" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |",
	"   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |",
	"    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |",
	"     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |",
	"      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |",
	"       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |",
	"        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |",
	"                                `'                            '-._|"
};

namespace std {
	std::ostream& operator<<(std::ostream& os, const std::pair<std::string, unsigned>& pair) {
		std::ostringstream oss{};
		oss
			<< std::left	<< std::setw(10) << pair.first + ": " << " "
			<< std::right << std::string(pair.second / 10, '#');
		if (!oss) os.setstate(oss.rdstate());
		else os << oss.str();
		return os;
	}
}

void ClearConsole() { std::system("CLS"); }

void WaitUserInput() { std::cin.get(); }

void WriteToConsole(const char* data) {	std::cout << data << std::endl; }

void WriteMsgToConsole(const std::string& msg) {
	WriteToConsole(msg.c_str());
	WaitUserInput();
	ClearConsole();
}

void WaitUserToPressKey() {
	std::ostringstream output{};
	output
		<< std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void WriteHeaderToConsole() {
	std::copy(
		std::begin(program_header), 
		std::end(program_header), 
		std::ostream_iterator<const char*>(std::cout, "\n")
	);
}

std::string ReadProgramStateFromConsole() {
	std::string program_state;
	std::ostringstream output{};
	output
		<< "0 - EXIT"										<< std::endl
		<< "1 - INPUT FILE PATH"				<< std::endl
		<< "2 - READ DATA FROM FILE"		<< std::endl
		<< "3 - WRITE DATA TO CONSOLE"	<< std::endl
		<< "4 - FIGHT"									<< std::endl
		<< "5 - COPY DATA TO FILE"			<< std::endl
		<< "6 - POKEMON PROCESSING"			<< std::endl
		<< "7 - SIMULATION"							<< std::endl
		<< "8 - SPEEDOGRAM"							<< std::endl;
	WriteToConsole(output.str().c_str());
	std::getline(std::cin, program_state);
	ClearConsole();
	if (program_state == "BEGIN TRAN") program_state.assign("9");
	else if (program_state.empty()) program_state.assign("e");
	return program_state;
}

void DetermineProgramState(const std::string& val, program_state_t& program_state) {
	switch (val[0]) {
	case '0': program_state = program_state_t::EXIT;
		break;
	case '1': program_state = program_state_t::INPUT_PATH;
		break;
	case '2': program_state = program_state_t::READ_DATA;
		break;
	case '3': program_state = program_state_t::WRITE_DATA;
		break;
	case '4': program_state = program_state_t::FIGHT;
		break;
	case '5': program_state = program_state_t::FILE_COPY;
		break;
	case '6': program_state = program_state_t::PROCESSING;
		break;
	case '7': program_state = program_state_t::SIMULTAION;
		break;
	case '8': program_state = program_state_t::SPEEDOGRAM;
		break;
	case '9': program_state = program_state_t::TRANSACTION;
		break;
	case 'e': program_state = program_state_t::VOID;
		break;
	default: program_state = program_state_t::VOID;
		throw program_state_except_t{};
		break;
	}
}

void ManageProgramState(program_state_t& program_state, std::vector<pokemon_t>& vec) {
	switch (program_state) {
	case program_state_t::EXIT: ManageStateExit(program_state);
		break;
	case program_state_t::INPUT_PATH: ManageStateInputPath();
		break;
	case program_state_t::READ_DATA: ManageStateReadData(vec);
		break;
	case program_state_t::WRITE_DATA: ManageStateWriteData(vec);
		break;
	case program_state_t::FIGHT: ManageStateFight(vec);
		break;
	case program_state_t::FILE_COPY: ManageStateFileCopy();
		break;
	case program_state_t::PROCESSING: ManageStateProcessing(vec);
		break;
	case program_state_t::SIMULTAION: ManageStateSimulation(vec);
		break;
	case program_state_t::SPEEDOGRAM: ManageStateSpeedogram(vec);
		break;
	case program_state_t::TRANSACTION: ManageStateTransaction(vec);
		break;
	case program_state_t::VOID:
		break;
	}
}

void ManageStateExit(program_state_t& program_state) {
	char exit{};
	WriteToConsole("Do you really want to exit? (1 - YES / 0 - NO)");
	std::cin >> exit;
	std::cin.ignore();
	exit != '0'
		? program_state = program_state_t::EXIT
		: program_state = program_state_t::VOID;
	ClearConsole();
}

void ManageStateInputPath() {
	std::string path{};
	WriteToConsole("Enter path to Pokemon .csv file.");
	std::getline(std::cin, path);
	ClearConsole();

	file_t file{ bin_path_file, std::ios::out | std::ios::binary };
	file->write(path.c_str(), path.size());

	std::ostringstream output{};
	output
		<< "Path saved successfully." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void ManageStateReadData(std::vector<pokemon_t>& vec) {
	long long time_taken{};
	if (TestLoadFileExistance()) ReadExistingData(vec, time_taken);
	else ReadNewData(vec, time_taken);
	ClearConsole();

	std::ostringstream output{};
	output
		<< "Data transfered successfully."									<< std::endl
		<< "Time taken: " << time_taken << " microseconds." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void ReadExistingData(std::vector<pokemon_t>& vec, long long& time_taken) {
	char load{};
	WriteToConsole("Do you want to load existing data? (1 - YES / 0 - NO)");
	std::cin >> load;
	std::cin.ignore();
	{
		benchmarker_t bm{};
		if (load != '0') ReadDataFromBinaryFile(vec);
		else ReadNewData(vec, time_taken);
		time_taken = bm.TimeTaken();
	}
}

void ReadNewData(std::vector<pokemon_t>& vec, long long& time_taken) {
	{
		benchmarker_t bm{};
		file_t file{ ReadPathFromBinaryFile().c_str(), std::ios::in };
		file.getline();
		vec.clear();
		std::copy(
			std::istream_iterator<pokemon_t>(*file), 
			std::istream_iterator<pokemon_t>(), 
			std::back_inserter(vec)
		);
		time_taken = bm.TimeTaken();
	}
	WriteDataToBinaryFile(vec);
}

bool TestLoadFileExistance() {
	file_t file{};
	file->open(bin_data_file, std::ios::in | std::ios::binary);
	if (file->is_open()) return true;
	return false;
}

std::string ReadPathFromBinaryFile() {
	file_t file{ bin_path_file, std::ios::in | std::ios::binary };

	file->seekg(0, std::ios::end);
	std::size_t path_len{ static_cast<std::size_t>(file->tellg()) };
	file->seekg(0, std::ios::beg);
	
	char* path_cstr{ new char[path_len] };
	auto act1 = finally_t(
		[&path_cstr]() -> void { 
			delete[] path_cstr;  
			path_cstr = nullptr;
		}
	);
	file->read(reinterpret_cast<char*>(path_cstr), path_len);
	return std::string(path_cstr, path_len);
}

void WriteDataToBinaryFile(std::vector<pokemon_t>& vec) {
	file_t file{ bin_data_file, std::ios::out | std::ios::binary };
	file->write(reinterpret_cast<char*>(vec.data()), sizeof(pokemon_t) * static_cast<__int64>(vec.size()));
}

void ReadDataFromBinaryFile(std::vector<pokemon_t>& vec) {
	file_t file{ bin_data_file, std::ios::in | std::ios::binary };
	file->seekg(0, std::ios::end);
	vec.resize(static_cast<unsigned>(file->tellg()) / sizeof(pokemon_t));
	file->seekg(0, std::ios::beg);
	file->read(reinterpret_cast<char*>(vec.data()), sizeof(pokemon_t) * static_cast<__int64>(vec.size()));
}

void ManageStateWriteData(std::vector<pokemon_t>& vec) {
	benchmarker_t bm{};
	WriteDataToConsole<std::vector<pokemon_t>>(vec);
	long long time_taken{ bm.TimeTaken() };

	std::ostringstream output{};
	output
		<< std::endl
		<< "Time taken: " << time_taken << " microseconds." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

template <typename Cont>
void WriteDataToConsole(Cont& cont) {
	if (cont.empty())
		throw std::runtime_error("MANAGESTATEWRITEDATA::no data to write to console, empty container");
	std::ostringstream output{};
	output
		<< std::left
		<< std::setw(4)		<< "ID"			<< " "
		<< std::right
		<< std::setw(30)	<< "NAME"		<< " "
		<< std::setw(10)	<< "TYPE 1" << " "
		<< std::setw(10)	<< "TYPE 2" << " "
		<< std::setw(10)	<< "TOTAL"	<< " "
		<< std::setw(10)	<< "HP"			<< " "
		<< std::setw(10)	<< "ATK"		<< " "
		<< std::setw(10)	<< "DEF"		<< " "
		<< std::setw(10)	<< "SPATK"	<< " "
		<< std::setw(10)	<< "SPDEF"	<< " "
		<< std::setw(10)	<< "SPEED"	<< " ";
	WriteToConsole(output.str().c_str());
	std::copy(
		std::begin(cont), 
		std::end(cont), 
		std::ostream_iterator<pokemon_t>(std::cout, "\n")
	);
}


void ManageStateFight(std::vector<pokemon_t>& vec) {
	WriteDataToConsole<std::vector<pokemon_t>>(vec);
	WriteToConsole("");

	std::string attacker_name{};
	WriteToConsole("Enter attacker name: ");
	std::getline(std::cin, attacker_name);
	pokemon_t& attacker{ FindPokemonByNameInVector(attacker_name, vec) };

	std::string defender_name{};
	WriteToConsole("Enter defender name: ");
	std::getline(std::cin, defender_name);
	pokemon_t& defender{ FindPokemonByNameInVector(defender_name, vec) };

	ClearConsole();

	std::stringstream output{};
	output
		<< "Attacker: "		<< attacker.getName()									<< std::endl
		<< "Defender: "		<< defender.getName()									<< std::endl
		<< "Winner is: "	<< defender.fight(attacker).getName() << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

pokemon_t& FindPokemonByNameInVector(const std::string& name, std::vector<pokemon_t>& vec) {
	auto pokemon = std::find(vec.begin(), vec.end(), name);
	if (pokemon == vec.end()) 
		throw std::runtime_error("MANAGESTATEFIGHT::invalid pokemon name");
	return *pokemon;
}

void ManageStateFileCopy() {
	WriteToConsole("Enter output file name.");
	std::string out_file_name{};
	std::getline(std::cin, out_file_name);
	ClearConsole();

	WriteToConsole("Define output order. (1 - ASC / 0 - DESC)");
	char load{};
	std::cin >> load;
	std::cin.ignore();
	ClearConsole();

	file_t in_file	{ ReadPathFromBinaryFile().c_str(), std::ios::in										};
	file_t out_file	{ out_file_name.c_str(),						std::ios::out | std::ios::trunc };

	benchmarker_t bm{};
	if (load != '0')
		std::copy(
			std::istreambuf_iterator<char>(*in_file), 
			std::istreambuf_iterator<char>(), 
			std::ostreambuf_iterator<char>(*out_file)
		);
	else {
		std::stack<std::string> file_stack{};
		std::string line{};
		while (std::getline(*in_file, line))
			file_stack.push(line);
		while (!file_stack.empty()) {
			*out_file << file_stack.top() << std::endl;
			file_stack.pop();
		}
	}
	long long time_taken{ bm.TimeTaken() };

	std::ostringstream output{};
	output
		<< "Data transfered " << (load == '0' ? "descending" : "ascending") << " into " << out_file_name << " successfully."	<< std::endl
		<< "Time taken: "			<< time_taken << " microseconds."																																<< std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void ManageStateProcessing(std::vector<pokemon_t>& vec) {
	if (vec.empty()) 
		throw std::runtime_error("MANAGESTATEPROCESSING::no data to process, empty vector");

	WriteToConsole("Enter TYPE of pokemons to process.");
	std::string type{};
	std::getline(std::cin, type);
	ClearConsole();

	std::list<pokemon_t> type_pokemons{};
	std::copy_if(
		std::begin(vec), 
		std::end(vec), 
		std::back_inserter(type_pokemons), 
		std::bind(pokemon_t::isType, std::placeholders::_1, type)
	);
	if (type_pokemons.empty()) 
		throw std::runtime_error("MANAGESTATEPROCESSING::invalid type name, empty list");

	WriteToConsole("Enter minimum TOTAL for processing.");
	int total{};
	std::cin >> total;
	std::cin.ignore();
	ClearConsole();

	type_pokemons.erase(
		std::remove_if(
			std::begin(type_pokemons), 
			std::end(type_pokemons), 
			std::bind<bool>(pokemon_t::totalLowerThan, std::placeholders::_1, total)
		),
		std::end(type_pokemons)
	);

	if (type_pokemons.empty()) 
		throw std::runtime_error("MANAGESTATEPROCESSING::total to high, empty list");

	WriteToConsole("Enter propery name for processing.");
	std::string prop{};
	std::getline(std::cin, prop);
	ClearConsole();

	if (
		prop != "HP"		&& 
		prop != "ATK"		&& 
		prop != "DEF"		&& 
		prop != "SPATK" && 
		prop != "SPDEF" && 
		prop != "SPEED"
		) throw std::runtime_error("MANAGESTATEPROCESSING::invalid pokemon property name");

	std::ostringstream output{};
	output << "Enter " << prop << " multiplier for processing.";
	WriteToConsole(output.str().c_str());
	output.str("");
	output.clear();
	double prop_mult{};
	std::cin >> prop_mult;
	std::cin.ignore();
	ClearConsole();

	std::transform(
		std::begin(type_pokemons), 
		std::end(type_pokemons), 
		std::begin(type_pokemons), 
		std::bind<pokemon_t>(pokemon_t::multiplyProp, std::placeholders::_1, prop, prop_mult)
	);

	std::reverse(std::begin(type_pokemons), std::end(type_pokemons));

	WriteDataToConsole<std::list<pokemon_t>>(type_pokemons);

	output
		<< std::endl
		<< "Pokemons processed successfully." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void ManageStateSimulation(std::vector<pokemon_t>& vec) {
	if (vec.empty()) 
		throw std::runtime_error("MANAGESTATESIMULATION::no data to process, empty vector");

	std::shuffle(std::begin(vec), std::end(vec), std::mt19937{ std::random_device{}() });

	std::queue<pokemon_t> chard_queue{};
	std::for_each(
		std::begin(vec), 
		std::end(vec), 
		[n = 0, &chard_queue](const pokemon_t& p) mutable -> void {
			chard_queue.push(p);
			std::cout 
				<< std::setw(4)		<< ++n 
				<<  ". Pokemon "	<< p.getName() << " entered into CHARD QUEUE." << std::endl;
		}
	);

	std::ostringstream output{};
	output
		<< std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
	output.str("");
	output.clear();

	unsigned n{};
	while (!chard_queue.empty()) {
		std::cout
			<< std::setw(4) << ++n
			<< ". Pokemon " << chard_queue.front().getName() << " entered into ARENA." << std::endl;
		chard_queue.pop();
	}

	output
		<< std::endl
		<< "Pokemons simulated successfully." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void ManageStateSpeedogram(std::vector<pokemon_t>& vec) {
	if (vec.empty()) 
		throw std::runtime_error("MANAGESTATESPEEDOGRAM::no data to process, empty vector");
	std::map<std::string, unsigned> speed_count{
		{ "0-19", 0 },
		{ "20-39", 0 },
		{ "40-59", 0 },
		{ "60-79", 0 },
		{ "80-99", 0 },
		{ ">=100", 0 },
	};
	std::for_each(
		std::begin(vec), 
		std::end(vec), 
		[&speed_count](const pokemon_t& p) { speed_count[p.getSpeedInterval()]++; }
	);
	std::copy(
		std::begin(speed_count), 
		std::end(speed_count), 
		std::ostream_iterator<std::pair<std::string, unsigned>>(std::cout, "\n")
	);

	std::ostringstream output{};
	output
		<< std::endl
		<< "Speedogram calculated successfully." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}

void ManageStateTransaction(std::vector<pokemon_t>& vec) {
	if (vec.empty())
		throw std::runtime_error("MANAGESTATETRANSACTION::no data to process, empty vector");

	std::string line{};
	std::istringstream iss{};
	std::string command{};
	
	std::stack<std::vector<pokemon_t>> transaction_stack{};
	transaction_stack.push(vec);
	vec.clear();
	while (true) {
		std::getline(std::cin, line);
		iss.str(line);
		iss >> command;

		if (command == "COMMIT") {
			vec = std::move(transaction_stack.top());
			while (!transaction_stack.empty()) transaction_stack.pop();
			break;
		}
		else if (command == "ADD") {
			std::string prop{};
			int value{};
			iss >> prop;
			iss >> value;
			if (
				prop != "HP"		&&
				prop != "ATK"		&&
				prop != "DEF"		&&
				prop != "SPATK" &&
				prop != "SPDEF" &&
				prop != "SPEED"
				) continue;
			std::vector<pokemon_t> new_vec{};
			std::transform(
				std::begin(transaction_stack.top()), 
				std::end(transaction_stack.top()), 
				std::back_inserter(new_vec),
				std::bind<pokemon_t>(pokemon_t::increaseProp, std::placeholders::_1, prop, value)
			);
			transaction_stack.push(new_vec);
			
		}
		else if (command == "ROLLBACK" && transaction_stack.size() > 1)
			transaction_stack.pop();

		iss.clear();
	}
	ClearConsole();

	WriteDataToConsole<std::vector<pokemon_t>>(vec);

	std::ostringstream output{};
	output
		<< std::endl
		<< "Transaction managed successfully." << std::endl << std::endl
		<< "Press any key to continue...";
	WriteMsgToConsole(output.str());
}