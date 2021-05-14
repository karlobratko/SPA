#pragma once

#include <stdexcept>

class file_except_t : public std::exception {
public:
	file_except_t() noexcept : file_except_t{ "file error" } {}
	explicit file_except_t(const char* msg) noexcept { msg_.append(msg); }
	~file_except_t() = default;
	virtual const char* what() const noexcept { return msg_.c_str(); }
private:
	std::string msg_{ "FSTREAM::" };
};