#pragma once

#include <random>
#include <cstdint>
#include "random_except_t.h"

class random_t {
public:
	random_t(std::uint_least32_t seed = std::_Random_device()) :
		generator_{ seed } {
	}

	std::int32_t next(std::int32_t min = 0, std::int32_t max = std::numeric_limits<std::int32_t>::max()) {
		if (min < 0 || max < min)
			throw random_except_t{ "INVALIDARGUMENT::min and max must be non negative, max must be greater than min" };
		return std::uniform_int_distribution<std::int32_t>{ min, max }(generator_);
	}
	
	std::double_t next_d(std::double_t min = 0., std::double_t max = 1.) {
		if (min < 0 || max < min)
			throw random_except_t{ "INVALIDARGUMENT::min and max must be non negative, max must be greater than min" };
		return std::uniform_real_distribution<std::double_t>{ min, max }(generator_);
	}

private:
	std::mt19937 generator_;

};

