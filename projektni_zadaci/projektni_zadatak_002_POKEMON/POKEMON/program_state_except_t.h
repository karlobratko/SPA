#pragma once

#include <stdexcept>

class program_state_except_t : public std::exception {
public:
	program_state_except_t() noexcept = default;
	~program_state_except_t() = default;
	virtual const char* what() const noexcept {
		return "PROGRAMSTATE::invalid input value";
	}
};