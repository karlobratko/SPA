#pragma once

#include <chrono>
#include <cstdint>

template <typename _Ratio = std::micro>
class benchmarker_t {
public:
	benchmarker_t() : 
		start_{ std::chrono::high_resolution_clock::now() } {
	};
	std::int64_t count() {
		return std::chrono::duration_cast<std::chrono::duration<std::int64_t, _Ratio>>(
			std::chrono::high_resolution_clock::now() - start_
		).count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_;

};