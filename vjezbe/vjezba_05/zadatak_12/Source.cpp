#include <iostream>
#include <sstream>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

int main() {
	std::string test1{ "{a{a(a[(a)a]a)a}a}" };
	std::string test2{ "{{(()})()" };
	std::string test3{ "{{}}([]){()}" };
	std::istringstream iss{ test1 };

	std::map<char, char> map{
		{ '{', '}' },
		{ '(', ')' },
		{ '[', ']' }
	};
	std::string l_braces{ "{([" };
	std::string r_braces{ "})]" };
	std::stack<char> stack{};
	char v{};
	do {
		iss >> v;
		if (std::find(std::begin(l_braces), std::end(l_braces), v) != std::end(l_braces)) stack.push(v);
		else if (std::find(std::begin(r_braces), std::end(r_braces), v) != std::end(r_braces)) {
			if (map.at(stack.top()) != v) {
				std::cerr << "invalid braces" << std::endl;
				return 1;
			}
			stack.pop();
		}
	} while (!stack.empty());
	std::cout << "valid braces" << std::endl;

	return 0;
}