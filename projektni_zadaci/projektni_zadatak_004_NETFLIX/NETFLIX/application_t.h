#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <functional>
#include "appstate_t.h" 
#include "application_except_t.h"
#include "file_t.h"
#include "console_t.h"
#include "database_t.h"
#include "benchmarker_t.h"
#include "random_t.h"

class application_t {
public:
	explicit application_t(std::vector<const char*>);
	application_t(const application_t&) = delete;
	application_t(application_t&&) noexcept = delete;
	application_t& operator=(const application_t&) = delete;
	application_t& operator=(application_t&&) noexcept = delete;
	~application_t() = default;

	bool is_running() const;
	void header();

	void determine_state();
	void manage_state() const;

	void catch_e(const std::exception&);

private:
	static constexpr const char* type_file_name{ "type.dat" };
	static constexpr const char* path_file_name{ "path.dat" };
	static constexpr const char* csv_file_data{ "SPA_PROJ_004_NETFLIX_data.csv" };
	static constexpr const char* json_output_file{ "data.json" };

	std::string read_state();
	std::string read_bin(const char*);
	std::string read_type();
	std::string read_path();

	void throw_e(const char*);

	void manage_state_void();
	void manage_state_help();
	void manage_state_exit();
	void manage_state_choose(const char);
	void manage_state_choose_m();
	void manage_state_choose_s();
	void manage_state_choose_a();
	void manage_state_path();
	void manage_state_read();
	void manage_state_write_c();
	void manage_state_write_f();

	std::map<std::string, appstate_t> command_state{
		{ "", appstate_t::VOID },
		{ "?", appstate_t::HELP },
		{ "exit", appstate_t::EXIT },
		{ "type -m", appstate_t::SETTYPE_M },
		{ "type -s", appstate_t::SETTYPE_S },
		{ "type -a", appstate_t::SETTYPE_A },
		{ "path", appstate_t::SETPATH },
		{ "read", appstate_t::READDATA },
		{ "write -c", appstate_t::WRITE_C },
		{ "write -f", appstate_t::WRITE_F },
	};

	std::map<appstate_t, std::function<void()>> state_method{
		{ appstate_t::VOID, std::bind(&application_t::manage_state_void, this) },
		{ appstate_t::HELP, std::bind(&application_t::manage_state_help, this) },
		{ appstate_t::EXIT, std::bind(&application_t::manage_state_exit, this) },
		{ appstate_t::SETTYPE_M, std::bind(&application_t::manage_state_choose_m, this) },
		{ appstate_t::SETTYPE_S, std::bind(&application_t::manage_state_choose_s, this) },
		{ appstate_t::SETTYPE_A, std::bind(&application_t::manage_state_choose_a, this) },
		{ appstate_t::SETPATH, std::bind(&application_t::manage_state_path, this) },
		{ appstate_t::READDATA, std::bind(&application_t::manage_state_read, this) },
		{ appstate_t::WRITE_C, std::bind(&application_t::manage_state_write_c, this) },
		{ appstate_t::WRITE_F, std::bind(&application_t::manage_state_write_f, this) },
	};

	std::vector <const char*> header_;
	appstate_t app_state_;
	console_t console_;
	database_t database_;

};

