#include <iostream>
#include <vector>
#include <limits>
#include <cstdint>
#include <iterator>
#include <thread>
#include <chrono>
#include <random>
#include "grid_t.h"

template <typename _Period>
void sleep(const std::size_t& time) {
	std::this_thread::sleep_for(std::chrono::duration<std::int64_t, _Period>(time));
}

void console_clear() {
	std::system("CLS");
}

void info() {
	std::cout
		<< "grid size: 23 * 20" << std::endl
		<< "x: [1, 23]" << std::endl
		<< "y: [1, 20]" << std::endl
		<< std::endl
		<< "Press any key to continue...";
	std::cin.get();
	console_clear();
}

vector2i_t input() {
	vector2i_t vec{};
	std::cout << "x coordinate: ";
	std::cin >> vec.x;
	std::cout << "y coordinate: ";
	std::cin >> vec.y;
	console_clear();
	return vec;
}

int main() {
	try {
		grid_t grid{ 23, 20 };
		grid.init_grid();

		grid.make_obstacle({ 10, 1 });
		grid.make_obstacle({ 10, 2 });
		grid.make_obstacle({ 10, 3 });
		grid.make_obstacle({ 10, 4 });
		grid.make_obstacle({ 10, 5 });
		grid.make_obstacle({ 10, 6 });

		std::cout << "SOURCE" << std::endl;
		grid.set_src(input());


		std::cout << "DESTINATION" << std::endl;
		grid.set_dst(input(), 88); // 79, 88

		std::vector<vector2i_t> path = grid.calculate_path();

		for (std::size_t i{ 0 }; i < path.size(); ++i) {
			vector2i_t vertex{ path.at(i) };
			grid.update(vertex, 254);
			grid.draw(std::cout);
			sleep<std::milli>(100);
			if (i == path.size() - 1) break;
			grid.update(vertex, 250);
			console_clear();
		}
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	std::cout << std::endl;
	return 0;
}