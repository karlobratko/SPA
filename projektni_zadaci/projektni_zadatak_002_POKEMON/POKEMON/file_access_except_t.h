#pragma once

#include <stdexcept>

class file_access_except_t : public std::exception {
public:
	file_access_except_t() noexcept = default;
	~file_access_except_t() = default;
	virtual const char* what() const noexcept {
		return "FSTREAM::could not access file";
	}
};