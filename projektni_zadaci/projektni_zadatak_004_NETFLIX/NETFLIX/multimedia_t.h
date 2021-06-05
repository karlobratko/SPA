#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "date_t.h"

class multimedia_t {
public:
	multimedia_t() = default;
	multimedia_t(const multimedia_t&) = default;

	std::string get_type() const;

	friend std::istream& operator>>(std::istream&, multimedia_t&);
	friend std::ostream& operator<<(std::ostream&, const multimedia_t&);

private:

	static const std::map<std::uint8_t, std::string> country_key;
	static const std::map<std::uint8_t, std::string> rating_key;
	static const std::map<std::uint8_t, std::string> genre_key;

	std::uint64_t id_{};
	bool type_{};
	std::string title_{};
	std::vector<std::string> director_{};
	std::vector<std::string> cast_{};
	std::vector<std::uint8_t> country_{};
	date_t date_{};
	std::uint16_t release_{};
	std::vector<std::uint8_t> rating_{};
	std::string duration_{};
	std::vector<std::uint8_t> genre_{};
	std::string description_{};

};

