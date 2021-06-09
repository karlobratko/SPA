/* BOGO SORT:
 
	while not inOrder(list) do
		shuffle(list)
	done

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <functional>

template <typename InputIterator>
void output(InputIterator begin, InputIterator end, std::ostream& os = std::cout, const std::string& delim = " ") {
	std::copy(begin, end, std::ostream_iterator<typename std::iterator_traits<InputIterator>::value_type>(os, delim.c_str()));
}

template <typename RandomAccessIterator, typename Predicate>
void bogo_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate) {
	std::mt19937 generator{ std::_Random_device() };
	while (!std::is_sorted(begin, end, predicate)) std::shuffle(begin, end, generator);
}

template <typename ForwardIterator, typename Predicate>
void sorted_test(ForwardIterator begin, ForwardIterator end, Predicate predicate, std::ostream& os = std::cout) {
	os << "sorted: " << std::boolalpha << std::is_sorted(begin, end, predicate) << std::noboolalpha << std::endl;
}

int main() {
	std::vector<int> vec{}; vec.reserve(5);
	std::generate_n(std::back_inserter(vec), vec.capacity(), std::bind<int>(std::uniform_int_distribution<int>{ 0, 100 }, std::mt19937{ std::_Random_device() }));
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	bogo_sort(std::begin(vec), std::end(vec), std::less<int>{});
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	sorted_test(std::begin(vec), std::end(vec), std::less<int>{});

	std::cout << std::endl;
	return 0;
}