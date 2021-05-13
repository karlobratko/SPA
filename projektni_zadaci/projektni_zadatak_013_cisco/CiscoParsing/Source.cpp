#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <fstream>

#include "date_t.h"
#include "certificate_t.h"
#include "FileAccessError.h"

const char* file_name_I{ "cisco_dat.txt" };

bool expired(const date_t& when, const certificate_t& certificate) {
	return !(
		certificate.get_start_date() <= when ||
		certificate.get_expiry_date() <= when
	);
}

int main() {
	
	try {
		std::fstream file{ file_name_I, std::ios::in };
		if (file.is_open()) {
			std::string temp{};
			do		std::getline(file, temp);
			while (temp.at(0) != '-');
			std::vector<certificate_t> certificates{};
			certificates.reserve(10);
			std::copy(
				std::istream_iterator<certificate_t>(file),
				std::istream_iterator<certificate_t>(),
				std::back_inserter(certificates)
			);
			/*std::copy(
				std::begin(certificates),
				std::end(certificates),
				std::ostream_iterator<certificate_t>(std::cout, "\n")
			);*/
			std::vector<certificate_t>::iterator certificates_past_due_begin{
				std::stable_partition(
					std::begin(certificates),
					std::end(certificates),
					std::bind(expired, date_t{ 2011, 1, 9 }, std::placeholders::_1)
				)
			};
			if (certificates_past_due_begin != std::end(certificates))
				std::copy(
					certificates_past_due_begin,
					std::end(certificates),
					std::ostream_iterator<certificate_t>(std::cout, "\n")
				);
			else std::cout << "no items past due" << std::endl;
		}
		else
			throw FileAccessError{};
	}
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}

	return 0;
}