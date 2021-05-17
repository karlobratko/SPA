#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <functional>
#include <iomanip>

#include "file_t.h"
#include "console_t.h"
#include "progstate_t.h"
#include "application_except_t.h"
#include "database_t.h"
#include "benchmarker_t.h"

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
	std::string read_state();
	std::string read_path();

	void throw_e(const char*);

	void manage_state_void();
	void manage_state_exit();
	void manage_state_path();
	void manage_state_data();
	void manage_state_write(bool);
	void manage_state_write_n();
	void manage_state_write_v();
	void manage_state_file(bool);
	void manage_state_file_asc();
	void manage_state_file_desc();
	void manage_state_process(bool);
	void manage_state_process_good();
	void manage_state_process_bad();
	void manage_state_fight();
	void manage_state_stat();
	void manage_state_tran();

	std::map<std::string, progstate_t> command_state{
		{ "",						progstate_t::VOID			},
		{ "EXIT",				progstate_t::EXIT			},
		{ "PATH",				progstate_t::PATH			},
		{ "COPY -D",		progstate_t::DATA			},
		{ "WRITE",			progstate_t::WRITE		},
		{ "WRITE -V",		progstate_t::WRITE_V	},
		{ "COPY -F -A",	progstate_t::FILE_A		},
		{ "COPY -F -D",	progstate_t::FILE_D		},
		{ "PROC -G",		progstate_t::PROC_G		},
		{ "PROC -B",		progstate_t::PROC_B		},
		{ "FIGHT",			progstate_t::FIGHT		},
		{ "STAT",				progstate_t::STAT			},
		{ "BEGIN TRAN",	progstate_t::TRAN			},
	};

	std::map<progstate_t, std::function<void()>> state_function{
		{ progstate_t::VOID,		std::bind(&application_t::manage_state_void,					this) },
		{ progstate_t::EXIT,		std::bind(&application_t::manage_state_exit,					this) },
		{ progstate_t::PATH,		std::bind(&application_t::manage_state_path,					this) },
		{ progstate_t::DATA,		std::bind(&application_t::manage_state_data,					this) },
		{ progstate_t::WRITE,		std::bind(&application_t::manage_state_write_n,				this) },
		{ progstate_t::WRITE_V,	std::bind(&application_t::manage_state_write_v,				this) },
		{ progstate_t::FILE_A,	std::bind(&application_t::manage_state_file_asc,			this) },
		{ progstate_t::FILE_D,	std::bind(&application_t::manage_state_file_desc,			this) },
		{ progstate_t::PROC_G,	std::bind(&application_t::manage_state_process_good,	this) },
		{ progstate_t::PROC_B,	std::bind(&application_t::manage_state_process_bad,		this) },
		{ progstate_t::FIGHT,		std::bind(&application_t::manage_state_fight,					this) },
		{ progstate_t::STAT,		std::bind(&application_t::manage_state_stat,					this) },
		{ progstate_t::TRAN,		std::bind(&application_t::manage_state_tran,					this) },
	};

	std::vector<const char*> header_;
	progstate_t program_state_;
	console_t console_;
	database_t database_;
};