//
// Created by James Lemkin on 11/25/19.
//

#include <iostream>
#include "Bezier.h"

Bezier::Bezier() : selected(false) {}

std::vector<Pointf> &Bezier::getPoints() {
  return points;
}
void Bezier::display(int resolution) const {
  glPointSize(5);

  for (const auto& point : points) {
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex3f(point.x, point.y, 0);
    glEnd();
  }

  if (points.size() >= 2) {
    glBegin(GL_LINE_STRIP);

    if (selected) {
      glColor3f(0, 1, 0);
    } else {
      glColor3f(0, 0, 0);
    }

    for (int i = 0; i <= resolution; i++) {
      float u = 1.0f / (float) resolution * (float) i;
      Pointf p = computePoint(u);
      glVertex3f(p.x, p.y, 0);
    }
    glEnd();
  }
}

Pointf Bezier::computePoint(float u) const {
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
void Bezier::select() {
  selected = true;
}
void Bezier::deselect() {
  selected = false;
}
void Bezier::addPoint(float x, float y, int point_index) {
  if (points.empty() || point_index == points.size() - 1) {
    points.emplace_back(x, y);
  } else {
    points.insert(points.begin() + point_index + 1, Pointf(x, y));
  }
}
int Bezier::getNumPoints() {
  return (int) points.size();
}
void Bezier::deletePoint(int point_index) {
  if (!points.empty()) {
    points.erase(points.begin() + point_index);
  }
}
void Bezier::modifyPoint(float x, float y, int point_index) {
  points.at(point_index).x = x;
  points.at(point_index).y = y;
}
