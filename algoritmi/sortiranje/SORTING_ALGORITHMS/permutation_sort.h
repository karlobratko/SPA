#pragma once

/* PERMUTATION SORT:

	while not InOrder(list) do
		nextPermutation(list)
	done

*/

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void permutation_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	while (std::next_permutation(begin, end, predicate)) {};
}