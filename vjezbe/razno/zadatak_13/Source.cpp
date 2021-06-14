#include <iostream>

#include "city_t.h"
#include "country_t.h"

int main() {
	country_t c{ "Croatia" };
	c.emplaceCity("Zagreb", 10);
	c.emplaceCity("Cakovec", 10);
	c.emplaceCity("Split", 10);
	std::cout << c.accumulatePplCount() << std::endl;

	return 0;
}