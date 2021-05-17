#pragma once

#include <chrono>

class benchmarker_t {
public:
	benchmarker_t() : start_{ std::chrono::high_resolution_clock::now() } {}
	long long count() {
		end_ = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_, end_;
};