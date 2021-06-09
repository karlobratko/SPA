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

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <functional>

template <typename ForwardIterator, typename Distribution, typename Generator>
void random_fill(ForwardIterator begin, ForwardIterator end, Distribution distr, Generator gen) {
  std::generate(begin, end, std::bind<typename std::iterator_traits<ForwardIterator>::value_type>(distr, gen));
}

template <typename InputIterator>
void output(InputIterator begin, InputIterator end, std::ostream& os = std::cout, const char* delim = " ") {
  std::copy(begin, end, std::ostream_iterator<typename std::iterator_traits<InputIterator>::value_type>(os, delim));
}

template <typename RandomAccessIterator, typename Predicate>
void heap_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate) {
  std::make_heap(begin, end, predicate);
  std::sort_heap(begin, end, predicate);
}

template <typename ForwardIterator, typename Predicate>
void sorted_test(ForwardIterator begin, ForwardIterator end, Predicate predicate, std::ostream& os = std::cout) {
  os << "sorted: " << std::boolalpha << std::is_sorted(begin, end, predicate) << std::noboolalpha << std::endl;
}

int main() {
  std::vector<int> vec(30);
  random_fill(std::begin(vec), std::end(vec), std::uniform_int_distribution<int>{ -100, 100 }, std::mt19937{ std::_Random_device() });
  output(std::begin(vec), std::end(vec));
  std::cout << std::endl;

  heap_sort(std::begin(vec), std::end(vec), std::less<int>{});
  output(std::begin(vec), std::end(vec));
  std::cout << std::endl;

  sorted_test(std::begin(vec), std::end(vec), std::less<int>{});

  std::cout << std::endl;
  return 0;
}