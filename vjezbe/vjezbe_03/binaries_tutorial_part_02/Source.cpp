#include <fstream>
#include <iostream>

struct Student {
	char name[20];
	int age;
	float gpa;
};

int main() {
	const std::size_t len{ 3 };
	Student arr[len]{
		{ "Hank", 48, 3.54 },
		{ "Tom", 25, 2.60 },
		{ "Rick", 22, 3.90 }
	};

	std::fstream f{ "records.dat", std::ios::out | std::ios::binary };
	if (f.is_open()) {
		f.write(reinterpret_cast<char*>(arr), sizeof(Student) * len);
		f.close();
	}
	else {
		std::cerr << "MAIN::FSTREAM::could not open file" << std::endl;
		return 1;
	}

	Student new_arr[len]{};
	f.open("records.dat", std::ios::in | std::ios::binary);
	if (f.is_open()) {
		f.read(reinterpret_cast<char*>(new_arr), sizeof(Student) * len);
		f.close();
	}
	else {
		std::cerr << "MAIN::FSTREAM::could not open file" << std::endl;
		return 2;
	}

	for (Student& s : new_arr)
		std::cout << s.name << " " << s.age << " " << s.gpa << std::endl;

	return 0;
}