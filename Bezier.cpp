//
// Created by James Lemkin on 11/25/19.
//

#include "Bezier.h"
Pointf::Pointf(float x, float y) : x(x), y(y) {}
float Pointf::getX() const {
  return x;
}
float Pointf::getY() const {
  return y;
}

Bezier::Bezier() {}

void Bezier::addPoint(float x, float y) {
  points.emplace_back(x, y);
}
const std::vector<Pointf> &Bezier::getPoints() const {
  return points;
}
