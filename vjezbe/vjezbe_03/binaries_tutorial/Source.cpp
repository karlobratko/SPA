#include <iostream>
#include <fstream>

struct Student {
	char name[20];
	int age;
	float gpa;
};

int main() {
	Student student{ "Karlo", 20, 3.58 };

	std::fstream f{ "records.dat", std::ios::out | std::ios::binary };
	//f.open("records.dat", std::ios::out | std::ios::binary);

	if (f.is_open()) {
		f.write(reinterpret_cast<char*>(&student), sizeof(Student));
		f.close();
	}
	else {
		std::cerr << "MAIN::FSTREAM::could not open file" << std::endl;
		return 1;
	}

	Student new_student{};
	f.open("records.dat", std::ios::in | std::ios::binary);

	if (f.is_open()) {
		f.read(reinterpret_cast<char*>(&new_student), sizeof(Student));
		f.close();
	}
	else {
		std::cerr << "MAIN::FSTREAM::could not open file" << std::endl;
		return 2;
	}

	std::cout << new_student.name << " " << new_student.age << " " << new_student.gpa << std::endl;

	return 0;
}