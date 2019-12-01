//
// Created by James Lemkin on 11/26/19.
//

#ifndef HW4_CURVEMANAGER_H
#define HW4_CURVEMANAGER_H

#include "Curve.h"
#include "Mode.h"

class CurveManager {
 private:
  std::vector<Curve> curves;

  int curve_index;
  int point_index;
  int knot_index;

  bool modifying;

  Mode mode;

  int resolution;

  void reset();

 public:
  explicit CurveManager(int resolution);

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

  Mode getMode() const;

  float& getSelectedKnot();
  Pointf& getSelectedPoint();
  Curve& getSelectedCurve();

  void selectNextKnot();
  void selectPreviousKnot();
  void incrKnot();
  void decrKnot();

  int getKnot_index() const;

  void saveState();
  void loadState();

  void toggleMode();
};

#endif //HW4_CURVEMANAGER_H
