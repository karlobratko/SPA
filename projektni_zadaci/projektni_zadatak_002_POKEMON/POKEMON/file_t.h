#pragma once

#include <fstream>
#include <string>

#include "file_access_except_t.h"

class file_t {
public:
	file_t() {};
	file_t(const char* file_name, std::ios::openmode open_mode) 
		: file_{ file_name, open_mode } {
		if (!file_.is_open()) throw file_access_except_t{};
	}
	file_t(const file_t&) = delete;
	file_t(file_t&& other) noexcept : file_{ std::move(other.file_) } {}
	file_t& operator=(const file_t&) = delete;
	file_t& operator=(file_t&& other) noexcept {
		file_ = std::move(other.file_);
		return *this;
	}
	~file_t() { file_.close(); }
	std::fstream* operator->() { return &file_; }
	std::fstream& operator*() { return file_; }
	void reuse() {
		file_.clear();
		file_.seekg(0, std::ios::beg);
	}
	std::string getline() {
		std::string temp{};
		std::getline(file_, temp);
		return temp;
	}
private:
	std::fstream file_;
};