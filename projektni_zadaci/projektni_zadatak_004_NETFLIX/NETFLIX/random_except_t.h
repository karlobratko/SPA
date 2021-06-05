#pragma once

#include "except_t.h"

class random_except_t : public except_t {
public:
	random_except_t(const char* msg = default_msg) noexcept :
		except_t{ std::string{ base }.append(msg).c_str() } {
	}
	virtual ~random_except_t() = default;
	virtual const char* what() const noexcept override {
		return except_t::what();
	}

private:
	static constexpr const char* base{ "RANDOM::" };
	static constexpr const char* default_msg{ "random generator error" };

};