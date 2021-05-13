#include "certificate_t.h"

#include <iomanip>
#include <algorithm>
#include <sstream>

certificate_t::certificate_t() {
}

certificate_t::certificate_t(const certificate_t& certificate) : 
	name_								{ certificate.name_								},
	pass_policy_				{ certificate.pass_policy_				},
	type_								{ certificate.type_								}, 
	renewal_start_date_	{ certificate.renewal_start_date_	},
	private_key_expiry_	{ certificate.private_key_expiry_ },
	DN_									{ certificate.DN_									} {
}

date_t certificate_t::get_start_date() const {
	return renewal_start_date_;
}

date_t certificate_t::get_expiry_date() const {
	return private_key_expiry_;
}

std::istream& operator>>(std::istream& is, certificate_t& certificate) {
	std::string line{};
	do		std::getline(is, line);
	while (is && line.empty());
	line.erase(line.find_last_not_of(" \t\v\f\r\n") + 1);
	std::istringstream iss{ line };
	std::string temp{};
	iss
		>> temp
		>> certificate.name_
		>> certificate.pass_policy_
		>> certificate.type_
		>> certificate.renewal_start_date_
		>> certificate.private_key_expiry_
		>> std::ws;
	std::getline(iss, certificate.DN_);
	certificate.name_ = temp + " " + certificate.name_;
	if (iss.fail()) is.setstate(iss.rdstate());
	return is;
}

std::ostream& operator<<(std::ostream& os, const certificate_t& certificate) {
	std::ostringstream oss{};
	oss
		<< std::left
		<< std::setw(16) << certificate.name_								<< " "
		<< std::setw(11) << certificate.pass_policy_				<< " "
		<< std::setw(12) << certificate.type_								<< " "
		<< std::setw(15) << certificate.renewal_start_date_	<< " "
		<< std::setw(15) << certificate.private_key_expiry_ << " "
		<<									certificate.DN_;
	if (!oss) os.setstate(oss.rdstate());
	else os << oss.str();
	return os;
}
