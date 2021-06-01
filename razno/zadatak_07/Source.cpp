#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <string>

const char* file_name_I{ "song.txt" };
const char* file_name_O{ "reverse.txt" };

int main() {
	try {
		std::fstream file{};
		file.open(file_name_I, std::ios::in);
		std::stack<std::string> stack{};
		if (file.is_open()) {
			std::string temp{};
			while (std::getline(file, temp))
				stack.push(temp);
			file.close();
		}
		else throw std::runtime_error{ "FSTREAM::IFSTREAM::could not open file" };
		file.open(file_name_O, std::ios::out);
		if (file.is_open()) {
			while (!stack.empty()) {
				file << stack.top() << std::endl;
				stack.pop();
			}
			file.close();
		}
		else throw std::runtime_error{ "FSTREAM::OFSTREAM::could not open file" };
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}