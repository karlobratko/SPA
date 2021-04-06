#pragma once

#include <memory>
#include <random>

class RandomFill {
private:
	static std::unique_ptr<std::random_device> device_;
	static std::unique_ptr<std::mt19937> generator_;
	int min_, max_;
public:
	RandomFill(int min = 0, int max = 100)
		: min_{ min }, max_{ max } {
	}
	void operator()(int* const arr, const std::size_t& len) {
		std::uniform_int_distribution<int> distribution{ min_, max_ };
		for (std::size_t i{ 0 }; i < len; ++i)
			arr[i] = distribution(*generator_);
	}
};
std::unique_ptr<std::random_device> RandomFill::device_ = std::make_unique<std::random_device>();
std::unique_ptr<std::mt19937> RandomFill::generator_ = std::make_unique<std::mt19937>((*device_)());