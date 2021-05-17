#pragma once

#include <iostream>
#include <string>

#include "powers_t.h"

class hero_t {
public:
	hero_t(
		std::string	= "", 
		bool				= false, 
		float				= 0., 
		float				= 0., 
		float				= 0., 
		float				= 0., 
		float				= 0., 
		float				= 0., 
		float				= 0.,
		powers_t		= powers_t{}
	);
	hero_t(const hero_t&);
	hero_t& operator=(const hero_t&);
	~hero_t() = default;

	void set_powers(const powers_t&);

	std::string get_name() const;
	powers_t&		get_powers();

	static bool is_good	(const hero_t&);
	static bool is_bad	(const hero_t&);
	static bool no_power(const hero_t&, const std::string&);

	static hero_t transform_prop(hero_t&, const std::string&, const std::string&, float);


	friend std::istream& operator>>(std::istream&, hero_t&);

	friend std::ostream& operator<<(std::ostream&, const hero_t&);
	void write_v(std::ostream&, const std::string&) const;

private:
	void add_prop(hero_t&, const std::string&, float);
	void sub_prop(hero_t&, const std::string&, float);
	void mul_prop(hero_t&, const std::string&, float);
	void div_prop(hero_t&, const std::string&, float);

	std::string	name_;
	bool				align_;
	float				intl_;
	float				str_;
	float				spd_;
	float				dur_;
	float				pow_;
	float				comb_;
	float				total_;
	powers_t		powers_;
};

