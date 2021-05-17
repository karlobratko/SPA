#pragma once

#include <array>
#include <string>
#include <iostream>

class powers_t {
public:
	powers_t(std::string = "");
	powers_t(const powers_t&);

	std::string get_name() const;

	bool has_power(const std::string&) const;

	static bool valid_power(const std::string&);

	friend std::istream& operator>>(std::istream&, powers_t&);
	friend std::ostream& operator<<(std::ostream&, const powers_t&);

	std::array<bool, 167>* operator->();

	static std::array<std::string, 167> power_names_;

private:
	std::string						name_;
	std::array<bool, 167> flags_{};
};

