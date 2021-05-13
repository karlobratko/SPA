#pragma once

#include <string>
#include <iostream>
#include "date_t.h"

class certificate_t {
public:
	certificate_t();
	certificate_t(const certificate_t&);
	date_t get_start_date() const;
	date_t get_expiry_date() const;

	friend std::istream& operator>>(std::istream&, certificate_t&);
	friend std::ostream& operator<<(std::ostream&, const certificate_t&);

private:
	std::string name_;
	std::string pass_policy_;
	std::string type_;
	date_t renewal_start_date_;
	date_t private_key_expiry_;
	std::string DN_;
};

