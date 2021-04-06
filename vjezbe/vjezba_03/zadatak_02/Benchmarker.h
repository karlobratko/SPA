#pragma once

#include <iostream>
#include <chrono>

class Benchmarker {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
public:
	Benchmarker()
		: start{ std::chrono::high_resolution_clock::now() } {
	}
	~Benchmarker() {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds diff{
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
		};
		std::cout << "time: " << diff.count() << " ms" << std::endl;
	}
};