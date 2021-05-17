#include "application_t.h"

const char* bin_file_path{ "path.dat" };
const char* csv_file_data_01{ "SPA_PROJ_003_HEROES_data_1.csv" };
const char* csv_file_data_02{ "SPA_PROJ_003_HEROES_data_2.csv" };
const char* bin_file_data_01{ "data_01.dat" };
const char* bin_file_data_02{ "data_01.dat" };

namespace std {
	std::ostream& operator<<(std::ostream& os, const std::pair<std::string, unsigned>& pair) {
		std::ostringstream oss{};
		oss
			<< std::left << std::setw(30) << pair.first + ": " << " "
			<< std::right << std::string(pair.second / 10, '#') << std::string(pair.second % 10, 'o') << " (" << pair.second << ")";
		if (!oss) os.setstate(oss.rdstate());
		else os << oss.str();
		return os;
	}
}

application_t::application_t(std::vector<const char*> header) :
	header_				{	header						},
	program_state_{ progstate_t::VOID } {
}

bool application_t::is_running() const {
	return program_state_ != progstate_t::EXIT;
}

void application_t::header() {
	std::copy(
		std::begin(header_),
		std::end(header_),
		std::ostream_iterator<const char*>(*console_, "\n")
	);
	console_.message("Press any key to continue...");
}

void application_t::determine_state() {
	try {
		program_state_ = command_state.at(read_state());
	}
	catch (const std::exception&) {
		throw_e("invalid input");
	}
}

void application_t::manage_state() const {
	state_function.at(program_state_)();
}

void application_t::catch_e(const std::exception& err) {
	console_.write(err.what());
	console_.message("\nPress any key to continue...");
}

std::string application_t::read_state() {
	{ std::ostringstream oss{};
		oss
			<< "EXIT                 - exit application" << std::endl
			<< "PATH                 - enter path to files" << std::endl
			<< "COPY [-D/F] [-A/-D]  - transfer data from files [to database/file] [asc/desc]" << std::endl
			<< "WRITE [-V]           - write data to console [verbose]" << std::endl
			<< "PROC [-G/B]          - process heroes [good/bad]" << std::endl
			<< "FIGHT                - simulate heroes fight" << std::endl
			<< "STAT                 - output powers status" << std::endl
			<< "BEGIN TRAN           - property management" << std::endl;
		console_.write(oss.str().c_str());
	}
	std::string program_state(console_.read_s());
	console_.clear();
	return program_state.empty() ? "" : program_state;
}

std::string application_t::read_path() {
	file_t file{ bin_file_path, std::ios::in | std::ios::binary };
	file.check();
	std::size_t path_len{ file.size() };
	char* path_cstr{ new char[path_len] };
	file->read(reinterpret_cast<char*>(path_cstr), path_len);
	std::string str(path_cstr, path_len);
	str.append("\\");
	delete[] path_cstr;
	return str;
}

void application_t::throw_e(const char* msg) {
	program_state_ = progstate_t::VOID;
	console_.clear();
	throw application_except_t{ msg };
}

void application_t::manage_state_void() {}

void application_t::manage_state_exit() {
	program_state_ = progstate_t::EXIT;
}

