#pragma once

#include <vector>

#include "hero_t.h"
#include "powers_t.h"

class database_t {
public:
	database_t() = default;

	void read_heroes(std::istream&);
	void read_powers(std::istream&);

	void combine();

	void write	(std::ostream&);
	void write_v(std::ostream&);

	std::vector<hero_t>* operator->();
	std::vector<hero_t>& operator*();

private:
	std::vector<hero_t> heroes_;
	std::vector<powers_t> powers_;
};

