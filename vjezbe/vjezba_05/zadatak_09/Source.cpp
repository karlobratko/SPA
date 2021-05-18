#include <iostream>
#include <map>
#include <stack>
#include <functional>
#include <sstream>

const std::map<std::string, std::function<int(int, int)>> operations{
		{ "+", [](int x, int y) -> int { return x + y; } },
		{ "-", [](int x, int y) -> int { return x - y; } },
		{ "*", [](int x, int y) -> int { return x * y; } },
		{ "/", [](int x, int y) -> int { return x / y; } },
};

int main() {
	//std::string expression = "2 1 12 3 / - +"; // -1
	//std::string expression = "4 2 5 * + 1 3 2 * + /"; // 2
	std::string expression = "2 3 11 + 5 - *"; // 18
	std::istringstream iss{ expression };
	std::stack<int> stack{};
	std::string value{};

	do {
		iss >> value;
		if (value != "*" && value != "/" && value != "+" && value != "-")
			stack.push(std::stoi(value));
		else {
			int y = stack.top(); stack.pop();
			int x = stack.top(); stack.pop();
			stack.push(operations.at(value)(x, y));
			std::cout << x << " " << value << " " << y << " = " << stack.top() << std::endl;
		}
		if (iss.eof()) break;
	} while (true);

	std::cout << stack.top() << std::endl;

	return 0;
}