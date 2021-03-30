#include <iostream>
#include <fstream>
#include <stdexcept>
#include <random>
#include <memory>
#include "Benchmarker.h"
#include "Point.h"

const std::size_t LEN{ 100000 };

PointPtr AllocatePointMemory(const std::size_t& len) {
	return new Point[len];
}

void DeallocatePointMemory(PointPtr& ptr) {
	delete[] ptr;
	ptr = nullptr;
}

void InputData(PointPtr const points, const std::size_t& len) {
	for (std::size_t i{ 0 }; i < len; ++i)
		points[i].Initialize(i, i);
}

void PrintData(const PointPtr const points, const std::size_t& len) {
	for (std::size_t i{ 0 }; i < len; ++i)
		std::cout << points[i] << std::endl;
}

void OutputDataToFile(const PointPtr const points, const std::size_t& len) {
	std::ofstream file_writer{ "points.txt" };
	if (!file_writer)
		throw std::runtime_error("OUTPUTDATATOFILE::OFSTREAM::could not open file");
	for (std::size_t i{ 0 }; i < len; ++i)
		file_writer << points[i] << std::endl;
	file_writer.close();
}

int main() {	
	{
		Benchmarker bm{};
		PointPtr points{ AllocatePointMemory(LEN) };
		InputData(points, LEN);
		//PrintData(points, LEN);
		OutputDataToFile(points, LEN);
		DeallocatePointMemory(points);
	}
	std::cin.get();
}