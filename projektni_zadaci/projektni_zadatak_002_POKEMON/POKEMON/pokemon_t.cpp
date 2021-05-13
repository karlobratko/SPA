#include "pokemon_t.h"

#include <iomanip>
#include <sstream>
#include <algorithm>
#include <random>
#include <memory>

double RandomNumber(double min, double max) {
	static std::unique_ptr<std::random_device> device_ = std::make_unique<std::random_device>();
	static std::unique_ptr<std::mt19937> generator = std::make_unique<std::mt19937>((*device_)());
	std::uniform_real_distribution<double> distribution{ min, max };
	return distribution(*generator);
}

int ParseInt(const std::string& s) {
	return s == "" ? 0 : std::stoi(s);
}

pokemon_t::pokemon_t() : 
	id_					{ 0			}, 
	name_				{ '\0'	},
	type1_			{ '\0'	},
	type2_			{ '\0'	},
	total_			{ 0			},
	hp_					{ 0			},
	atk_				{ 0			},
	def_				{ 0			},
	SPAtk_			{ 0			},
	SPDef_			{ 0			},
	speed_			{ 0			},
	gen_				{ 0			},
	isLegendary_{ false } {
}

pokemon_t::pokemon_t(const pokemon_t& other) :
	id_					{ other.id_						},
	total_			{ other.total_				},
	hp_					{ other.hp_						},
	atk_				{ other.atk_					},
	def_				{ other.def_					},
	SPAtk_			{ other.SPAtk_				},
	SPDef_			{ other.SPDef_				},
	speed_			{ other.speed_				},
	gen_				{ other.gen_					},
	isLegendary_{ other.isLegendary_	} {
	std::copy(std::begin(other.name_),	std::end(other.name_), name_);
	std::copy(std::begin(other.type1_), std::end(other.type1_), type1_);
	std::copy(std::begin(other.type2_), std::end(other.type2_), type2_);
}

void pokemon_t::setID(const int id) {
	id_ = id;
}

void pokemon_t::setName(const std::string& name) {
	std::copy(std::begin(name), std::end(name), name_);
}

void pokemon_t::setType1(const std::string& type1) {
	std::copy(std::begin(type1), std::end(type1), type1_);
}

void pokemon_t::setType2(const std::string& type2) {
	std::copy(std::begin(type2), std::end(type2), type2_);
}

void pokemon_t::setTotal(const int total) {
	total_ = total;
}

void pokemon_t::setHP(const int hp) {
	hp_ = hp;
}

void pokemon_t::setAtk(const int atk) {
	atk_ = atk;
}

void pokemon_t::setDef(const int def) {
	def_ = def;
}

void pokemon_t::setSPAtk(const int SPAtk) {
	SPAtk_ = SPAtk;
}

void pokemon_t::setSPDef(const int SPDef) {
	SPDef_ = SPDef;
}

void pokemon_t::setSpeed(const int speed) {
	speed_ = speed;
}

void pokemon_t::setGen(const int gen) {
	gen_ = gen;
}

void pokemon_t::setIsLegendary(const bool leg) {
	isLegendary_ = leg;
}

std::string pokemon_t::getName() const {
	return std::string{ name_ };
}

std::string pokemon_t::getSpeedInterval() const {
	if			(speed_ <= 19)	return "0-19";
	else if (speed_ <= 39)	return "20-39";
	else if (speed_ <= 59)	return "40-59";
	else if (speed_ <= 79)	return "60-79";
	else if (speed_ <= 99)	return "80-99";
	else										return ">=100";
}

double pokemon_t::calculateDMG(const pokemon_t& defender) const {
	return (this->atk_ / defender.def_) * RandomNumber(0.75, 1.0);
}

pokemon_t& pokemon_t::fight(pokemon_t& attacker) {
	bool attacker_won{};
	double attackerHP{ static_cast<double>(attacker.hp_) };
	double defenderHP{ static_cast<double>(this->hp_) };
	while (true) {
		defenderHP -= attacker.calculateDMG(*this);
		if (defenderHP <= 0) {
			attacker_won = true;
			break;
		}

		attackerHP -= this->calculateDMG(attacker);
		if (attackerHP <= 0) {
			attacker_won = false;
			break;
		}
	}
	return attacker_won
		? attacker
		: *this;
}

