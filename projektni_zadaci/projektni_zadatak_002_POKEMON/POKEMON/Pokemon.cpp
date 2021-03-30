#include "Pokemon.h"
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

Pokemon::Pokemon()
: m_ID{ 0 }
, m_Name{ "" }
, m_Type1{ "" }
, m_Type2{ "" }
, m_Total{ 0 }
, m_HP{ 0 }
, m_Atk{ 0 }
, m_Def{ 0 }
, m_SPAtk{ 0 }
, m_SPDef{ 0 }
, m_Speed{ 0 }
, m_Gen{ 0 }
, m_IsLegendary{ false } {
}

void Pokemon::SetData(std::string& line) {
	std::stringstream sstr{ line };
	std::string data{};
	std::getline(sstr, data, ',');
	SetID(std::stoi(data));
	std::getline(sstr, data, ',');
	SetName(data);
	std::getline(sstr, data, ',');
	SetType1(data);
	std::getline(sstr, data, ',');
	SetType2(data);
	std::getline(sstr, data, ',');
	SetTotal(ParseInt(data));
	std::getline(sstr, data, ',');
	SetHP(ParseInt(data));
	std::getline(sstr, data, ',');
	SetAtk(ParseInt(data));
	std::getline(sstr, data, ',');
	SetDef(ParseInt(data));
	std::getline(sstr, data, ',');
	SetSPAtk(ParseInt(data));
	std::getline(sstr, data, ',');
	SetSPDef(ParseInt(data));
	std::getline(sstr, data, ',');
	SetSpeed(ParseInt(data));
	std::getline(sstr, data, ',');
	SetGen(ParseInt(data));
	std::getline(sstr, data, ',');
	SetIsLegendary((data == "" || data == "0" ? 0 : 1));
}

void Pokemon::SetID(const int ID) {
	m_ID = ID;
}

void Pokemon::SetName(const std::string& name) {
	std::copy(name.begin(), name.end(), m_Name);
}

void Pokemon::SetType1(const std::string& type1) {
	std::copy(type1.begin(), type1.end(), m_Type1);
}

void Pokemon::SetType2(const std::string& type2) {
	std::copy(type2.begin(), type2.end(), m_Type2);
}

void Pokemon::SetTotal(const int total) {
	m_Total = total;
}

void Pokemon::SetHP(const int HP) {
	m_HP = HP;
}

void Pokemon::SetAtk(const int atk) {
	m_Atk = atk;
}

void Pokemon::SetDef(const int def) {
	m_Def = def;
}

void Pokemon::SetSPAtk(const int SPAtk) {
	m_SPAtk = SPAtk;
}

void Pokemon::SetSPDef(const int SPDef) {
	m_SPDef = SPDef;
}

void Pokemon::SetSpeed(const int speed) {
	m_Speed = speed;
}

void Pokemon::SetGen(const int gen) {
	m_Gen = gen;
}

void Pokemon::SetIsLegendary(const bool leg) {
	m_IsLegendary = leg;
}

std::string Pokemon::GetName() const {
	return std::string{ m_Name };
}

double Pokemon::CalculateDMG(const Pokemon& defender) const {
	return (this->m_Atk / defender.m_Def) * RandomNumber(0.75, 1.0);
}

Pokemon& Pokemon::Fight(Pokemon& attacker) {
	bool attacker_won{};
	double attackerHP{ static_cast<double>(attacker.m_HP) };
	double defenderHP{ static_cast<double>(this->m_HP) };
	while (true) {
		defenderHP -= attacker.CalculateDMG(*this);
		if (defenderHP <= 0) {
			attacker_won = true;
			break;
		}

		attackerHP -= this->CalculateDMG(attacker);
		if (attackerHP <= 0) {
			attacker_won = false;
			break;
		}
	}
	return attacker_won
		? attacker
		: *this;
}

std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
	os
		<< std::setw(4) << p.m_ID << " "
		<< std::setw(30) << p.m_Name << " "
		<< std::setw(10) << p.m_Type1 << " "
		<< std::setw(10) << p.m_Type2 << " "
		<< std::setw(5) << p.m_Total;
	return os;
}
