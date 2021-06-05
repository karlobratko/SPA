#pragma once

#include <iostream>
#include <cstdint>
#include <map>

class date_t {
public:
  date_t(std::uint32_t = 1900, std::uint32_t = '\x01', std::uint32_t = 1);

  bool valid() const;

  std::uint32_t get_year() const;
  std::uint32_t get_month() const;
  std::uint32_t get_day() const;

  friend std::istream& operator>>(std::istream&, date_t&);
  friend std::ostream& operator<<(std::ostream&, const date_t&);

private:
  static const std::map<std::uint32_t, const char*> month_names_abbr;

  std::uint32_t year_{};
  std::uint32_t month_{};
  std::uint32_t day_{};
};

