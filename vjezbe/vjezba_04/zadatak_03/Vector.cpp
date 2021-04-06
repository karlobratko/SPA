#include "Vector.h"

Vector::Vector(const std::size_t& size, const std::string& value) {
  for (std::size_t i{ 0 }; i < size; ++i)
    m_Data[i] = value;
  m_Size = size;
}

std::size_t Vector::Size() const {
  return m_Size;
}

std::string& Vector::At(const std::size_t& idx) {
  return m_Data[idx];
}
