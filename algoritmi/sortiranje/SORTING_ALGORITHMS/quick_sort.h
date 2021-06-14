#pragma once

/* QUICK SORT:

	int partition(std::vector<int>& vec, int begin, int end) {
		int pivot = vec[end];
		int pindex = begin;
		for (int i = begin; i < end; ++i) {
			if (vec[i] <= pivot) {
				std::swap(vec[i], vec[pindex]);
				++pindex;
			}
		}
		std::swap(vec[pindex], vec[end]);
		return pindex;
	}

	void quick_sort(std::vector<int>& vec, int begin, int end) {
		if (begin < end) {
			int partition_point = partition(vec, begin, end);
			quick_sort(vec, begin, partition_point - 1);
			quick_sort(vec, partition_point + 1, end);
		}
	}

*/

template <typename Type>
Type median(const Type& t1, const Type& t2, const Type& t3) {
	if (t1 < t2) {
		if (t2 < t3) return t2;
		else if (t1 < t3) return t3;
		else return t1;
	}
	else {
		if (t1 < t3) return t1;
		else if (t2 < t3) return t3;
		else return t2;
	}
}

template <typename Predicate>
class non_strict_predicate : public std::binary_function<typename Predicate::second_argument_type, typename Predicate::first_argument_type, bool> {
public:
	non_strict_predicate(Predicate predicate) : predicate_{ predicate } {}
	bool operator()(const typename Predicate::second_argument_type& lhs, const typename Predicate::first_argument_type& rhs) const {
		return !predicate_(rhs, lhs);
	}

private:
	Predicate predicate_;
};

template <typename Predicate>
non_strict_predicate<Predicate> non_strict(Predicate predicate) {
	return non_strict_predicate<Predicate>{ predicate };
}

template <typename RandomAccessIterator, typename Predicate = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>>
void quick_sort(RandomAccessIterator begin, RandomAccessIterator end, Predicate predicate = Predicate{}) {
	if ((end - begin) > 1) {
		auto mid = begin + (end - begin) / 2;
		auto pivot = median(*begin, *mid, *std::prev(end));
		auto partition_point1 = std::partition(begin, end, std::bind2nd(predicate, pivot));
		auto partition_point2 = std::partition(partition_point1, end, std::bind2nd(non_strict(predicate), pivot));
		quick_sort(begin, partition_point1, predicate);
		quick_sort(partition_point2, end, predicate);
	}
}