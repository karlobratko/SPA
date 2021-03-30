#include <iostream>
#include <stdexcept>
#include "Rectangle.h"

int main() {
	try {
		Rectangle rect{ 10, 10 };
		std::cout << rect << std::endl;
	}
	catch (const std::exception& except) {
		std::cout << except.what() << std::endl;
	}

	std::cin.get();
}