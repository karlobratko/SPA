#include "IpAddress.h"

IPAddress::IPAddress(int x, int y, int z, int w)
  : x_{ x }, y_{ y }, z_{ z }, w_{ w } {
}

char IPAddress::DetermineClass() const {
  if (x_ <= 127)
    return 'A';
  else if (x_ <= 191)
    return 'B';
  else if (x_ <= 223)
    return 'C';
  else if (x_ <= 239)
    return 'D';
  else if (x_ <= 254)
    return 'E';
  return '?';
}

std::ostream& operator<<(std::ostream& os, const IPAddress& ip) {
  os << ip.x_ << "." << ip.y_ << "." << ip.z_ << "." << ip.w_;
  return os;
}
