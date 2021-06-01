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
		throw_e("invalid input");
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
	{ std::ostringstream oss{};
		oss
			<< "EXIT - exit application" << std::endl
			<< std::endl;
		console_.write(oss.str().c_str());
	}
	std::string app_state(console_.read_s());
	console_.clear();
	return app_state.empty() ? "" : app_state;
}

void application_t::throw_e(const char* msg) {
	app_state_ = appstate_t::VOID;
	console_.clear();
	throw application_except_t{ msg };
}

void application_t::manage_state_void() {}

void application_t::manage_state_exit() {
	app_state_ = appstate_t::EXIT;
}