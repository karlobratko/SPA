#include <iostream>
#include <random>
#include <memory>
#include <fstream>
#include <stdexcept>
#include "Student.h"

const int MIN{ 1961 };
const int MAX{ 1997 };
const std::size_t LEN{ 3 };
const std::string FILE_NAME{ "students.txt" };

int RandomNumber() {
	static std::unique_ptr<std::random_device> device_ = std::make_unique<std::random_device>();
	static std::unique_ptr<std::mt19937> generator_ = std::make_unique<std::mt19937>((*device_)());
	static std::uniform_int_distribution<int> distribution{ MIN, MAX };
	return distribution(*generator_);
}

template <typename T>
T* AllocateArrayMemory(const std::size_t& len) {
	return new T[len]{};
}

template <typename T>
void DeallocateArrayMemory(T*& x) {
	delete[] x;
	x = nullptr;
}

void InputArrayData(StudentPtr const arr, const std::size_t& len) {
	for (std::size_t i{ 0 }; i < len; ++i) {
		std::cout << "name: ";
		std::cin >> arr[i].name_;
		std::cout << "surname: ";
		std::cin >> arr[i].surname_;
		arr[i].birth_date_ = RandomNumber();
		std::cout << std::endl;
	}
}

void OutputArrayData(const StudentPtr const arr, const std::size_t& len, const std::string& file_name) {
	std::ofstream file_writer{ file_name };
	if (!file_writer)
		throw std::runtime_error("OUTPUTARRAYDATA::OFSTREAM::could not open file");
	for (std::size_t i{ 0 }; i < len; ++i)
		file_writer << arr[i] << std::endl;
	file_writer.close();
}

int main() {
	StudentPtr arr{ AllocateArrayMemory<Student>(LEN) };
	InputArrayData(arr, LEN);
	OutputArrayData(arr, LEN, FILE_NAME);
	DeallocateArrayMemory<Student>(arr);
	std::cin.get();
}