void application_t::manage_state_path() {
	{ std::ostringstream oss{};
		oss << "Enter path to .csv files." << std::endl;
		console_.write(oss.str().c_str());
	}
	std::string path{ console_.read_s() };
	console_.clear();

	file_t file{ bin_file_path, std::ios::out | std::ios::binary };
	file.check();
	file->write(path.c_str(), path.size());

	{ std::ostringstream oss{};
		oss
			<< "Path saved successfully." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_data() {
	benchmarker_t bm{};
	std::string path{ read_path() };

	{ file_t file_csv_01{ std::string{ path + csv_file_data_01 }.c_str(), std::ios::in };
		file_csv_01.check();
		file_csv_01.getline();
		database_.read_heroes(*file_csv_01);
	}

	{ file_t file_csv_02{ std::string{ path + csv_file_data_02 }.c_str(), std::ios::in };
		file_csv_02.check();
		file_csv_02.getline();
		database_.read_powers(*file_csv_02);
	}

	database_.combine();

	{ std::ostringstream oss{};
		oss
			<< "Data transfered successfully." << std::endl
			<< "Time taken: " << bm.count() << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_write(bool verbose) {
	benchmarker_t bm{};
	{ std::ostringstream oss{};
		if (verbose)
			oss
				<< std::left
				<< std::setw(20) << "NAME" << " "
				<< std::right
				<< std::setw(5) << "ALIGN" << " "
				<< std::setw(5) << "INT" << " "
				<< std::setw(5) << "STR" << " "
				<< std::setw(5) << "SPD" << " "
				<< std::setw(5) << "DUR" << " "
				<< std::setw(5) << "POW" << " "
				<< std::setw(5) << "COMB" << " "
				<< std::setw(5) << "TOTAL" << " "
				<< "POWERS" << std::endl;
		else
			oss
				<< std::left
				<< std::setw(20)	<< "NAME"		<< " "
				<< std::right
				<< std::setw(5)		<< "ALIGN"	<< " "
				<< std::setw(5)		<< "INT"		<< " "
				<< std::setw(5)		<< "STR"		<< " "
				<< std::setw(5)		<< "SPD"		<< " "
				<< std::setw(5)		<< "DUR"		<< " "
				<< std::setw(5)		<< "POW"		<< " "
				<< std::setw(5)		<< "COMB"		<< " "
				<< std::setw(5)		<< "TOTAL"	<< std::endl;
		console_.write(oss.str().c_str());
	}
	if (verbose)
		database_.write_v(*console_);
	else
		database_.write(*console_);
	{ std::ostringstream oss{};
		oss
			<< std::endl
			<< "Time taken: " << bm.count() << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_write_n() {
	manage_state_write(false);
}

void application_t::manage_state_write_v() {
	manage_state_write(true);
}

void application_t::manage_state_file(bool asc) {
	{ std::ostringstream oss{};
		oss << "Enter output file name." << std::endl;
		console_.write(oss.str().c_str());
	}
	std::string o_file_name{ console_.read_s() };
	console_.clear();

	file_t o_file{ o_file_name.c_str(), std::ios::out | std::ios::trunc };
	o_file.check();

	{ std::ostringstream oss{};
		oss
			<< "Choose input file name:" << std::endl
			<< "1 - SPA_PROJ_003_HEROES_data_1.csv" << std::endl
			<< "2 - SPA_PROJ_003_HEROES_data_2.csv" << std::endl;
		console_.write(oss.str().c_str());
	}
	char option{ console_.read<char>() };
	console_.clear();

	file_t i_file{};
	std::string path{ read_path() };
	if			(option == '1') i_file->open(std::string{ path + csv_file_data_01 }, std::ios::in);
	else if (option == '2') i_file->open(std::string{ path + csv_file_data_02 }, std::ios::in);
	else throw_e("invalid input");
	i_file.check();

	benchmarker_t bm{};
	if (asc) {
		std::queue<std::string> file_queue{};
		std::string line{};
		while (std::getline(*i_file, line))
			file_queue.push(line);
		while (!file_queue.empty()) {
			*o_file << file_queue.front() << std::endl;
			file_queue.pop();
		}
	}
	else {
		std::stack<std::string> file_stack{};
		std::string line{};
		while (std::getline(*i_file, line))
			file_stack.push(line);
		while (!file_stack.empty()) {
			*o_file << file_stack.top() << std::endl;
			file_stack.pop();
		}
	}

	{ std::ostringstream oss{};
		oss
			<< "Data transfered " << (asc ? "ASC" : "DESC") << " into " << o_file_name << " successfully." << std::endl
			<< "Time taken: " << bm.count() << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_file_asc() {
	manage_state_file(true);
}

void application_t::manage_state_file_desc() {
	manage_state_file(false);
}

void application_t::manage_state_process(bool good) {
	if (database_->empty())
		throw_e("database empty");

	{ std::ostringstream oss{};
		oss << "Enter power name." << std::endl;
		console_.write(oss.str().c_str());
	}
	std::string power{ console_.read_s() };
	console_.clear();

	if (!powers_t::valid_power(power))
		throw_e("invalid input");

	{ std::ostringstream oss{};
		oss << "Enter property and operation. (ex. INT += 100)" << std::endl;
		console_.write(oss.str().c_str());
	}
	std::string command{ console_.read_s() };
	console_.clear();

	std::string prop{};
	std::string action{};
	float value{};
	{ std::istringstream iss{ command };
		iss >> prop;
		iss >> action;
		iss >> value;
		if (
			(
				prop != "INT" &&
				prop != "STR" &&
				prop != "SPD" &&
				prop != "DUR" &&
				prop != "POW" &&
				prop != "COM" &&
				prop != "TOTAL"
				) ||
			(
				action != "+=" &&
				action != "*=" &&
				action != "-=" &&
				action != "/="
				) ||
			value == 0
			) throw_e("invalid input");
	}

	benchmarker_t bm{};
	long long time_taken{};

	std::list<hero_t> list{};
	std::copy_if(
		std::begin(*database_), 
		std::end(*database_), 
		std::back_inserter(list), 
		(good ? hero_t::is_good : hero_t::is_bad)
	);

	list.erase(
		std::remove_if(
			std::begin(list), 
			std::end(list), 
			std::bind<bool>(hero_t::no_power, std::placeholders::_1, power)
		),
		std::end(list)
	);

	std::transform(
		std::begin(list), 
		std::end(list), 
		std::begin(list), 
		std::bind<hero_t>(hero_t::transform_prop, std::placeholders::_1, prop, action, value)
	);

	std::reverse(std::begin(list), std::end(list));

	time_taken = bm.count();

	std::copy(std::begin(list), std::end(list), std::ostream_iterator<hero_t>(*console_, "\n"));

	{ std::ostringstream oss{};
		oss
			<< std::endl
			<< "Time taken: " << time_taken << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_process_good() {
	manage_state_process(true);
}

void application_t::manage_state_process_bad() {
	manage_state_process(false);
}

void application_t::manage_state_fight() {
	if (database_->empty())
		throw_e("database empty");

	std::stack<hero_t> hero_stack{};
	std::for_each(
		std::begin(*database_),
		std::end(*database_),
		[&hero_stack](const hero_t& hero) -> void {
			if (!hero_stack.empty() && hero_t::is_bad(hero))
				hero_stack.pop();
			else hero_stack.push(hero);
		}
	);

	if (hero_stack.empty()) { 
		std::ostringstream oss{};
		oss << "Villains won!" << std::endl; 
		console_.write(oss.str().c_str());
	}
	else {
		std::ostringstream oss{};
		oss << "Heroes won!" << std::endl << std::endl;
		console_.write(oss.str().c_str());

		oss.str("");
		while (!hero_stack.empty()) {
			oss << hero_stack.top() << std::endl;
			hero_stack.pop();
		}
		console_.write(oss.str().c_str());
	}

	{ std::ostringstream oss{};
		oss
			<< std::endl
			<< "Simulation successfull." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_stat() {
	if (database_->empty())
		throw_e("database empty");
	
	std::map<std::string, unsigned> power_count{};

	std::for_each(
		std::begin(*database_),
		std::end(*database_),
		[&power_count](hero_t& hero) -> void {
			for (std::size_t i{ 0 }; i < hero.get_powers()->size(); ++i)
				if (hero.get_powers()->at(i))
					power_count[powers_t::power_names_.at(i)]++;
		}
	);

	std::copy(
		std::begin(power_count),
		std::end(power_count),
		std::ostream_iterator<std::pair<std::string, unsigned>>(*console_, "\n")
	);

	{ std::ostringstream oss{};
		oss
			<< std::endl
			<< "Statistics calculated successfully." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_tran() {
	if (database_->empty())
		throw_e("database empty");

	{ std::ostringstream oss{};
		oss 
			<< "UPDATE -A SET [property] [operation] [value]" << std::endl
			<< "\tproperty  -> INT | STR | SPD | DUR | POW | COM | TOTAL" << std::endl
			<< "\toperation -> += | -= | *= | /=" << std::endl
			<< "\tvalue     -> must be != 0" << std::endl
			<< "ROLLBACK" << std::endl
			<< "COMMIT" << std::endl << std::endl;
		console_.write(oss.str().c_str());
	}

	std::string line{};
	std::istringstream iss{};
	std::string command{};

	std::stack<std::vector<hero_t>> stack{};
	stack.push(*database_);

	while (true) {
		line = console_.read_s();
		iss.str(line);
		iss >> command;

		if (command == "COMMIT") {
			*database_ = std::move(stack.top());
			while (!stack.empty()) stack.pop();
			break;
		}

		else if (command == "UPDATE") {
			std::string align{};
			std::string prop{};
			std::string action{};
			float value{};
			iss >> align;
			iss >> command;
			iss >> prop;
			iss >> action;
			iss >> value;

			if (
				(
					prop		!= "INT"		&&
					prop		!= "STR"		&&
					prop		!= "SPD"		&&
					prop		!= "DUR"		&&
					prop		!= "POW"		&&
					prop		!= "COM"		&&
					prop		!= "TOTAL"
				)											||
				(
					action	!= "+="			&&
					action	!= "*="			&&
					action	!= "-="			&&
					action	!= "/="
				)											||
					value		== 0
			)  continue;
			
			std::vector<hero_t> vec{};
			if (align == "-A")
				std::copy(std::begin(stack.top()), std::end(stack.top()), std::back_inserter(vec));
			else continue;

			std::transform(
				std::begin(vec), 
				std::end(vec), 
				std::begin(vec), 
				std::bind<hero_t>(hero_t::transform_prop, std::placeholders::_1, prop, action, value)
			);
			stack.push(vec);
		}

		else if (command == "ROLLBACK" && stack.size() > 1)
			stack.pop();

		iss.clear();
	}

	console_.clear();

	database_.write(*console_);

	{ std::ostringstream oss{};
		oss
			<< std::endl
			<< "Transaction managed successfully." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}