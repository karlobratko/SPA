#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>

const char* file_name{ "numbers.txt" };

template <typename _Cont>
void WriteToConsole(_Cont& cont) {
	std::copy(std::begin(cont), std::end(cont), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

int main() {
	try {
		std::fstream file{};
		std::list<int> list{};
		file.open(file_name, std::ios::in);
		if (file.is_open()) {
			std::copy(std::istream_iterator<int>(file), std::istream_iterator<int>(), std::back_inserter(list));
			file.close();
		}
		else throw std::runtime_error("FSTREAM::IFSTREAM::could not open file");

		auto isEven = [](int x) -> bool { return x % 2 == 0; };
		list.erase(
			std::remove_if(std::begin(list), std::end(list), isEven),
			std::end(list)
		);
		WriteToConsole(list);

		std::transform(std::begin(list), std::end(list), std::begin(list), std::bind<int>(std::multiplies<int>{}, 10, std::placeholders::_1));
		WriteToConsole(list);

		std::vector<int> vector{ std::rbegin(list), std::rend(list) };
		WriteToConsole(vector);

		std::transform(std::begin(vector), std::end(vector), std::begin(vector), std::bind<int>(std::divides<int>{}, std::placeholders::_1, 5));
		WriteToConsole(vector);

		std::queue<int> queue{};
		auto copy = [&queue](int x) -> void { queue.push(x); };
		std::for_each(std::begin(vector), std::end(vector), copy);
		
		std::cout << "queue: ";
		while (!queue.empty()) {
			std::cout << queue.front() << " ";
			queue.pop();
		}
		std::cout << std::endl;
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}
	return 0;
}