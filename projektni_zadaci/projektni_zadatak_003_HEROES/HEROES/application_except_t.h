#pragma once

#include <stdexcept>

class application_except_t : public std::exception {
public:
	application_except_t() noexcept : application_except_t{ "application error" } {}
	explicit application_except_t(const char* msg) noexcept { msg_.append(msg); }
	~application_except_t() = default;
	virtual const char* what() const noexcept { return msg_.c_str(); }
private:
	std::string msg_{ "APPLICATION::" };
};