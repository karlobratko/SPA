#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <algorithm>

template <typename F>
auto Compose(F&& f) {
	return[f = std::move(f)](auto&&... args) {
		return f(std::move(args)...);
	};
}

template <typename F1, typename F2, typename... Fs>
auto Compose(F1&& f1, F2&& f2, Fs&&... fs) {
	return Compose(
		[f1 = std::move(f1), f2 = std::move(f2)](auto&&... args) {
		return f2(f1(std::move(args)...));
	},
		std::move<Fs>(fs)...
		);
}

int RandomNumber(int min, int max) {
	static auto device = std::make_unique<std::random_device>();
	static auto generator = std::make_unique<std::mt19937>((*device)());
	return std::uniform_int_distribution<int>(min, max)(*generator);
}

int main() {
	std::vector<int> v;
	v.reserve(100);
	for (std::size_t i{ 0 }; i < v.capacity(); ++i) {
		// v.insert(v.begin(), RandomNumber(1, 100));
		v.push_back(RandomNumber(1, 100));
	}
	
	std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << " "; });
	std::cout << std::endl << std::endl;

	v.resize(50);
	for (auto it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	v.reserve(30); // nothing changes
	for (auto it = v.crbegin(); it != v.crend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	std::vector<int> v2{ v }; // copy constructor
	v.clear();

	std::for_each(v2.begin(), v2.end(), [](int x) { std::cout << x << " "; });
	std::cout << std::endl << std::endl;

	v2.erase(v2.begin(), v2.begin() + 10);
	std::cout << v2.front() << ", " << v2.back() << std::endl;

	for (auto it = v2.begin(); it != v2.end();)
		it = v2.erase(it);
	std::cout << v2.size() << std::endl;

	return 0;
}