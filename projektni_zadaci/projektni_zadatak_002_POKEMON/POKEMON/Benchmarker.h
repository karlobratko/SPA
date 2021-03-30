#pragma once

#include <chrono>
#include <ostream>

class Benchmarker {
public:
	Benchmarker() : start{ std::chrono::high_resolution_clock::now() } {}
	long long TimeTaken() {
		end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
};