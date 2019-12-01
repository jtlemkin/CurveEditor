//
// Created by James Lemkin on 11/25/19.
//

#ifndef HW4_BEZIER_H
#define HW4_BEZIER_H

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <vector>
#include "Pointf.h"
#include "Mode.h"

class Curve {
 private:

  std::vector<Pointf> points;
  bool selected;
  int order;
 public:
  void setOrder(int newOrder);
 private:

  std::vector<float> knots;

  Pointf computeBezierPoint(float u) const;
  Pointf computeSplinePoint(float u) const;

  int getEffectiveOrder() const;

 public:
  Curve();

  std::vector<Pointf> &getPoints();
  std::vector<float>& getKnots();

  void display(int resolution, Mode mode) const;
  void displayBezier(int resolution) const;
  void displaySpline(int resolution) const;

  void select();
  void deselect();
  void addPoint(float x, float y, int point_index);

  void deletePoint(int point_index);

  void modifyPoint(float x, float y, int point_index);

  int getNumPoints() const;
  int getKnotInterval(float u) const;

  float& getKnotAt(int knot_index);
  void incrKnotAt(int knot_index);
  void decrKnotAt(int knot_index);

  int getNumKnots() const;
  int getOrder() const;
};

#endif //HW4_BEZIER_H
