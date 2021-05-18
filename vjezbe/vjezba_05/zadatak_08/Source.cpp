#include <iostream>
#include <stack>
#include <string>
#include <sstream>

int main() {
	std::stack<std::string> stack{};
	std::string command{};
	std::string operation{};
	do {
		std::getline(std::cin, command);
		std::istringstream iss{ command };
		iss >> operation;
		if (operation == "ADD") {
			std::string value{};
			iss >> value;
			stack.push(value);
		}
		if (operation == "UNDO") {
			if (stack.size() != 0)
				stack.pop();
		}
		if (operation == "EXIT") {
			std::stack<std::string> output{};
			while (!stack.empty()) {
				output.push(stack.top());
				stack.pop();
			}
			while (!output.empty()) {
				std::cout << output.top() << std::endl;
				output.pop();
			}
			break;
		}
	} while (true);

	return 0;
}