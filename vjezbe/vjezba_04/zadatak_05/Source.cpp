#include <iostream>
#include <vector>
#include <chrono>

class Benchmarker {
public:
	Benchmarker() : start{ std::chrono::high_resolution_clock::now() } {}
	~Benchmarker() {
		end = std::chrono::high_resolution_clock::now();
		std::cout << "time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
};

int main() {
	std::vector<int> v1{}, v2{};

	{
		Benchmarker bm{};
		for (std::size_t i{ 0 }; i < 100000; ++i)
			v1.push_back(i);
		// push_back je puno brzi
	}

	{
		Benchmarker bm{};
		for (std::size_t i{ 0 }; i < 100000; ++i)
			v2.insert(v2.begin(), i);
		// potrebna je pomicanje svih prethodnih elemenata
	}


	return 0;
}