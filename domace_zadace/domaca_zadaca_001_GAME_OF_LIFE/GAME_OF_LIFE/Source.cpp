#include <iostream>

#include "grid_t.h"

// preferred settings (for best performance)
const std::size_t GRID_SIZE{ 30 };

int main() {
	grid_t grid(GRID_SIZE, GRID_SIZE * 2);
	try {
		// -- RANDOM --
		grid.random_fill();

		// -- LIFE --
		//grid.make_life(GRID_SIZE / 2, GRID_SIZE);

		// -- STILL LIFES -- 
		//grid.make_block(GRID_SIZE / 2 , GRID_SIZE);
		//grid.make_bee_hive(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_loaf(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_boat(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_tub(GRID_SIZE / 2, GRID_SIZE);

		// -- OSCILLATORS --
		//grid.make_blinker(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_toad(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_beacon(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_pulsar(GRID_SIZE / 2 - 8, GRID_SIZE - 8);
		//grid.make_penta_decathlon(GRID_SIZE / 2 - 8, GRID_SIZE - 6);

		// -- METHUSELAHS --
		//grid.make_r_petromino(GRID_SIZE / 2, GRID_SIZE);
		//grid.make_diehard(GRID_SIZE / 2 - 8, GRID_SIZE - 4);
		//grid.make_acorn(GRID_SIZE / 2, GRID_SIZE - 4);

		// -- GUNS --
		//grid.make_gosper_glider_gun(0, 0);

		// -- SWITCH ENGINES --
		//grid.make_switch_engine_01(GRID_SIZE / 2 - 3, GRID_SIZE - 6);
		//grid.make_switch_engine_02(GRID_SIZE / 2 - 3, GRID_SIZE - 3);
	}
	catch (const std::exception& err) {
		std::cout << err.what() << std::endl;
		return 1;
	}

	while (true) {
		std::cout << grid;
		grid.next_gen();
		std::system("CLS");
	}

	return 0;
}