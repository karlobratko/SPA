#include <iostream>
#include <stdexcept>

template <typename T>
T Multiply(T a, T b) {
	return a * b;
}

template <typename T>
T Divide(T a, T b) {
	if (b == 0) throw std::invalid_argument("DIVIDE::INVALID_ARGUMENT::second parameterm must not be 0");
	return a / b;
}

double Sqrt(int a) {
	if (a < 0) throw std::invalid_argument("SQRT::INVALID_ARGUMENT::parameter must not be less than 0");
	return std::sqrt(a);
}

int main() {
	try {
		Sqrt(-1);
	}
	catch (const std::invalid_argument& exception) {
		std::cerr << exception.what() << std::endl;
	}
	std::cin.get();
};