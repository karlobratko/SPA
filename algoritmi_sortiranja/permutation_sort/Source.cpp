/* PERMUTATION SORT:

	while not InOrder(list) do
		nextPermutation(list)
	done

*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <functional>

template <typename InputIterator>
void output(InputIterator begin, InputIterator end, std::ostream& os = std::cout, const std::string& delim = " ") {
	std::copy(begin, end, std::ostream_iterator<typename std::iterator_traits<InputIterator>::value_type>(os, delim.c_str()));
}

template <typename ForwardIterator, typename Function>
void random_fill(ForwardIterator begin, ForwardIterator end, Function function) {
	std::generate(begin, end, std::bind<std::iterator_traits<ForwardIterator>::value_type>(std::uniform_int_distribution<int>{ 0, 100 }, function));
}

template <typename BidirectionalIterator, typename Predicate>
void permutation_sort(BidirectionalIterator begin, BidirectionalIterator end, Predicate predicate) {
	while (std::next_permutation(begin, end, predicate)) {}
}

template <typename ForwardIterator, typename Predicate>
void sorted_test(ForwardIterator begin, ForwardIterator end, Predicate predicate, std::ostream& os = std::cout) {
	os << "sorted: " << std::boolalpha << std::is_sorted(begin, end, predicate) << std::noboolalpha << std::endl;
}

int main() {
	std::vector<int> vec(10);
	random_fill(std::begin(vec), std::end(vec), std::mt19937{ std::_Random_device() });
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	permutation_sort(std::begin(vec), std::end(vec), std::less<int>{});
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	sorted_test(std::begin(vec), std::end(vec), std::less<int>{});

	std::cout << std::endl;
	return 0;
}