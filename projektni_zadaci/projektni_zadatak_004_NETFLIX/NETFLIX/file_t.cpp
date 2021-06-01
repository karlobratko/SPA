#include "file_t.h"
#include "file_except_t.h"

file_t::file_t(const char* path, std::ios_base::openmode openmode) :
	path_{ path						},
	file_{ path, openmode } {
}

file_t::file_t(file_t&& other) noexcept : 
	file_{ std::move(other.file_) } {
}

file_t& file_t::operator=(file_t&& other) noexcept {
	file_ = std::move(other.file_);
	return *this;
}

void file_t::is_open() const {
	std::string msg{ "INVALIDARGUMENT::could not open file, path: " };
	msg.append(path_);
	if (!file_) throw file_except_t{ msg.c_str() };
}

std::streampos file_t::position(std::streamoff offset, std::ios_base::seekdir direction) {
	std::streampos pos = file_.tellg();
	file_.seekg(offset, direction);
	return pos;
}

std::streampos file_t::beg() {
	return position(0, std::ios_base::beg);
}

std::streampos file_t::end() {
	return position(0, std::ios_base::end);
}

void file_t::reuse() {
	file_.clear();
	beg();
}

std::int64_t file_t::size() {
	std::streampos pos = end();
	std::int64_t size{ file_.tellg() };
	file_.seekg(pos, std::ios_base::beg);
	return size;
}

std::string file_t::getline(char delim) {
	std::string buff{};
	std::getline(file_, buff, delim);
	return buff;
}