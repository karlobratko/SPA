#pragma once

/* HEAP SORT:

  void shift_down(std::vector<int>& heap, int i, int max) {
    int i_big{}, left{}, right{};
    while (i < max) {
      i_big = i;
      left = i * 2 + 1;
      right = i * 2 + 2;
      if (left < max && heap[left] > heap[i_big]) i_big = left;
      if (right < max && heap[right] > heap[i_big]) i_big = right;
      if (i_big == i) return;
      std::swap(heap[i], heap[i_big]);
      i = i_big;
    }
  }

  void to_heap(std::vector<int>& vec) {
    int i = (vec.size() / 2) - 1;
    while (i >= 0) {
      shift_down(vec, i, vec.size());
      --i;
    }
  }

  void heap_sort(std::vector<int>& vec) {
    to_heap(vec);
    int end = vec.size() - 1;
    while (end > 0) {
      std::swap(vec[0], vec[end]);
      shift_down(vec, 0, end);
      --end;
    }
  }

*/

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void heap_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	std::make_heap(begin, end, predicate);
	std::sort_heap(begin, end, predicate);
}