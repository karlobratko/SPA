#pragma once

/* MERGE SORT:

	void merge(std::vector<int>& vec, int begin, int mid, int end) {
		std::size_t 
			l_beg = begin, r_beg = mid + 1, 
			l_size = mid - begin + 1, r_size = end - mid;

		int* l_arr = new int[l_size] {};
		for (std::size_t i = 0; i < l_size; ++i)
			l_arr[i] = vec[l_beg + i];

		int* r_arr = new int[r_size] {};
		for (std::size_t i = 0; i < r_size; ++i)
			r_arr[i] = vec[r_beg + i];

		std::size_t i = 0, j = 0, k = l_beg;
		while (i < l_size && j < r_size) {
			if (l_arr[i] <= r_arr[j]) vec[k] = l_arr[i++];
			else vec[k] = r_arr[j++];
			++k;
		}

		while (i < l_size) vec[k++] = l_arr[i++];

		while (j < r_size) vec[k++] = r_arr[j++];

		delete[] l_arr;
		delete[] r_arr;
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

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	if ((end - begin) > 1) {
		auto mid = begin + (end - begin) / 2;
		merge_sort(begin, mid, predicate);
		merge_sort(mid, end, predicate);
		std::inplace_merge(begin, mid, end, predicate);
	}
}