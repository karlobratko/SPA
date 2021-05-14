#pragma once

#include <fstream>
#include <string>

#include "file_except_t.h"

class file_t{
public:
	file_t(const char* file_name, std::ios::openmode open_mode) : file_{ file_name, open_mode } {}
	file_t(const file_t&) = delete;
	file_t(file_t&& other) noexcept : file_{ std::move(other.file_) } {}
	file_t& operator=(const file_t&) = delete;
	file_t& operator=(file_t&& other) noexcept { file_ = std::move(other.file_); return *this; }
	~file_t() { file_.close(); }
	void check() const { if (!file_.is_open()) throw file_except_t{ "could not access file" }; }
	void beg() { file_.seekg(0, std::ios::beg); }
	void end() { file_.seekg(0, std::ios::end); }
	void reuse_r() { file_.clear(); beg(); }
	std::size_t size() { end(); std::size_t size{ static_cast<std::size_t>(file_.tellg()) }; beg(); return size; }
	std::string getline() { std::string s{}; std::getline(file_, s); return s; }
	std::fstream& operator*() { return file_; }
	std::fstream* operator->() { return &file_; }
private:
	std::fstream file_;
};