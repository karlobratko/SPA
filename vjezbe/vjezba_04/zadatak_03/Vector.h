#pragma once
#include <string>
class Vector {
public:
	Vector(const std::size_t&, const std::string&);
	std::size_t Size() const;
	std::string& At(const std::size_t&);

private:
	std::string m_Data[50];
	std::size_t m_Size;
};

