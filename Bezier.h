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

class Bezier {
  std::vector<Pointf> points;
  bool selected;

  Pointf computePoint(float u) const;
 public:
  Bezier();

  std::vector<Pointf> &getPoints();

  void display(int resolution) const;

  void select();
  void deselect();
  void addPoint(float x, float y, int point_index);

  void deletePoint(int point_index);

  void modifyPoint(float x, float y, int point_index);

  int getNumPoints();
};

#endif //HW4_BEZIER_H
