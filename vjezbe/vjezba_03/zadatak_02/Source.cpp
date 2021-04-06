#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <ctime>
#include "funkcije_za_sortiranje.h";
#include "Benchmarker.h";
#include "RandomFill.h";

const std::size_t SIZE{ 20000u };
const int MIN{ 1 };
const int MAX{ 1000 };
const std::string FILE_NAME{ "sorted.txt" };

typedef int* NumberPtr;

NumberPtr AllocateArrayMemory(const std::size_t&);
void DeallocateArrayMemory(NumberPtr&);
void PrintArrayToFile(const NumberPtr const, const std::size_t&, const std::string&);

int main() {
	NumberPtr arr{ AllocateArrayMemory(SIZE) };
	RandomFill{ MIN, MAX }(arr, SIZE);
	{
		Benchmarker bm{};
		//bubble_sort(arr, SIZE);
		quick_sort(arr, SIZE);
	}
	try {
		PrintArrayToFile(arr, SIZE, FILE_NAME);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
	}
	DeallocateArrayMemory(arr);
	std::cin.get();
}

NumberPtr AllocateArrayMemory(const std::size_t& len) {
	return new int[len] {};
}

void DeallocateArrayMemory(NumberPtr& arr) {
	delete[] arr;
	arr = nullptr;
}

void PrintArrayToFile(const NumberPtr const arr, const std::size_t& len, const std::string& file_name) {
	std::ofstream file_writer{ file_name };
	if (!file_writer)
		throw std::runtime_error("PRINTARRAYTOFILE::OFSTREAM::could not open file");
	for (std::size_t i{ 0 }; i < len; ++i)
		file_writer << arr[i] << std::endl;
	file_writer.close();
}
