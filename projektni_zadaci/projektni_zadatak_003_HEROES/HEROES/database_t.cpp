#include "database_t.h"

#include <algorithm>
#include <functional>

void database_t::read_heroes(std::istream& is) {
	std::copy(
		std::istream_iterator<hero_t>(is),
		std::istream_iterator<hero_t>(),
		std::back_inserter(heroes_)
	);
}

void database_t::read_powers(std::istream& is) {
	std::copy(
		std::istream_iterator<powers_t>(is),
		std::istream_iterator<powers_t>(),
		std::back_inserter(powers_)
	);
}

void database_t::combine() {
	std::for_each(
		std::begin(heroes_),
		std::end(heroes_),
		[this](hero_t& hero) {
			auto it = std::find_if(
				std::begin(powers_),
				std::end(powers_),
				[hero](powers_t& power) -> bool {
					return hero.get_name() == power.get_name();
				}
			);
			if (it != std::end(powers_)) hero.set_powers(*it);
		}
	);
	powers_.clear();
}

void database_t::write(std::ostream& os) {
	std::copy(std::begin(heroes_), std::end(heroes_), std::ostream_iterator<hero_t>(os, "\n"));
}

void database_t::write_v(std::ostream& os) {
	std::for_each(
		std::begin(heroes_),
		std::end(heroes_),
		[&os](const hero_t& hero) { hero.write_v(os, "\n"); }
	);
}

std::vector<hero_t>* database_t::operator->() {
	return &heroes_;
}

std::vector<hero_t>& database_t::operator*() {
	return heroes_;
}
