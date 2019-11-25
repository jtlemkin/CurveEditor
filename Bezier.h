//
// Created by James Lemkin on 11/25/19.
//

#ifndef HW4_BEZIER_H
#define HW4_BEZIER_H

#include <vector>

class Pointf {
  float x, y;
 public:
  float getX() const;
  float getY() const;
 public:
  Pointf(float x, float y);
};

class Bezier {
  std::vector<Pointf> points;
 public:
  Bezier();

  void addPoint(float x, float y);
  const std::vector<Pointf> &getPoints() const;
};

#endif //HW4_BEZIER_H
