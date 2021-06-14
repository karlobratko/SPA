#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>

inline std::mt19937& global_rng() {
	thread_local std::mt19937 rng{ std::_Random_device() };
	return rng;
}

template <typename Duration>
class benchmarker_t {
public:
	benchmarker_t() : start_{ std::chrono::high_resolution_clock::now() } {};
	std::uint64_t count() const {
		return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - start_).count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

template <typename ForwardIterator, typename Distribution>
void random_fill(ForwardIterator begin, ForwardIterator end, Distribution distr) {
	std::generate(begin, end, std::bind<typename std::iterator_traits<ForwardIterator>::value_type>(distr, global_rng()));
}

template <typename InputIterator>
void output(InputIterator begin, InputIterator end, std::ostream& os = std::cout, const char* delim = " ") {
	std::copy(begin, end, std::ostream_iterator<typename std::iterator_traits<InputIterator>::value_type>(os, delim));
	os << std::endl;
}

template <typename ForwardIterator, typename Predicate>
void sorted_check(ForwardIterator begin, ForwardIterator end, Predicate predicate, std::ostream& os = std::cout) {
	os << "sorted: " << std::boolalpha << std::is_sorted(begin, end, predicate) << std::noboolalpha << std::endl;
}