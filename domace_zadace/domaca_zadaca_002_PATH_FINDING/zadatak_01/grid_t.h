#pragma once

#include <cstdlib>
#include "matrix_t.h"
#include "vector2i_t.h"

template <bool path = false>
class grid_t {
public:
	typedef unsigned char uchar_t;

	grid_t(std::size_t col, std::size_t row)
		: matrix_{ col, row } {
	}

	void init_grid(const uchar_t c = default_grid_char) {
		settings.grid_char = c;
		matrix_.fill(c);
	}

	void set_src(const vector2i_t& loc, const uchar_t c = default_cur_char) {
		settings.cur_char = c;
		cur_ = loc;
		matrix_.at(loc.x, loc.y) = c;
	}

	void set_dst(const vector2i_t& loc, const uchar_t c = default_dst_char) {
		settings.dst_char = c;
		dst_ = loc;
		matrix_.at(loc.x, loc.y) = c;
	}

	void update() {
		static bool flag{};
		temp_ = cur_;
		if (flag) {
			if (cur_.x != dst_.x) {
				if (cur_.x - dst_.x < 0) ++cur_.x;
				else --cur_.x;
			}
			else if (cur_.y != dst_.y) {
				if (cur_.y - dst_.y < 0) ++cur_.y;
				else --cur_.y;
			}
		}
		else {
			if (cur_.y != dst_.y) {
				if (cur_.y - dst_.y < 0) ++cur_.y;
				else --cur_.y;
			}
			else if (cur_.x != dst_.x) {
				if (cur_.x - dst_.x < 0) ++cur_.x;
				else --cur_.x;
			}
		}
		flag = !flag;
	}

	void render() {
		if (!path)
			matrix_.at(temp_.x, temp_.y) = settings.grid_char;
		matrix_.at(cur_.x, cur_.y) = settings.cur_char;
	}

	bool dst_found() const {
		if (temp_.x == dst_.x && temp_.y == dst_.y) return true;
		return false;
	}

	void draw(std::ostream& os) const {
		os << matrix_;
	}

	friend std::ostream& operator<<(std::ostream& os, const grid_t& grid) {
		os << grid.matrix_;
		return os;
	}

private:
	static constexpr uchar_t default_grid_char = 250;
	static constexpr uchar_t default_cur_char = 254;
	static constexpr uchar_t default_dst_char = 32;

	matrix_t<uchar_t> matrix_;

	vector2i_t cur_{};
	vector2i_t temp_{};
	vector2i_t dst_{};

	struct settings_t {
		uchar_t grid_char;
		uchar_t cur_char;
		uchar_t dst_char;
	} settings{};

};