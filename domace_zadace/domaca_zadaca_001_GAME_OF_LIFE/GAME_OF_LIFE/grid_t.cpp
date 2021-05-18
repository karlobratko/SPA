#include "grid_t.h"

#include <algorithm>
#include <functional>
#include <random>

typedef unsigned char uchar8_t;
const uchar8_t CELL_OUT{ 254 };

grid_t::grid_t(std::size_t len) :
	grid_t{ len, len } {
}

grid_t::grid_t(std::size_t row_len, std::size_t col_len) :
	row_	{ row_len },
	col_	{ col_len },
	grid_	( (row_ + 1) * (col_ + 1), false ) {
}

void grid_t::make_life(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 1 || x >= col_ - 1)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	init_coordinates(y, x);
	grid_.at(col_ * y + x) = true;
}

void grid_t::make_block(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 2 || x >= col_ - 2)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 0);
	make_life(y + 0, x + 1);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 1);
}

void grid_t::make_bee_hive(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 4)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 0, x + 2);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 3);
	make_life(y + 2, x + 1);
	make_life(y + 2, x + 2);
}

void grid_t::make_loaf(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 4 || x >= col_ - 4)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 0, x + 2);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 3);
	make_life(y + 2, x + 1);
	make_life(y + 2, x + 3);
	make_life(y + 3, x + 2);
}

void grid_t::make_boat(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 3)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 0);
	make_life(y + 0, x + 1);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 2);
	make_life(y + 2, x + 1);
}

void grid_t::make_tub(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 3)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 2);
	make_life(y + 2, x + 1);
}

void grid_t::make_blinker(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 3)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 1, x + 1);
	make_life(y + 2, x + 1);
}

void grid_t::make_toad(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 4 || x >= col_ - 4)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 0, x + 2);
	make_life(y + 0, x + 3);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 1);
	make_life(y + 1, x + 2);
}

void grid_t::make_beacon(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 4 || x >= col_ - 4)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_block(y + 0, x + 0);
	make_block(y + 2, x + 2);
}

void grid_t::make_pulsar(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 15 || x >= col_ - 15)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_blinker(y + 3, x + 0);
	make_blinker(y + 3, x + 5);
	make_blinker(y + 3, x + 7);
	make_blinker(y + 3, x + 12);
	make_blinker(y + 9, x + 0);
	make_blinker(y + 9, x + 5);
	make_blinker(y + 9, x + 7);
	make_blinker(y + 9, x + 12);
	make_life(y + 1, x + 3);
	make_life(y + 1, x + 4);
	make_life(y + 1, x + 5);
	make_life(y + 6, x + 3);
	make_life(y + 6, x + 4);
	make_life(y + 6, x + 5);
	make_life(y + 8, x + 3);
	make_life(y + 8, x + 4);
	make_life(y + 8, x + 5);
	make_life(y + 13, x + 3);
	make_life(y + 13, x + 4);
	make_life(y + 13, x + 5);
	make_life(y + 1, x + 9);
	make_life(y + 1, x + 10);
	make_life(y + 1, x + 11);
	make_life(y + 6, x + 9);
	make_life(y + 6, x + 10);
	make_life(y + 6, x + 11);
	make_life(y + 8, x + 9);
	make_life(y + 8, x + 10);
	make_life(y + 8, x + 11);
	make_life(y + 13, x + 9);
	make_life(y + 13, x + 10);
	make_life(y + 13, x + 11);
}

void grid_t::make_penta_decathlon(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 16 || x >= col_ - 9)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 3, x + 4);
	make_life(y + 4, x + 4);
	make_life(y + 5, x + 3);
	make_life(y + 5, x + 5);
	make_life(y + 6, x + 4);
	make_life(y + 7, x + 4);
	make_life(y + 8, x + 4);
	make_life(y + 9, x + 4);
	make_life(y + 10, x + 3);
	make_life(y + 10, x + 5);
	make_life(y + 11, x + 4);
	make_life(y + 12, x + 4);
}

void grid_t::make_r_petromino(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 3)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 0, x + 2);
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 1);
	make_life(y + 2, x + 1);
}

void grid_t::make_diehard(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 8)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 1, x + 0);
	make_life(y + 1, x + 1);
	make_life(y + 2, x + 1);
	make_life(y + 0, x + 6);
	make_life(y + 2, x + 5);
	make_life(y + 2, x + 6);
	make_life(y + 2, x + 7);
}

void grid_t::make_acorn(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 3 || x >= col_ - 7)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 1);
	make_life(y + 2, x + 0);
	make_life(y + 2, x + 1);
	make_life(y + 1, x + 3);
	make_life(y + 2, x + 4);
	make_life(y + 2, x + 5);
	make_life(y + 2, x + 6);
}

