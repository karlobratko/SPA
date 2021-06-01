#pragma once

#include <string>

class city_t {
public:
	city_t(std::string name = "undefined", unsigned ppl_count = 0) :
		name_			{ name			},
		ppl_count_{ ppl_count } {
	}
	friend int operator+(int sum, const city_t& city) {
		return sum + city.ppl_count_;
	}

private:
	std::string name_;
	unsigned ppl_count_;
};

