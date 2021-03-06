#pragma once

#include <fstream>
#include <cstdint>
#include <string>
#include <cstring>

class file_t {
public:
	file_t() = default;
	file_t(const char*, std::ios_base::openmode);

	file_t(const file_t&) = delete;
	file_t(file_t&&) noexcept;

	file_t& operator=(const file_t&) = delete;
	file_t& operator=(file_t&&) noexcept;

	~file_t();

	void is_open() const;
	std::streampos set_position(std::streampos);
	std::streampos set_offset(std::streamoff, std::ios_base::seekdir = std::ios_base::cur);
	std::streampos get_position();
	std::streampos beg();
	std::streampos end();
	void reuse();
	void clear_flags(std::ios_base::iostate = std::ios_base::goodbit);
	std::int64_t size();
	std::string getline(char = '\n');

	std::fstream& operator*();
	std::fstream* operator->();

private:
	std::string path_;
	std::fstream file_;

};