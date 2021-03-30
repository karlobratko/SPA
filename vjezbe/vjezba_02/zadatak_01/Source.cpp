#include <iostream>
#include "Lampa.h"

void PrintLampa(const Lampa&);

int main() {
	Lampa l1{};
	Lampa l2{ "Antifoni" };
	l2.SetProizvodjac("Ikea");
	l2.SetSijaliceCount(1);
	l2.SetSnaga(10);
	std::string s = l2.GetProizvodjac();
	std::cout << s << std::endl;
	PrintLampa(l2);

	return 0;
}

void PrintLampa(const Lampa& lampa) {
	std::cout << lampa << std::endl;
}
