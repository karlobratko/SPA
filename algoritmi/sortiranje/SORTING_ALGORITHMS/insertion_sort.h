#pragma once

/* INSERTION SORT:

  void insertion_sort(std::vector<int>& vec) {
    for (std::size_t i = 1; i < vec.size(); ++i) {
      int j = i - 1;
      while (j >= 0 && vec[j] > vec[j + 1]) {
        std::swap(vec[j], vec[j + 1]);
        --j;
      }
    }
  }

*/

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void insertion_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	for (auto it = std::next(begin); it != end; it = std::next(it)) {
		std::rotate(std::upper_bound(begin, it, *it, predicate), it, std::next(it));
	}
}