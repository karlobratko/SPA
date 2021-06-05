#include "application_t.h"

application_t::application_t(std::vector<const char*> header) :
	header_		{ header						},
	app_state_{ appstate_t::VOID	} {
}

bool application_t::is_running() const {
	return app_state_ != appstate_t::EXIT;
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
		app_state_ = command_state.at(read_state());
	}
	catch (...) {
		throw_e("INVALIDCOMMAND::invalid input");
	}
}

void application_t::manage_state() const {
	state_method.at(app_state_)();
}

void application_t::catch_e(const std::exception& err) {
	console_.write(err.what());
	console_.message("\nPress any key to continue...");
}

std::string application_t::read_state() {
	std::string app_state(console_.read_s());
	console_.clear();
	return app_state.empty() ? "" : app_state;
}

std::string application_t::read_bin(const char* file_name) {
	file_t file{ file_name, std::ios_base::in | std::ios_base::binary };
	file.is_open();
	std::int64_t path_len{ file.size() };
	char* path_cstr{ new char[path_len] {} };
	file->read(reinterpret_cast<char*>(path_cstr), path_len);
	std::string str(path_cstr, path_len);
	delete[] path_cstr;
	return str;
}

std::string application_t::read_type() {
	return read_bin(type_file_name);
}

std::string application_t::read_path() {
	std::string path{ read_bin(path_file_name) };
	path.append("\\");
	return path;
}

void application_t::throw_e(const char* msg) {
	app_state_ = appstate_t::VOID;
	console_.clear();
	throw application_except_t{ msg };
}

void application_t::manage_state_void() {}

void application_t::manage_state_help() {
	{ std::ostringstream oss{};
	oss
		<< "exit      - exit application" << std::endl
		<< "type -m   - choose movies" << std::endl
		<< "type -s   - choose series" << std::endl
		<< "type -a   - choose all" << std::endl
		<< "path      - set path to .csv file" << std::endl
		<< "read      - read data from .csv file" << std::endl
		<< "write -c  - write data to console" << std::endl
		<< "write -f  - write data to .json file" << std::endl
		<< std::endl;
	console_.write(oss.str().c_str());
	}
}

void application_t::manage_state_exit() {
	app_state_ = appstate_t::EXIT;
}

void application_t::manage_state_choose(const char c) {
	std::string type{};
	if (c == 'm') type = "Movie";
	else if (c == 's') type = "TV Show";
	else if (c == 'a') type = "All";

	file_t file{ type_file_name, std::ios_base::out | std::ios_base::binary };
	file.is_open();
	file->write(type.c_str(), type.size());

	{ std::ostringstream oss{};
		oss
			<< "Media type saved successfully." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_choose_m() {
	manage_state_choose('m');
}

void application_t::manage_state_choose_s() {
	manage_state_choose('s');
}

void application_t::manage_state_choose_a() {
	manage_state_choose('a');
}

void application_t::manage_state_path() {
	{ std::ostringstream oss{};
		oss << ".csv file path: ";
		console_.write(oss.str().c_str());
	}
	std::string path{ console_.read_s() };
	console_.clear();

	file_t file{ path_file_name, std::ios_base::out | std::ios_base::binary };
	file.is_open();
	file->write(path.c_str(), path.size());

	{ std::ostringstream oss{};
		oss
			<< "Path saved successfully." << std::endl
			<< "Press any key to continue..." << std::endl;
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_read() {
	benchmarker_t<std::micro> bm{};
	std::string path{ read_path() };
	std::string type{ read_type() };

	if (type != "Movie" && type != "TV Show" && type != "All")
		throw_e("invalid type value");

	file_t file{ std::string{ path + csv_file_data }.c_str(), std::ios_base::in };
	file.is_open();
	file.getline();
	database_.read_data(*file, type);

	{ std::ostringstream oss{};
		oss
			<< "Data transfered successfully." << std::endl
			<< "Time taken: " << bm.count() << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_write_c() {
	benchmarker_t<std::micro> bm{};
	database_.write_data(*console_);
	{ std::ostringstream oss{};
		oss
			<< std::endl
			<< std::endl
			<< "Data written successfully." << std::endl
			<< "Time taken: " << bm.count() << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}

void application_t::manage_state_write_f() {
	benchmarker_t<std::micro> bm{};
	file_t file{ json_output_file, std::ios_base::out | std::ios_base::trunc };
	file.is_open();
	database_.write_data(*file);
	{ std::ostringstream oss{};
		oss
			<< "Data written successfully." << std::endl
			<< "Time taken: " << bm.count() << " microseconds." << std::endl
			<< "Press any key to continue...";
		console_.message(oss.str().c_str());
	}
}
