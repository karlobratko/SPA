#pragma once

#pragma once
#include <iostream>

class Vector2i {

	friend std::ostream& operator<<(std::ostream& os, const Vector2i& src) {
		os << "[" << src.m_X << "," << src.m_Y << "]";
		return os;
	}

public:
	Vector2i(int x, int y)
		: m_X{ x }, m_Y{ y } {
		//std::cout << "CONSTRUCTOR" << std::endl;
	}
	Vector2i(int scalar = 0.f)
		: Vector2i{ scalar, scalar } {
	}
	Vector2i(const Vector2i& src)
		: m_X{ src.m_X }, m_Y{ src.m_Y } {
		std::cout << "COPY" << std::endl;
	}
	Vector2i& operator=(const Vector2i& src) {
		m_X = src.m_X;
		m_Y = src.m_Y;
		std::cout << "COPY" << std::endl;
		return *this;
	}
	Vector2i(Vector2i&& src) noexcept
		: m_X{ src.m_X }, m_Y{ src.m_Y } {
		std::cout << "MOVE" << std::endl;
	}
	Vector2i& operator=(Vector2i&& src) noexcept {
		m_X = src.m_X;
		m_Y = src.m_Y;
		std::cout << "MOVE" << std::endl;
		return *this;
	}
	~Vector2i() {
		std::cout << "DESTRUCTOR" << std::endl;
	}

	bool operator==(const Vector2i& rhs) const {
		return this->m_X == rhs.m_X && this->m_Y == rhs.m_Y;
	}

	bool operator>(const Vector2i& rhs) const {
		return this->m_X > rhs.m_X && this->m_Y > rhs.m_Y;
	}

private:
	int m_X, m_Y;

};
