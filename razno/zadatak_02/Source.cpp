#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>

int main() {
	std::array<int, 100> arr{};
	std::iota(std::begin(arr), std::end(arr), 1);
	auto isPrime = [](int x) -> bool {
		if (x == 1) return false;
		for (std::size_t i{ 2 }; i < std::sqrt(x) + 1; ++i)
			if (x % i == 0)
				return false;
		return true;
	};
	std::copy_if(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, "\n"), isPrime);

	return 0;
}