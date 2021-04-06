#include <iostream>
#include "Vector.h"

int main() {
	Vector v(10, "HELLOOOO");
	for (unsigned i = 0; i < v.Size(); i++)
		std::cout << v.At(i) << std::endl;

	return 0;
}