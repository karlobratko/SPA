#pragma once

#include "except_t.h"

class application_except_t : public except_t {
public:
	application_except_t(const char* msg = default_msg) noexcept :
		except_t{ std::string{ base }.append(msg).c_str() } {
	}
	virtual ~application_except_t() = default;
	virtual const char* what() const noexcept override { return except_t::what(); }

private:
	static constexpr const char* base{ "APPLICATION::" };
	static constexpr const char* default_msg{ "application error" };

};
