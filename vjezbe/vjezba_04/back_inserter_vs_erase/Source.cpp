#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <chrono>

const std::size_t size = 100000;

class Benchmarker {
public:
	Benchmarker() : start_{ std::chrono::high_resolution_clock::now() } {}
	~Benchmarker() {
		end_ = std::chrono::high_resolution_clock::now();
		std::cout 
			<< "time taken: " 
			<< std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count() 
			<< " us" << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_, end_;
};

template <typename T, typename F>
std::vector<T> Filter_01(F predicate, const std::vector<T>& vec) {
	std::vector<T> res(vec.size());
	typename std::vector<T>::const_iterator it = std::copy_if(
		std::begin(vec),
		std::end(vec),
		std::begin(res),
		predicate
	);
	res.erase(it, res.end());
	return res;
}

template <typename T, typename F>
std::vector<T> Filter_02(F predicate, std::vector<T>& vec) {
	std::vector<T> res{};
	std::copy_if(
		std::begin(vec),
		std::end(vec),
		std::back_inserter(vec),
		predicate
	);
	return res;
}

int main() {
	std::vector<int> vec(size);
	std::iota(std::begin(vec), std::end(vec), 1);
	// std::for_each(std::begin(vec), std::begin(vec), [](const int& x) -> void { std::cout << x << std::endl; });

	{
		Benchmarker bm{};
		std::vector<int> res(vec.size());
		std::vector<int>::const_iterator it = std::copy_if(
			std::begin(vec),
			std::end(vec),
			std::begin(res),
			[](const int& x) -> bool {
				return x % 2 == 0;
			}
		);
		res.erase(it, res.end());
	}

	{
		Benchmarker bm{};
		std::vector<int> res{};
		res.reserve(size);
		std::copy_if(
			std::begin(vec),
			std::end(vec),
			std::back_inserter(vec),
			[](const int& x) -> bool {
				return x % 2 == 0;
			}
		);
	}

	return 0;
}