#pragma once

#include <iostream>

class date_t {
public:
	date_t(unsigned = 0, unsigned = 0, unsigned = 0);
	bool valid() const;
	bool operator==(const date_t&);
	bool operator<(const date_t&);
	bool operator<=(const date_t&);

	friend std::istream& operator>>(std::istream&, date_t&);
	friend std::ostream& operator<<(std::ostream&, const date_t&);

private:
	static const char* month_names_abbr[12];
	unsigned year_, month_, day_;
};

