//
// Created by James Lemkin on 11/25/19.
//

#include <iostream>
#include "Curve.h"

Curve::Curve() : selected(false), order(2) {
  for (int i = 0; i < order + 1; i++) {
    knots.push_back((float) i);
  }
}

std::vector<Pointf> &Curve::getPoints() {
  return points;
}
void Curve::display(int resolution, Mode mode) const {
  glPointSize(5);

  if (selected) {
    for (const auto& point : points) {
      glBegin(GL_POINTS);
      glColor3f(0, 0, 0);
      glVertex3f(point.x, point.y, 0);
      glEnd();
    }
  }

  if (selected) {
    glColor3f(0, 1, 0);
  } else {
    glColor3f(0, 0, 0);
  }

  switch(mode) {
    case bezier:
      displayBezier(resolution);
      break;
    case spline:
      displaySpline(resolution);
      break;
  }
}

Pointf Curve::computeBezierPoint(float u) const {
  auto size = (int) points.size();

  Pointf work[size][size];

  for (int i = 0; i < size; ++i) {
    work[0][i] = points.at(i);
  }

  for (int i = 1; i < size; ++i) {
    for (int j = 0; j < size - i; ++j) {
      work[i][j] = (work[i - 1][j] * (1.0f - u)) + (work[i - 1][j + 1] * u);
    }
  }

  return work[size - 1][0];
}
void Curve::select() {
  selected = true;
}
void Curve::deselect() {
  selected = false;
}
void Curve::addPoint(float x, float y, int point_index) {
  if (points.empty() || point_index == points.size() - 1) {
    points.emplace_back(x, y);
  } else {
    points.insert(points.begin() + point_index + 1, Pointf(x, y));
  }

  knots.push_back(knots.back() + 1.0f);
}
int Curve::getNumPoints() const {
  return (int) points.size();
}
void Curve::deletePoint(int point_index) {
  if (!points.empty()) {
    points.erase(points.begin() + point_index);
  }

  if (knots.size() > order) {
    knots.pop_back();
  }
}
void Curve::modifyPoint(float x, float y, int point_index) {
  points.at(point_index).x = x;
  points.at(point_index).y = y;
}
void Curve::displayBezier(int resolution) const {
  if (points.size() >= 2) {
    glBegin(GL_LINE_STRIP);

    if (selected) {
      glColor3f(0, 1, 0);
    } else {
      glColor3f(0, 0, 0);
    }

    for (int i = 0; i <= resolution; i++) {
      float u = 1.0f / (float) resolution * (float) i;
      Pointf p = computeBezierPoint(u);
      glVertex3f(p.x, p.y, 0);
    }
    glEnd();
  }
}


Pointf Curve::computeSplinePoint(float u) const {
  //knot interval index
  unsigned long I = getKnotInterval(u);
  int k = getEffectiveOrder();

  Pointf p[k][points.size()];

  for (int i = 0; i < points.size(); ++i) {
    p[0][i] = points.at(i);
  }

  float denom, lweight, rweight;

  for (int j = 1; j <= k - 1; ++j) {
    for (int i = I - (k - 1); i <= I - j; ++i) {
      denom = knots.at(i + k) - knots.at(i + j);
      lweight = (knots.at(i + k) - u) / denom;
      rweight = (u - knots.at(i + j)) / denom;

      p[j][i] = p[j - 1][i] * lweight + p[j - 1][i + 1] * rweight;
    }
  }

  return p[k - 1][I - (k - 1)];
}

void Curve::displaySpline(int resolution) const {
  if (points.size() >= 2) {
    glBegin(GL_LINE_STRIP);

    if (selected) {
      glColor3f(0, 1, 0);
    } else {
      glColor3f(0, 0, 0);
    }

    float range = knots.at(points.size()) - knots.at(getEffectiveOrder() - 1);
    for (int i = 0; i <= resolution * range; i++) {
      float u = knots.at(getEffectiveOrder() - 1) + i / (float) resolution;
      Pointf p = computeSplinePoint(u);
      glVertex3f(p.x, p.y, 0);
    }
    glEnd();
  }
}

unsigned long Curve::getKnotInterval(float u) const {
  if (u == knots.at(points.size() + 1)) {
    return (int) points.size();
  }

  for(unsigned long i = 0; i < knots.size(); ++i) {
    if (knots.at(i) > u) {
      return i - 1;
    }
  }
}

int Curve::getEffectiveOrder() const {
  return order >= points.size() ? (int) points.size() : order;
}
int Curve::getOrder() const {
  return order;
}
float &Curve::getKnotAt(unsigned long knot_index) {
  return knots.at(knot_index);
}
void Curve::incrKnotAt(unsigned long knot_index) {
  knots.at(knot_index) += 0.1f;

  if (knot_index != knots.size() - 1 && knots.at(knot_index) > knots.at(knot_index + 1)) {
    knots.at(knot_index) = knots.at(knot_index + 1);
  }
}
void Curve::decrKnotAt(unsigned long knot_index) {
  knots.at(knot_index) -= 0.1f;

  if (knots.at(knot_index) < 0) {
    knots.at(knot_index) = 0;
  }

  if (knot_index != 0 && knots.at(knot_index) < knots.at(knot_index - 1)) {
    knots.at(knot_index) = knots.at(knot_index - 1);
  }
}
int Curve::getNumKnots() const {
  return (int) knots.size();
}
std::vector<float> &Curve::getKnots() {
  return knots;
}
void Curve::setOrder(int newOrder) {
  if (newOrder < order) {
    for (int i = 0; i < order - newOrder; i++) {
      knots.pop_back();
    }
  } else if (newOrder > order) {
    for (int i = 0; i < newOrder - order; i++) {
      knots.push_back(knots.back() + 1);
    }
  }

  order = newOrder;
}
