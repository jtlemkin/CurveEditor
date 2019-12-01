//
// Created by James Lemkin on 11/25/19.
//

#ifndef HW4_POINTF_H
#define HW4_POINTF_H

#include <ostream>
class Pointf {
 public:

  float x, y;

  explicit Pointf(float x = 0, float y = 0);

  Pointf operator* (float n);
  Pointf operator+ (const Pointf& p2);
  Pointf operator/ (float n);
  friend std::ostream &operator<<(std::ostream &os, const Pointf &pointf);
};

#endif //HW4_POINTF_H
