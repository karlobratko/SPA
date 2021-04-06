#include <iostream>
#include <vector>

typedef int Number;

// vector raste za 50%

int main() {
	std::vector<Number> v{};
	v.reserve(500);

	int counter{};
	std::size_t capacity{ v.capacity() };
	for (std::size_t i{ 0 }; i < 500; ++i) {
			v.push_back(i);
		if (v.capacity() != capacity) {
			++counter;
			capacity = v.capacity();
			std::cout << "cap: " << capacity << ", size: " << v.size() << std::endl;
		}
	}
	std::cout << "rastao: " << counter << std::endl;

	return 0;
}