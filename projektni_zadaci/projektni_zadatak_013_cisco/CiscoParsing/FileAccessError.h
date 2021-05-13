#pragma once

#include <stdexcept>

class FileAccessError : public std::exception {
public:
	FileAccessError() noexcept = default;
	~FileAccessError() = default;
	virtual const char* what() const noexcept {
		return "FSTREAM::could not access file";
	}
};
