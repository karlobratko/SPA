/* SHELL SORT:

	template <typename Predicate>
	void shell_sort(std::vector<int>& vec, Predicate predicate) {
		int gap = vec.size() / 2;
		while (gap > 0) {
			for (std::size_t i = gap; i < vec.size(); ++i) {
				int j = i;
				while (j >= gap && predicate(vec[j], vec[j - gap])) {
					std::swap(vec[j], vec[j - gap]);
					j -= gap;
				}
			}
			gap /= 2;
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

template <typename Predicate>
void shell_sort(std::vector<int>& vec, Predicate&& predicate) {
	int gap = vec.size() / 2;
	while (gap > 0) {
		for (std::size_t i = gap; i < vec.size(); ++i) {
			int j = i;
			while (j >= gap && predicate(vec[j], vec[j - gap])) {
				std::swap(vec[j], vec[j - gap]);
				j -= gap;
			}
		}
		gap /= 2;
	}
}

template <typename ForwardIterator, typename Predicate>
void test_sorted(ForwardIterator begin, ForwardIterator end, Predicate&& predicate, std::ostream& os = std::cout) {
	os << "sorted: " << std::boolalpha << std::is_sorted(begin, end, std::forward<Predicate>(predicate)) << std::noboolalpha << std::endl;
}

int main() {
	std::vector<int> vec(30);
	random_fill(std::begin(vec), std::end(vec), std::uniform_int_distribution<int>{ -100, 100 }, std::mt19937{ std::_Random_device() });
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	shell_sort(vec, std::less<int>{});
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	test_sorted(std::begin(vec), std::end(vec), std::less<int>{});

	std::cout << std::endl;
	return 0;
}