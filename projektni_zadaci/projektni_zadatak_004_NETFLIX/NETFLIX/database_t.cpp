#include "database_t.h"

#include <algorithm>

void database_t::read_data(std::istream& is, const std::string& type) {
	multimedia_t media{};
	if (type != "All") {
		while (is >> media)
			if (media.get_type() == type)
				data_.push_back(media);
	}
	else 
		std::copy(
			std::istream_iterator<multimedia_t>(is),
			std::istream_iterator<multimedia_t>(),
			std::back_inserter(data_)
		);
}

void database_t::write_data(std::ostream& os) {
	os << "[\n";
	std::for_each(
		std::begin(data_),
		std::end(data_),
		[&os, i = 0, size = data_.size()](const multimedia_t& media) mutable -> void {
			os << media << (i != size - 1 ? "," : "") << "\n";
			++i;
		}
	);
	os << "]";
}
