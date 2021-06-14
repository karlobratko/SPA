#pragma once

/* SHELL SORT:
 
	void shell_sort(std::vector<int>& vec) {
		int gap = vec.size() / 2;
		while (gap > 0) {
			for (std::size_t i = gap; i < vec.size(); ++i) {
				int j = i;
				while (j >= gap && vec[j] < vec[j - gap]) {
					std::swap(vec[j], vec[j - gap]);
					j -= gap;
				}
			}
			gap /= 2;
		}
	}

*/

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void shell_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	std::size_t gap = (end - begin) / 2;
	while (gap > 0) {
		for (auto it = begin + gap; it != end; it = std::next(it)) {
			auto it2 = it;
			while ((it2 - begin) >= gap && predicate(*it2, *std::prev(it2, gap))) {
				std::iter_swap(it2, std::prev(it2, gap));
				it2 = std::prev(it2, gap);
			}
		}
		gap /= 2;
	}
}