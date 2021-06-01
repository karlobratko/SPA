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
	static constexpr const char* path_file_name{ "path.dat" };
	static constexpr const char* csv_file_data_01{ "SPA_PROJ_004_NETFLIX_data.csv" };

	std::string read_state();
	std::string read_path();

	void throw_e(const char*);

	void manage_state_void();
	void manage_state_exit();

	std::map<std::string, appstate_t> command_state{
		{ "", appstate_t::VOID },
		{ "EXIT", appstate_t::EXIT },
	};

	std::map<appstate_t, std::function<void()>> state_method{
		{ appstate_t::VOID, std::bind(&application_t::manage_state_void, this) },
		{ appstate_t::EXIT, std::bind(&application_t::manage_state_exit, this) },
	};

	std::vector <const char*> header_;
	appstate_t app_state_;
	console_t console_;

};

