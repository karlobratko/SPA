#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <memory>
#include <functional>
#include <list>

std::string rand_str(std::size_t size) {
	static auto device = std::make_unique<std::random_device>();
	std::mt19937 generator{ (*device)() };
	std::uniform_int_distribution<int> distribution{ 65, 122 };
	std::string s{};
	s.reserve(size);
	std::generate_n(
		std::back_inserter(s),
		size,
		std::bind<char>(distribution, generator)
	);
	return s;
};

class Benchmarker {
public:
	Benchmarker() : start_{ std::chrono::high_resolution_clock::now() } {}
	~Benchmarker() {
		end_ = std::chrono::high_resolution_clock::now();
		std::cout << "time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count() << std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_, end_;
};

int main() {	
	std::list<std::string> list{};
	std::generate_n(std::back_inserter(list), 100000, std::bind<std::string>(rand_str, 30));
	std::copy(std::begin(list), std::end(list), std::ostream_iterator<std::string>(std::cout, "\n"));

	return 0;
}