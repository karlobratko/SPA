#pragma once

#include <cstdint>

struct vector2i_t {
	vector2i_t(std::int32_t _x = 0, std::int32_t _y = 0) : x{ _x }, y{ _y } {}
	std::int32_t x, y;
};