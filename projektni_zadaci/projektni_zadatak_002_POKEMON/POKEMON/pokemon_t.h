#pragma once

#include <iostream>
#include <string>

class pokemon_t
{
public:
	pokemon_t();
	pokemon_t(const pokemon_t&);

	void setID(const int);
	void setName(const std::string&);
	void setType1(const std::string&);
	void setType2(const std::string&);
	void setTotal(const int);
	void setHP(const int);
	void setAtk(const int);
	void setDef(const int);
	void setSPAtk(const int);
	void setSPDef(const int);
	void setSpeed(const int);
	void setGen(const int);
	void setIsLegendary(const bool);

	std::string getName() const;
	std::string getSpeedInterval() const;

	double calculateDMG(const pokemon_t&) const;
	pokemon_t& fight(pokemon_t&);

	bool operator==(const std::string&) const;
	friend std::istream& operator>>(std::istream&, pokemon_t&);
	friend std::ostream& operator<<(std::ostream&, const pokemon_t&);

	static bool isType(const pokemon_t&, const std::string&);
	static bool totalLowerThan(const pokemon_t&, const int);
	static pokemon_t multiplyProp(pokemon_t, const std::string&, const double);
	static pokemon_t increaseProp(pokemon_t, const std::string&, const int);

private:
	int		id_;
	char	name_[30]; 
	char	type1_[10];
	char	type2_[10];
	int		total_;
	int		hp_;
	int		atk_;
	int		def_;
	int		SPAtk_;
	int		SPDef_;
	int		speed_;
	int		gen_;
	bool	isLegendary_;
};

