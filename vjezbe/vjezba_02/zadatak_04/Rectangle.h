#pragma once

#include <string>
#include <stdexcept>
#include <ostream>

class Rectangle {
public:
	friend std::ostream& operator<<(std::ostream&, const Rectangle&);

	Rectangle(unsigned = 1, unsigned = 1);
	
	std::string Shape(const char = '#', const char = '*', const bool = true) const;

private:
	unsigned m_Width;
	unsigned m_Height;

};

