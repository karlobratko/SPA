#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <chrono>
#include <functional>

#include "file_t.h"

std::vector<const char*> program_header{
	"_____________________                              _____________________",
	"`-._:  .:'   `:::  .:\\           |\\__/|           /::  .:'   `:::  .:.-'",
	"    \\      :          \\          |:   |          /         :       /",
	"     \\     ::    .     `-_______/ ::   \\_______-'   .      ::   . /",
	"      |  :   :: ::'  :   :: ::'  :   :: ::'      :: ::'  :   :: :|",
	"      |     ;::         ;::         ;::         ;::         ;::  |",
	"      |  .:'   `:::  .:'   `:::  .:'   `:::  .:'   `:::  .:'   `:|",
	"      /     :           :           :           :           :    \\",
	"     /______::_____     ::    .     ::    .     ::   _____._::____\\",
	"                   `----._:: ::'  :   :: ::'  _.----'",
	"                          `--.       ;::  .--'",
	"                              `-. .:'  .-'",
	"                                 \\    /",
	"                                  \\  /",
	"                                   \\/"
};

enum class progstate_t {
	EXIT = 0,
	VOID,
	SIZE
};

class hero_t {};

class database_t {
public:
	database_t() = default;
	std::vector<hero_t>* operator->() {
		return &data;
	}

private:
	std::vector<hero_t> data{};
};

class console_t {
public:
	void clear() { std::system("CLS"); }
	void wait() { std::cin.get(); }
	std::string read_s() { std::string s{};	std::getline(std::cin, s); return s; }
	template <typename T>
	T read() { T t; std::cin >> t; std::cin.ignore(); return t;	};
	void write(const char* msg) { std::cout << msg; };
	void message(const char* msg) { write(msg); wait(); clear(); }
	std::ostream& operator*() { return std::cout;	}
};

class application_t {
public:
	application_t(std::vector<const char*> header) :
		header_{ header },
		program_state_{ progstate_t::VOID } {}
	bool is_running() { return program_state_ != progstate_t::EXIT; }
	void header() {
		std::copy(
			std::begin(header_), 
			std::end(header_), 
			std::ostream_iterator<const char*>(*console_, "\n")
		);
	}
	void determine_state() { program_state_ = command_state.at(read_state()); }
	void manage_state() { state_function.at(program_state_)(); }
private:
	std::string read_state() {
		std::ostringstream oss{};
		oss
			<< "EXIT - exit application" << std::endl;
		console_.write(oss.str().c_str());
		std::string program_state(console_.read_s());
		console_.clear();
		return program_state;
	}

	static void manage_state_exit() {
		char exit{};
	}
	
	static std::map<std::string, progstate_t> command_state;
	static std::map<progstate_t, std::function<void()>> state_function;

	std::vector<const char*> header_;
	progstate_t program_state_;
	console_t console_;
	database_t database_;
};

std::map<std::string, progstate_t> application_t::command_state{
	{ "EXIT", progstate_t::EXIT },
};

void fun() {}

std::map<progstate_t, std::function<void(void)>> application_t::state_function{
	{ progstate_t::EXIT, application_t::manage_state_exit },
};

int main() {
	application_t application{ program_header };
	application.header();

	/*do {
		try {
			application.determine_state();
			application.manage_state();
		}
		catch (const std::exception&) {

		}
	} while (application.is_running());*/


	return 0;
}