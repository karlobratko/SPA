#pragma once

#include <vector>
#include "multimedia_t.h"

class database_t {
public:
	database_t() = default;

	void read_data(std::istream&, const std::string&);
	void write_data(std::ostream&);

private:
	std::vector<multimedia_t> data_{};

};

