#pragma once

#include <string>
#include <vector>
#include <numeric>

#include "city_t.h"

class country_t {
public:
	country_t(std::string name) : name_{ name } {}

	void emplaceCity(std::string name, unsigned ppl_count) {
		cities_.emplace_back(name, ppl_count);
	}

	int accumulatePplCount() const {
		return std::accumulate(std::begin(cities_), std::end(cities_), 0);
	}

private:
	std::string name_;
	std::vector<city_t> cities_;
};

