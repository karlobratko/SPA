#pragma once

/* BOGO SORT:

	while not inOrder(list) do
		shuffle(list)
	done

*/

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void bogo_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	while (!std::is_sorted(begin, end, predicate)) std::shuffle(begin, end, global_rng());
}