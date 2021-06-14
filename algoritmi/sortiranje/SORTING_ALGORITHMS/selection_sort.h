#pragma once

/* SELECTION SORT:

	void selection_sort(std::vector<int>& vec) {
		for (int i = 0; i < vec.size(); ++i) {
			int comp = i;
			for (int j = i + 1; j < vec.size(); ++j)
				if (predicate(vec[j], vec[comp])) 
					comp = j;
			if (comp != i)
				std::swap(vec[i], vec[comp]);
		}
	}

*/

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void selection_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	for (auto it = begin; it != end; it = std::next(it)) {
		std::iter_swap(it, std::min_element(it, end, predicate));
	}
}