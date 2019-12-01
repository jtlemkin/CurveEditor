//
// Created by James Lemkin on 11/25/19.
//

#include "Pointf.h"

Pointf::Pointf(float x, float y) : x(x), y(y) {}

Pointf Pointf::operator*(float n) {
  return Pointf(x * n, y * n);
}

Pointf Pointf::operator+(const Pointf &p2) {
  return Pointf(x + p2.x, y + p2.y);
}
std::ostream &operator<<(std::ostream &os, const Pointf &pointf) {
  os << "x: " << pointf.x << " y: " << pointf.y;
  return os;
}
Pointf Pointf::operator/(float n) {
  return Pointf(x / n, y / n);
}
