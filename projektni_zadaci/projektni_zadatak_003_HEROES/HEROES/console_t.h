#pragma once

#include <iostream>
#include <string>

class console_t {
public:
	void clear() { std::system("CLS"); }
	void wait() { std::cin.get(); }
	std::string read_s() { std::string s{};	std::getline(std::cin, s); return s; }
	template <typename T>
	T read() { T t; std::cin >> t; std::cin.ignore(); return t; };
	void write(const char* msg) { std::cout << msg; };
	void message(const char* msg) { write(msg); wait(); clear(); }
	std::ostream& operator*() { return std::cout; }
};
