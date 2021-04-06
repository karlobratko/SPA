#pragma once
#include <chrono>
#include <iostream>

class Benchmarker {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
public:
	Benchmarker()
		: start{ std::chrono::high_resolution_clock::now() } {
	}
	~Benchmarker() {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds diff{
			std::chrono::duration_cast<std::chrono::microseconds>(end - start)
		};
		std::cout << "time: " << diff.count() << std::endl;
	}
};