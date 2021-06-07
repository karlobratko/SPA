#pragma once

#include <stdexcept>
#include <cstdlib>
#include <vector>

template <typename _Ty>
class matrix_t {
public:
	explicit matrix_t(const std::int32_t& col) : matrix_t{ col, col } {};
	explicit matrix_t(const std::int32_t& col, const std::int32_t& row) :
		col_{ col },
		row_{ row } {
		vec_.reserve(col_* row_);
	}

	void fill(const _Ty& value) {
		std::fill_n(std::back_inserter(vec_), vec_.capacity(), value);
	}

	std::int32_t size() const {
		return vec_.size();
	}

	_Ty& at(const std::int32_t x, const std::int32_t y) {
		if (x < 0 || x > col_ || y < 0 || y > row_) throw std::out_of_range{ "MATRIX_T::location out of range" };
		return vec_.at((y - 1) * col_ + (x - 1));
	}

	const _Ty& at(const std::int32_t x, const std::int32_t y) const {
		if (x < 0 || x > col_ || y < 0 || y > row_) throw std::out_of_range{ "MATRIX_T::location out of range" };
		return vec_.at((y - 1) * col_ + (x - 1));
	}

	friend std::ostream& operator<<(std::ostream& os, const matrix_t<_Ty>& matrix) {
		for (std::int32_t i{ 0 }; i < matrix.size(); ++i) {
			if (i != 0 && i % matrix.col_ == 0) {
				os << std::endl;
			}
			os << matrix.at(i % matrix.col_ + 1, i / matrix.col_ + 1) << " ";
		}
		return os;
	}

private:
	std::vector<_Ty> vec_{};
	std::int32_t col_, row_;

};