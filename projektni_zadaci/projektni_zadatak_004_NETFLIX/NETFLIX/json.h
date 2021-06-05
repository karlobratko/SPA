#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <cstdint>

void stringify_key(std::ostream& oss, const std::string& key, const std::int64_t depth) {
	oss << std::string(depth, '\t') << "\"" << key << "\": ";
}

template <typename _Type, typename _Function>
void stringify_vec(std::ostream& oss, const std::string& key, _Function function, const std::vector<_Type>& vec, const std::int64_t depth) {
	stringify_key(oss, key, depth);
	if (vec.empty())
		oss << "null,\n";
	else {
		oss << "[\n";
		std::for_each(
			std::begin(vec),
			std::end(vec),
			[&oss, i = 0, &vec, &function](const _Type& value) mutable -> void {
			function(oss, value, i, vec.size());
			++i;
		}
		);
		oss << std::string(depth, '\t') << "],\n";
	}
}

void stringify_integer(std::ostream& oss, const std::string& key,  const std::uint64_t& value, const std::int64_t depth) {
	stringify_key(oss, key, depth);
	oss << value << ",\n";
}

void stringify_string(std::ostream& oss, const std::string& key, const std::string& value, const std::int64_t depth) {
	stringify_key(oss, key, depth);
	oss << "\"" << value << "\",\n";
}

void stringify_date(std::ostream& oss, const date_t& date, const std::int64_t depth) {
	stringify_key(oss, "date", depth);
	oss
		<< "{\n"
		<< std::string(depth + 1, '\t') << "\"year\": " << date.get_year() << ",\n"
		<< std::string(depth + 1, '\t') << "\"month\": " << date.get_month() << ",\n"
		<< std::string(depth + 1, '\t') << "\"day\": " << date.get_day() << "\n"
		<< std::string(depth, '\t') << "},\n";
}