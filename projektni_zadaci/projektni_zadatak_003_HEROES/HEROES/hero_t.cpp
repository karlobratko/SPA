#include "hero_t.h"

#include <sstream>
#include <iomanip>

hero_t::hero_t(
	std::string name, 
	bool				align, 
	float				intl, 
	float				str, 
	float				spd, 
	float				dur, 
	float				pow, 
	float				comb, 
	float				total,
	powers_t		powers
) :
	name_		{ name		},
	align_	{ align		},
	intl_		{ intl		},
	str_		{ str			},
	spd_		{ spd			},
	dur_		{ dur			},
	pow_		{ pow			},
	comb_		{ comb		},
	total_	{ total		},
	powers_	{ powers	} {
}

hero_t::hero_t(const hero_t& other) :
	name_		{ other.name_		},
	align_	{ other.align_	},
	intl_		{ other.intl_		},
	str_		{ other.str_		},
	spd_		{ other.spd_		},
	dur_		{ other.dur_		},
	pow_		{ other.pow_		},
	comb_		{ other.comb_		},
	total_	{ other.total_	},
	powers_	{ other.powers_ } {
}

hero_t& hero_t::operator=(const hero_t& other) {
	if (&other == this) return *this;
	name_		= other.name_;
	align_	= other.align_;
	intl_		= other.intl_;
	str_		= other.str_;
	spd_		= other.spd_;
	dur_		= other.dur_;
	pow_		= other.pow_;
	comb_		= other.comb_;
	total_	= other.total_;
	powers_ = other.powers_;
	return *this;
}

void hero_t::set_powers(const powers_t& powers) {
	powers_ = powers;
}

std::string hero_t::get_name() const {
	return name_;
}

powers_t& hero_t::get_powers() {
	return powers_;
}

bool hero_t::is_good(const hero_t& hero) {
	return hero.align_;
}

bool hero_t::is_bad(const hero_t& hero) {
	return !hero.align_;
}

bool hero_t::no_power(const hero_t& hero, const std::string& power) {
	return !hero.powers_.has_power(power);
}

hero_t hero_t::transform_prop(hero_t& hero, const std::string& prop, const std::string& action, float value) {
	if			(action == "+=") hero.add_prop(hero, prop, value);
	else if (action == "-=") hero.sub_prop(hero, prop, value);
	else if (action == "*=") hero.mul_prop(hero, prop, value);
	else if (action == "/=") hero.div_prop(hero, prop, value);
	return hero;
}

void hero_t::add_prop(hero_t& hero, const std::string& prop, float value) {
	if			(prop == "INT"	) hero.intl_	+= value; 
	else if (prop == "STR"	) hero.str_		+= value;
	else if (prop == "SPD"	) hero.spd_		+= value;
	else if (prop == "DUR"	) hero.dur_		+= value;
	else if (prop == "POW"	) hero.pow_		+= value;
	else if (prop == "COM"	) hero.comb_	+= value;
	else if (prop == "TOTAL") hero.total_ += value;
}

void hero_t::sub_prop(hero_t& hero, const std::string& prop, float value) {
	if			(prop == "INT"	) hero.intl_	-= value; 
	else if (prop == "STR"	) hero.str_		-= value;
	else if (prop == "SPD"	) hero.spd_		-= value;
	else if (prop == "DUR"	) hero.dur_		-= value;
	else if (prop == "POW"	) hero.pow_		-= value;
	else if (prop == "COM"	) hero.comb_	-= value;
	else if (prop == "TOTAL") hero.total_ -= value;
}

void hero_t::mul_prop(hero_t& hero, const std::string& prop, float value) {
	if			(prop == "INT"	) hero.intl_	*= value; 
	else if (prop == "STR"	) hero.str_		*= value;
	else if (prop == "SPD"	) hero.spd_		*= value;
	else if (prop == "DUR"	) hero.dur_		*= value;
	else if (prop == "POW"	) hero.pow_		*= value;
	else if (prop == "COM"	) hero.comb_	*= value;
	else if (prop == "TOTAL") hero.total_ *= value;
}

void hero_t::div_prop(hero_t& hero, const std::string& prop, float value) {
	if (value != 0.f) {
		if			(prop == "INT"	) hero.intl_	/= value; 
		else if (prop == "STR"	) hero.str_		/= value;
		else if (prop == "SPD"	) hero.spd_		/= value;
		else if (prop == "DUR"	) hero.dur_		/= value;
		else if (prop == "POW"	) hero.pow_		/= value;
		else if (prop == "COM"	) hero.comb_	/= value;
		else if (prop == "TOTAL") hero.total_ /= value;
	}
}

bool iss_fail(std::istringstream& iss) {
	if (iss.fail()) {
		iss.clear();
		return true;
	}
	return false;
}

std::istream& operator>>(std::istream& is, hero_t& hero) {
	std::string line{};
	std::getline(is, line);
	if (!is.eof()) {
		std::istringstream iss{ line };
		std::string temp{};
		std::getline(iss, hero.name_, ',');
		std::getline(iss, temp, ',');
		hero.align_ = (temp == "good" ? true : false);
		char c{};
		iss >> hero.intl_;
		if (iss_fail(iss)) hero.intl_		= 0;
		iss.get();
		iss >> hero.str_; iss.get();
		if (iss_fail(iss)) hero.str_		= 0;
		iss.get();
		iss >> hero.spd_; iss.get();
		if (iss_fail(iss)) hero.spd_		= 0;
		iss.get();
		iss >> hero.dur_; iss.get();
		if (iss_fail(iss)) hero.dur_		= 0;
		iss.get();
		iss >> hero.pow_; iss.get();
		if (iss_fail(iss)) hero.pow_		= 0;
		iss.get();
		iss >> hero.comb_; iss.get();
		if (iss_fail(iss)) hero.comb_		= 0;
		iss.get();
		iss >> hero.total_;
		if (iss_fail(iss)) hero.total_	= 0;
	}
	else is.setstate(std::ios::eofbit);
	return is;
}

std::ostream& operator<<(std::ostream& os, const hero_t& hero) {
	std::ostringstream oss{};
	oss
		<< std::left
		<< std::setw(20)	<< hero.name_											<< " "
		<< std::right
		<< std::setw(5)		<< (hero.align_ ? "good" : "bad")	<< " "
		<< std::setw(5)		<< hero.intl_											<< " "
		<< std::setw(5)		<< hero.str_											<< " "
		<< std::setw(5)		<< hero.spd_											<< " "
		<< std::setw(5)		<< hero.dur_											<< " "
		<< std::setw(5)		<< hero.pow_											<< " "
		<< std::setw(5)		<< hero.comb_											<< " "
		<< std::setw(5)		<< hero.total_;
	if (!oss) os.setstate(oss.rdstate());
	else os << oss.str();
	return os;
}

void hero_t::write_v(std::ostream& os, const std::string& delim) const {
	std::ostringstream oss{};
	oss
		<< std::left
		<< std::setw(20)	<< name_											<< " "
		<< std::right
		<< std::setw(5)		<< (align_ ? "good" : "bad")	<< " "
		<< std::setw(5)		<< intl_											<< " "
		<< std::setw(5)		<< str_												<< " "
		<< std::setw(5)		<< spd_												<< " "
		<< std::setw(5)		<< dur_												<< " "
		<< std::setw(5)		<< pow_												<< " "
		<< std::setw(5)		<< comb_											<< " "
		<< std::setw(5)		<< total_											<< " "
		<< std::setw(167) << powers_										<< delim;
	if (!oss) os.setstate(oss.rdstate());
	else os << oss.str();
}