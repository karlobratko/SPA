#pragma once

#include <iostream>
#include <string>

class console_t {
public:
	console_t() = default;
	~console_t() = default;

	void clear() {
		std::system("CLS");
	}

	void wait() {
		std::cin.get();
	}

	std::string read_s() {
		std::string buff{};
		std::getline(std::cin, buff);
		return buff;
	}

	template <typename T>
	T read() {
		T buff{};
		std::cin >> buff; std::cin.ignore();
		return buff;
	}

	void write(const char* msg) {
		std::cout << msg;
	}

	void message(const char* msg) {
		write(msg); wait(); clear();
	}

	std::ostream& operator*() {
		return std::cout;
	}

};

