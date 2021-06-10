/* MERGE SORT:

	void merge(std::vector<int>& vec, int begin, int mid, int end) {
		int l = begin, r = mid + 1;
		std::size_t left_size = mid - begin + 1;
		std::size_t right_size = end - mid;

		int* left = new int[left_size] {};
		for (std::size_t i = 0; i < left_size; ++i)
			left[i] = vec[l + i];

		int* right = new int[right_size]{};
		for (std::size_t i = 0; i < right_size; ++i)
			right[i] = vec[r + i];

		std::size_t i = 0, j = 0, k = l;
		while (i < left_size && j < right_size) {
			if (left[i] <= right[j]) {
				vec[k] = left[i];
				++i;
			}
			else {
				vec[k] = right[j];
				++j;
			}
			++k;
		}

		while (i < left_size) {
			vec[k] = left[i];
			++i; ++k;
		}
		while (j < right_size) {
			vec[k] = right[j];
			++j; ++k;
		}

	}

	void merge_sort(std::vector<int>& vec, int begin, int end) {
		if (begin < end) {
			int mid = (begin + end) / 2;
			merge_sort(vec, begin, mid);
			merge_sort(vec, mid + 1, end);
			merge(vec, begin, mid, end);
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

template <typename RandomAccessIterator, typename Predicate>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate&& predicate) {
	if (std::distance(begin, end) > 1) {
		auto mid = begin + (std::distance(begin, end) / 2);
		merge_sort(begin, mid, std::forward<Predicate>(predicate));
		merge_sort(mid, end, std::forward<Predicate>(predicate));
		std::inplace_merge(begin, mid, end, std::forward<Predicate>(predicate));
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

	merge_sort(std::begin(vec), std::end(vec), std::less<int>{});
	output(std::begin(vec), std::end(vec));
	std::cout << std::endl;

	test_sorted(std::begin(vec), std::end(vec), std::less<int>{});

	std::cout << std::endl;
	return 0;
}