#include "Point.h"
#include <cmath>
#include <iomanip>

Point::Point(int x, int y) 
  : x_{ x }, y_{ y } {
}

void Point::SetX(const int& x) {
  x_ = x;
}

void Point::SetY(const int& y) {
  y_ = y;
}

void Point::Initialize(const int& x, const int& y) {
  x_ = x;
  y_ = y;
}

int Point::GetX() const {
    return x_;
}

int Point::GetY() const {
    return y_;
}

double Point::Distance() const {
  return std::sqrt(
    std::pow(x_, 2) + std::pow(y_, 2)
  );
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  os << 
    "(" << point.x_ << ", " << point.y_ << ") - d: " 
    << std::setprecision(9) << point.Distance();
  return os;
}
