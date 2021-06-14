#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
#include <memory>
#include <functional>

const std::size_t capacity{ 100u };
const int min{ 100 };
const int max{ 200 };

int rand_num(int min, int max) {
	static auto device = std::make_unique<std::random_device>();
	static auto generator = std::make_unique<std::mt19937>((*device)());
	return std::uniform_int_distribution<int>{ min, max }(*generator);
}

int main() {
	std::vector<int> vector{};
	vector.reserve(capacity);

	// generiranje slucajnih brojeva
	std::generate_n(std::back_inserter(vector), capacity, std::bind<int>(rand_num, min, max));

	// ispis vectora
	std::cout << "vector numbers: ";
	std::copy(std::begin(vector), std::end(vector), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl << std::endl;

	// algoritam zadatka
	std::stack<int> stack{};
	for (int num : vector) {
		while (stack.size() > 0 && stack.top() <= num) stack.pop();
		stack.push(num);
	}

	// ispis stacka
	std::cout << "stack numbers: ";
	while (!stack.empty()) {
		std::cout << stack.top() << " ";
		stack.pop();
	}

	std::cout << std::endl << std::endl;
	return 0;
}