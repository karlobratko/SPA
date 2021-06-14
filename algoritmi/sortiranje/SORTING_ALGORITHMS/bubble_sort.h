#pragma once

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

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void bubble_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	bool swapped{ true };
	while (begin != end && swapped) {
		end = std::prev(end);
		swapped = false;
		for (auto it = begin; it != end; it = std::next(it)) {
			if (predicate(*std::next(it), *it)) {
				std::iter_swap(it, std::next(it));
				swapped = true;
			}
		}
	}
}