void grid_t::make_gosper_glider_gun(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 9 || x >= col_ - 35)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_block(y + 4, x + 0);
	make_block(y + 2, x + 34);
	make_life(y + 2, x + 12);
	make_life(y + 2, x + 13);
	make_life(y + 3, x + 11);
	make_life(y + 3, x + 15);
	make_life(y + 4, x + 10);
	make_life(y + 4, x + 16);
	make_life(y + 5, x + 10);
	make_life(y + 5, x + 14);
	make_life(y + 5, x + 14);
	make_life(y + 5, x + 16);
	make_life(y + 5, x + 17);
	make_life(y + 6, x + 10);
	make_life(y + 6, x + 16);
	make_life(y + 7, x + 15);
	make_life(y + 7, x + 11);
	make_life(y + 8, x + 12);
	make_life(y + 8, x + 13);

	make_block(x + 2, y + 20);
	make_block(x + 3, y + 20);
	make_life(y + 1, x + 22);
	make_life(y + 1, x + 24);
	make_life(y + 0, x + 24);
	make_life(y + 5, x + 22);
	make_life(y + 5, x + 24);
	make_life(y + 6, x + 24);
}

void grid_t::make_switch_engine_01(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 6 || x >= col_ - 8)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 5, x + 0);
	make_life(y + 4, x + 2);
	make_life(y + 5, x + 2);
	make_life(y + 1, x + 4);
	make_life(y + 2, x + 4);
	make_life(y + 3, x + 4);
	make_life(y + 0, x + 6);
	make_life(y + 1, x + 6);
	make_life(y + 2, x + 6);
	make_life(y + 1, x + 7);
}

void grid_t::make_switch_engine_02(std::size_t y, std::size_t x) {
	if (y < 0 || x < 0 || y >= row_ - 5 || x >= col_ - 5)
		throw std::invalid_argument{ "GRID_T::value out of boundries" };
	make_life(y + 0, x + 0);
	make_life(y + 0, x + 1);
	make_life(y + 0, x + 2);
	make_life(y + 0, x + 4);
	make_life(y + 1, x + 0);
	make_life(y + 2, x + 3);
	make_life(y + 2, x + 4);
	make_life(y + 3, x + 1);
	make_life(y + 3, x + 2);
	make_life(y + 3, x + 4);
	make_life(y + 4, x + 0);
	make_life(y + 4, x + 2);
	make_life(y + 4, x + 4);
}

std::vector<bool>::iterator grid_t::begin() {
	return grid_.begin();
}

std::vector<bool>::iterator grid_t::end() {
	return grid_.end();
}

void grid_t::random_fill() {
	std::mt19937 generator{ std::_Random_device() };
	for (std::size_t y = 1; y < row_; ++y) {
		for (std::size_t x = 1; x < col_; ++x)
			if (std::uniform_int_distribution<int>{ 0, 100 }(generator) <= 25)
				grid_.at(y * col_ + x) = true;
	}
}

bool grid_t::cell(std::size_t y, std::size_t x) const {
	return grid_.at(y * col_ + x);
}

void grid_t::next_gen() {
	grid_t grid_copy{ row_, col_ };
	std::copy(std::begin(grid_), std::end(grid_), std::begin(grid_copy));

	for (std::size_t y = 1; y < row_; ++y) {
		for (std::size_t x = 1; x < col_; ++x) {
			int life_cells{
				grid_copy.cell(y - 1, x - 1) + grid_copy.cell(y - 1, x + 0) + grid_copy.cell(y - 1, x + 1) +
				grid_copy.cell(y + 0, x - 1) +							0								+ grid_copy.cell(y + 0, x + 1) +
				grid_copy.cell(y + 1, x - 1) + grid_copy.cell(y + 1, x + 0) + grid_copy.cell(y + 1, x + 1)
			};

			if			(life_cells <		2)	{ grid_.at(y * col_ + x) = false; }
			else if (life_cells ==	3)	{ grid_.at(y * col_ + x) = true;	}
			else if (life_cells >		3)	{ grid_.at(y * col_ + x) = false; }
		}
	}
}

std::vector<bool>* grid_t::operator->() {
	return &grid_;
}

const std::vector<bool>* grid_t::operator->() const {
	return &grid_;
}

void grid_t::init_coordinates(std::size_t& y, std::size_t& x) {
	++y; ++x;
}

std::ostream& operator<<(std::ostream& os, const grid_t& grid) {
	for (std::size_t y = 1; y < grid.row_; ++y) {
		for (std::size_t x = 1; x < grid.col_; ++x) {
			if (grid.cell(y, x)) os << " " << CELL_OUT;
			else os << "  ";
		}
		os << "\n";
	}
	return os;
}