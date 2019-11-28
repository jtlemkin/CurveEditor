//
// Created by James Lemkin on 11/26/19.
//

#ifndef HW4_CURVEMANAGER_H
#define HW4_CURVEMANAGER_H

#include "Curve.h"
#include "Mode.h"

class CurveManager {
  std::vector<Curve> curves;

  int curve_index;
  int point_index;

  bool modifying;

  Mode mode;

  Pointf& getSelectedPoint();
  Curve& getSelectedCurve();

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
