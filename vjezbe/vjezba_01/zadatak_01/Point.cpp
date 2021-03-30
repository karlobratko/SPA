#include "Point.h"
#include <sstream>


auto Point::_TestValues(unsigned x, unsigned y) const -> bool {
	return x >= 0 && x <= 100 && y >= 0 && y <= 100;
}

auto Point::_InitVariables(unsigned x, unsigned y) -> void {
	this->_x = x;
	this->_y = y;
}

auto Point::_InitDefault() -> void {
	this->_x = 0;
	this->_y = 0;
}

auto Point::_Print(std::ostream& os) const -> void {
	os << this->to_string();
}

Point::Point(unsigned x, unsigned y) {
	if (!this->_TestValues(x, y))
		this->_InitDefault();
	this->_InitVariables(x, y);
}

auto Point::GetX() const -> unsigned {
	return this->_x;
}

auto Point::GetY() const -> unsigned {
	return this->_y;
}

auto Point::to_string() const -> std::string {
	std::stringstream ss;
	ss << "(" << this->_x << ", " << this->_y << ")";
	return ss.str();
}

auto Point::SetX(unsigned x) -> void {
	this->_x = x;
}

auto Point::SetY(unsigned y) -> void {
	this->_y = y;
}

auto Point::Display() const -> void {
	this->_Print(std::cout);
	std::cout << std::endl;
}

auto Point::Distance() const -> double {
	return std::sqrt(std::pow(this->_x, 2) + std::pow(this->_y, 2));
}

auto operator<<(std::ostream& os, const Point& point) -> std::ostream& {
	point._Print(os);
	return os;
}
