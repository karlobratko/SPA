/* SELECTION SORT:
 
	template <typename Predicate>
	void selection_sort(std::vector<int>& vec, Predicate predicate) {
		int comp{};
		for (int i = 0; i < vec.size(); ++i) {
			comp = i;
			for (int j = i + 1; j < vec.size(); ++j) {
				if (predicate(vec[j], vec[comp])) comp = j;
			}
			if (comp != i)
				std::swap(vec[i], vec[comp]);
		}
	}

*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <functional>

template <typename ForwardIterator, typename Distribution, typename Generator>
void random_fill(ForwardIterator begin, ForwardIterator end, Distribution&& distr, Generator&& gen) {
	std::generate(begin, end, std::bind<typename std::iterator_traits<ForwardIterator>::value_type>(std::forward<Distribution>(distr), std::forward<Generator>(gen)));
}

template <typename InputIterator>
void output(InputIterator begin, InputIterator end, std::ostream& os = std::cout, const char* delim = " ") {
	std::copy(begin, end, std::ostream_iterator<typename std::iterator_traits<InputIterator>::value_type>(os, delim));
}

template <typename ForwardIterator, typename Predicate>
void selection_sort(ForwardIterator begin, ForwardIterator end, Predicate&& predicate) {
	for (auto it = begin; it != end; it = std::next(it)) {
		std::iter_swap(it, std::min_element(it, end, std::forward<Predicate>(predicate)));
	}
}

template <typename ForwardIterator, typename Predicate>
void sorted_test(ForwardIterator begin, ForwardIterator end, Predicate&& predicate, std::ostream& os = std::cout) {
	os << "sorted: " << std::boolalpha << std::is_sorted(begin, end, std::forward<Predicate>(predicate)) << std::noboolalpha << std::endl;
}

int main() {
	std::vector<int> vec(30);
	random_fill(std::begin(vec), std::end(vec), std::uniform_int_distribution<int>{ -100, 100 }, std::mt19937{ std::_Random_device() });
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	selection_sort(std::begin(vec), std::end(vec), std::less<int>{});
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	sorted_test(std::begin(vec), std::end(vec), std::less<int>{});

	std::cout << std::endl;
	return 0;
}