bool pokemon_t::operator==(const std::string& name) const {
	return name_ == name;
}

bool pokemon_t::isType(const pokemon_t& p, const std::string& type) {
	return p.type1_ == type;
}

bool pokemon_t::totalLowerThan(const pokemon_t& p, const int total) {
	return p.total_ < total;
}

pokemon_t pokemon_t::multiplyProp(pokemon_t p, const std::string& prop, const double prop_mult) {
	if			(prop == "HP")		p.hp_			= static_cast<int>(p.hp_		* prop_mult);
	else if (prop == "ATK")		p.atk_		= static_cast<int>(p.atk_		* prop_mult);
	else if (prop == "DEF")		p.def_		= static_cast<int>(p.def_		* prop_mult);
	else if (prop == "SPATK") p.SPAtk_	= static_cast<int>(p.SPAtk_ * prop_mult);
	else if (prop == "SPDEF") p.SPDef_	= static_cast<int>(p.SPDef_ * prop_mult);
	else if (prop == "SPEED") p.speed_	= static_cast<int>(p.speed_ * prop_mult);
	return p;
}

pokemon_t pokemon_t::increaseProp(pokemon_t p, const std::string& prop, const int prop_inc) {
	if			(prop == "HP")		p.hp_			+= prop_inc;
	else if (prop == "ATK")		p.atk_		+= prop_inc;
	else if (prop == "DEF")		p.def_		+= prop_inc;
	else if (prop == "SPATK") p.SPAtk_	+= prop_inc;
	else if (prop == "SPDEF") p.SPDef_	+= prop_inc;
	else if (prop == "SPEED") p.speed_	+= prop_inc;
	return p;
}

std::istream& operator>>(std::istream& is, pokemon_t& p) {
	std::string line{};
	std::getline(is, line);
	if (!is.eof()) {
		std::istringstream iss{ line };
		std::string data{};
		std::getline(iss, data, ',');
		p.setID(std::stoi(data));
		iss.getline(p.name_, 30, ',');
		iss.getline(p.type1_, 30, ',');
		iss.getline(p.type2_, 30, ',');
		std::getline(iss, data, ',');
		p.setTotal(ParseInt(data));
		std::getline(iss, data, ',');
		p.setHP(ParseInt(data));
		std::getline(iss, data, ',');
		p.setAtk(ParseInt(data));
		std::getline(iss, data, ',');
		p.setDef(ParseInt(data));
		std::getline(iss, data, ',');
		p.setSPAtk(ParseInt(data));
		std::getline(iss, data, ',');
		p.setSPDef(ParseInt(data));
		std::getline(iss, data, ',');
		p.setSpeed(ParseInt(data));
		std::getline(iss, data, ',');
		p.setGen(ParseInt(data));
		std::getline(iss, data, ',');
		p.setIsLegendary((data == "" || data == "0" ? 0 : 1));
		if (iss.fail()) is.setstate(iss.rdstate());
	}
	else is.setstate(std::ios::eofbit);
	return is;
}

std::ostream& operator<<(std::ostream& os, const pokemon_t& p) {
	std::ostringstream oss{};
	oss
		<< std::left
		<< std::setw(4)		<< p.id_		<< " "
		<< std::right
		<< std::setw(30)	<< p.name_	<< " "
		<< std::setw(10)	<< p.type1_ << " "
		<< std::setw(10)	<< p.type2_ << " "
		<< std::setw(10)	<< p.total_ << " "
		<< std::setw(10)	<< p.hp_		<< " "
		<< std::setw(10)	<< p.atk_		<< " "
		<< std::setw(10)	<< p.def_		<< " "
		<< std::setw(10)	<< p.SPAtk_	<< " "
		<< std::setw(10)	<< p.SPDef_	<< " "
		<< std::setw(10)	<< p.speed_	<< " ";
	if (!oss) os.setstate(oss.rdstate());
	else os << oss.str();
	return os;
}