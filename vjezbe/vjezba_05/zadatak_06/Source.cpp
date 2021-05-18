#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>

int main() {
	std::vector<int> nums(10);
	std::iota(std::begin(nums), std::end(nums), 1);
	//std::copy(std::begin(nums), std::end(nums), std::ostream_iterator<int>(std::cout, "\n"));

	std::stack<int, std::vector<int>> st{ nums };
	
	while (!st.empty()) {
		std::cout << st.top() << std::endl;
		st.pop();
	}

	return 0;
}