#include "core.h"
#include "bogo_sort.h"
#include "bubble_sort.h"
#include "heap_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "permutation_sort.h"
#include "quick_sort.h"
#include "selection_sort.h"
#include "shell_sort.h"

int main() {
	// PREPARE CONTAINER
	std::vector<int> vec(30);
	random_fill(std::begin(vec), std::end(vec), std::uniform_int_distribution<int>{ -100, 100 });
	output(std::begin(vec), std::end(vec));

	// SORT CONTAINER
	benchmarker_t<std::chrono::microseconds> bm{};
	quick_sort(std::begin(vec), std::end(vec), std::less<int>{});
	std::cout << "time taken: " << bm.count() << " microseconds" << std::endl;

	// TEST IF SORTED
	output(std::begin(vec), std::end(vec));
	sorted_check(std::begin(vec), std::end(vec), std::less<int>{});

	std::cout << std::endl;
	return 0;
}