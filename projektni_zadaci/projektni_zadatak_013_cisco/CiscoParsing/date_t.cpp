#include "date_t.h"

#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

std::string titlecase(const std::string& s) {
  std::string r{};
  if (s.size()) {
    std::transform(std::begin(s), std::end(s), std::back_inserter(r), std::tolower);
    r.at(0) = std::toupper(s.at(0));
  }
  return r;
}

const char* date_t::month_names_abbr[12]{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

date_t::date_t(unsigned year, unsigned month, unsigned day) : 
  year_   { year  }, 
  month_  { month }, 
  day_    { day   } {
}

bool date_t::valid() const {
  return year_ > 0 && month_ >= 1 && month_ <= 12 && day_ > 0;
}

bool date_t::operator==(const date_t& rhs) {
  return year_ == rhs.year_ && month_ == rhs.month_ && day_ == rhs.day_;
}

bool date_t::operator<(const date_t& rhs)
{
  return year_ != rhs.year_
    ? year_ < rhs.year_
    : month_ != rhs.month_
      ? month_ < rhs.month_
      : day_ < rhs.day_;
}

bool date_t::operator<=(const date_t& rhs)
{
  return *this == rhs || *this < rhs;
}

std::istream& operator>>(std::istream& is, date_t& date) {
  unsigned year{}, day{};
  std::string month{};
  is 
    >> day 
    >> month 
    >> year;
  if (is) {
    date.year_ = year;
    date.month_ = std::find(
      std::begin(date_t::month_names_abbr), 
      std::end(date_t::month_names_abbr), 
      titlecase(month.substr(0, 3))
    ) - date_t::month_names_abbr + 1;
    date.day_ = day;
    if (!date.valid())
      is.setstate(std::ios::failbit);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const date_t& date) {
  std::ostringstream oss{};
  oss
    << std::setw(2) << date.day_                                 << " "
    << std::setw(3) << date_t::month_names_abbr[date.month_ - 1] << " "
    << std::setw(4) << date.year_;
  if (!oss) os.setstate(oss.rdstate());
  else os << oss.str();
  return os;
}
