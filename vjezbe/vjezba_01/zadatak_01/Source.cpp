#include <iostream>
#include "Point.h"

int main() {
	Point p{ 4, 1 };
	p.Display();
	std::cout << p << std::endl;
	std::cout << p.to_string() << std::endl;
	return 0;
}