#include "date_t.h"

#include <sstream>
#include <string>
#include <iomanip>

const std::map<std::uint32_t, const char*> date_t::month_names_abbr{
	{ 1,	"Jan" },
	{ 2,	"Feb" },
	{ 3,	"Mar" },
	{ 4,	"Apr" },
	{ 5,	"May" },
	{ 6,	"Jun" },
	{ 7,	"Jul" },
	{ 8,	"Aug" },
	{ 9,	"Sep" },
	{ 10, "Oct" },
	{ 11, "Nov" },
	{ 12, "Dec" },
};

date_t::date_t(std::uint32_t year, std::uint32_t month, std::uint32_t day) :
	year_{ year },
	month_{ month },
	day_{ day } {
}

bool date_t::valid() const {
	return 
		year_ >= 1900 && 
		month_ >= 1 && month_ <= 12 && 
		day_ >= 1 && day_ <= 31;
}

std::uint32_t date_t::get_year() const {
	return year_;
}

std::uint32_t date_t::get_month() const {
	return month_;
}

std::uint32_t date_t::get_day() const {
	return day_;
}

std::istream& operator>>(std::istream& is, date_t& date) {
	std::string month{};
	std::uint32_t day{};
	std::uint32_t year{};
	std::string buff{};

	is >> month >> day; is.get(); is >> year;
	if (is) {
		date.year_ = year;
		date.month_ = std::find_if(
			std::begin(date_t::month_names_abbr),
			std::end(date_t::month_names_abbr),
			[month = month.substr(0, 3)](const std::pair<std::uint32_t, const char*>& pair) {
				return pair.second == month;
			}
		)->first;
		date.day_ = day;
		if (!date.valid())
			is.setstate(std::ios::failbit);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const date_t& date) {
	std::ostringstream oss{};
	oss
		<< date.day_ << " "
		<< date_t::month_names_abbr.at(date.month_) << " "
		<< date.year_;
	if (!oss) os.setstate(oss.rdstate());
	else os << oss.str();
	return os;
}