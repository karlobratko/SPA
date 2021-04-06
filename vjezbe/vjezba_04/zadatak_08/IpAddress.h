#pragma once

#include <ostream>

class IPAddress {
public:
	IPAddress(int = 0, int = 0, int = 0, int = 0);
	char DetermineClass() const;
	friend std::ostream& operator<<(std::ostream&, const IPAddress&);
private:
	int x_, y_, z_, w_;
};

