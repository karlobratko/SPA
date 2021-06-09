/* BUBBLE SORT:

	repeat
    if itemCount <= 1
        return
    hasChanged := false
    decrement itemCount
    repeat with index from 1 to itemCount
        if (item at index) > (item at (index + 1))
            swap (item at index) with (item at (index + 1))
            hasChanged := true
   until hasChanged = false

*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <functional>

template <typename ForwardIterator, typename Distribution, typename Function>
void random_fill(ForwardIterator begin, ForwardIterator end, Distribution distr, Function func) {
  std::generate(begin, end, std::bind<typename std::iterator_traits<ForwardIterator>::value_type>(distr, func));
}

template <typename InputIterator>
void output(InputIterator begin, InputIterator end, std::ostream& os = std::cout, const std::string& delim = " ") {
  std::copy(begin, end, std::ostream_iterator<typename std::iterator_traits<InputIterator>::value_type>(os, delim.c_str()));
}

template <typename RandomAccessIterator, typename Predicate>
void bubble_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate) {
  bool swapped{ true };
  while (begin != end && swapped) {
    end = std::prev(end);
    swapped = false;
    for (auto it = begin; it != end; it = std::next(it)) {
      if (predicate(*std::next(it), *it)) {
        std::iter_swap(std::next(it), it);
        swapped = true;
      }
    }
  }
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

  bubble_sort(std::begin(vec), std::end(vec), std::less<int>{});
  output(std::begin(vec), std::end(vec));
  std::cout << std::endl;

  sorted_test(std::begin(vec), std::end(vec), std::less<int>{});

  std::cout << std::endl;
  return 0;
}