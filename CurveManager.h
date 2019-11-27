//
// Created by James Lemkin on 11/26/19.
//

#ifndef HW4_CURVEMANAGER_H
#define HW4_CURVEMANAGER_H

#include "Bezier.h"

class CurveManager {
  std::vector<Bezier> curves;

  int curve_index;
  int point_index;

  bool modifying;

  Pointf& getSelectedPoint();
  Bezier& getSelectedCurve();

 public:
  CurveManager();

  void displayCurves();

  void addPoint(float x, float y);
  void addCurve();

  void selectNextPoint();
  void selectPreviousPoint();
  void selectNextCurve();

  void deletePoint();

  void modifyPoint(float x, float y);

  void toggleModifying();

  bool isModifying();
};

#endif //HW4_CURVEMANAGER_H
