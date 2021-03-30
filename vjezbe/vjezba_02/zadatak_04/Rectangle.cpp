#include "Rectangle.h"

#include <sstream>

Rectangle::Rectangle(unsigned p_Width, unsigned p_Height)
	: m_Width{ p_Width }, m_Height{ p_Height } {
	if (p_Width <= 0 || p_Height <= 0)
		throw std::invalid_argument("RECTANGLE::CONSTRUCTOR::INVALID_ARGUMENT::width and height must be above 0");
}

std::string Rectangle::Shape(const char outline_repr, const char content_repr, const bool repr) const {
	std::stringstream ss{};
	for (std::size_t row{ 0 }; row < m_Height; ++row) {
		for (std::size_t col{ 0 }; col < m_Width; ++col) {
			if (col == 0 || col == m_Width - 1 || row == 0 || row == m_Height - 1)
				ss << outline_repr;
			else {
				if (repr)
					ss << content_repr;
			}
		}
		ss << std::endl;
	}
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rec) {
	os << rec.Shape();
	return os;
}
