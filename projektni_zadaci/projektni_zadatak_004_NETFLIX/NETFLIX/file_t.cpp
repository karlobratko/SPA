#include "file_t.h"
#include "file_except_t.h"

file_t::file_t(const char* path, std::ios_base::openmode openmode) :
	path_{ path },
	file_{ path, openmode } {
}

file_t::file_t(file_t&& other) noexcept :
	file_{ std::move(other.file_) } {
}

file_t::~file_t() {
	file_.close();
}

file_t& file_t::operator=(file_t&& other) noexcept {
	file_ = std::move(other.file_);
	return *this;
}

void file_t::is_open() const {
	std::string msg{ "INVALIDPATH::could not open file, path: " };
	msg.append(path_);
	if (!file_) throw file_except_t{ msg.c_str() };
}

std::streampos file_t::set_position(std::streampos position) {
	std::streampos pos = get_position();
	file_.seekg(position);
	return pos;
}

std::streampos file_t::set_offset(std::streamoff offset, std::ios_base::seekdir direction) {
	std::streampos pos = get_position();
	file_.seekg(offset, direction);
	return pos;
}

std::streampos file_t::get_position() {
	return file_.tellg();
}

std::streampos file_t::beg() {
	return set_offset(0, std::ios_base::beg);
}

std::streampos file_t::end() {
	return set_offset(0, std::ios_base::end);
}

void file_t::reuse() {
	clear_flags();
	beg();
}

void file_t::clear_flags(std::ios_base::iostate flag) {
	file_.clear(flag);
}

std::int64_t file_t::size() {
	std::streampos pos{ end() };
	std::int64_t size{ get_position() };
	file_.seekg(pos);
	return size;
}

std::string file_t::getline(char delim) {
	std::string buff{};
	std::getline(file_, buff, delim);
	return buff;
}

std::fstream& file_t::operator*() {
	return file_;
}

std::fstream* file_t::operator->() {
	return &file_;
}