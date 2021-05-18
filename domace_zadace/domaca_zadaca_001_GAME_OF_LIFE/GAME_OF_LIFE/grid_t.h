#pragma once

#include <iostream>
#include <vector>

class grid_t {
public:
	grid_t(std::size_t);
	grid_t(std::size_t, std::size_t);

	void make_life							(std::size_t, std::size_t);
	void make_block							(std::size_t, std::size_t);
	void make_bee_hive					(std::size_t, std::size_t);
	void make_loaf							(std::size_t, std::size_t);
	void make_boat							(std::size_t, std::size_t);
	void make_tub								(std::size_t, std::size_t);
	void make_blinker						(std::size_t, std::size_t);
	void make_toad							(std::size_t, std::size_t);
	void make_beacon						(std::size_t, std::size_t);
	void make_pulsar						(std::size_t, std::size_t);
	void make_penta_decathlon		(std::size_t, std::size_t);
	void make_r_petromino				(std::size_t, std::size_t);
	void make_diehard						(std::size_t, std::size_t);
	void make_acorn							(std::size_t, std::size_t);
	void make_gosper_glider_gun	(std::size_t, std::size_t);
	void make_switch_engine_01	(std::size_t, std::size_t);
	void make_switch_engine_02	(std::size_t, std::size_t);

	std::vector<bool>::iterator begin();
	std::vector<bool>::iterator end();

	void random_fill();
	bool cell(std::size_t, std::size_t) const;
	void next_gen();

	std::vector<bool>* operator->();
	const std::vector<bool>* operator->() const;

	friend std::ostream& operator<<(std::ostream&, const grid_t&);

private:
	void init_coordinates(std::size_t&, std::size_t&);

	std::size_t row_;
	std::size_t col_;
	std::vector<bool> grid_;
};

