#pragma once

#include <string>
#include <ostream>

struct Student {
	std::string name_;
	std::string surname_;
	int birth_date_;
	
	friend std::ostream& operator<<(std::ostream& os, const Student& student) {
		os
			<< student.name_ << "\t"
			<< student.surname_ << "\t"
			<< student.birth_date_;
		return os;
	}
};

typedef Student* StudentPtr;