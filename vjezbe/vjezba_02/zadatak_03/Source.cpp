#include <iostream>
#include <array>
#include <algorithm>

void InitArr(std::array<int, 100>& arr) {
	for (std::size_t i{ 0 }; i < arr.size(); ++i)
		arr[i] = i + 1;
}

bool IsPrime(int p_Num) {
	for (int i{ 2 }; i <= p_Num / 2; ++i)
		if (p_Num % i == 0) return false;
	return p_Num != 1;
}

int main() {
	std::array<int, 100> arr{};
	InitArr(arr);
	std::reverse(arr.begin(), arr.end());
	std::for_each(
		arr.begin(), 
		arr.end(), 
		[](int i) -> void {
			if (IsPrime(i)) {
				std::cout << i << std::endl;
			}	
		}
	);
	return 0;
}