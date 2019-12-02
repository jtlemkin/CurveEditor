//
// Created by James Lemkin on 11/26/19.
//

#include <fstream>
#include "CurveManager.h"
CurveManager::CurveManager(int resolution) : resolution(resolution) {
  curves.emplace_back();
  curves.at(0).select();

  curve_index = 0;
  point_index = 0;
  knot_index = 0;

  modifying = false;

  mode = spline;
}

void CurveManager::displayCurves() {
  for (const auto& curve : curves) {
    curve.display(resolution, mode);
  }

  if (getSelectedCurve().getNumPoints() != 0) {
    auto selected_point = getSelectedPoint();

    glBegin(GL_POINTS);

    if(modifying) {
      glColor3f(1, 0, 0);
    } else {
      glColor3f(0, 0.749, 1);
    }

    glVertex3f(selected_point.x, selected_point.y, 0);
    glEnd();
  }
}
void CurveManager::addPoint(float x, float y) {
  getSelectedCurve().addPoint(x, y, point_index);

  // We have to reset the selected point when the first point is added to avoid seg faults
  if (getSelectedCurve().getNumPoints() == 1) {
    point_index = 0;
  } else {
    selectNextPoint();
  }
}
void CurveManager::selectNextCurve() {
  getSelectedCurve().deselect();

  curve_index++;

  if (curve_index == curves.size()) {
    curve_index = 0;
  }

  getSelectedCurve().select();
  point_index = 0;
  knot_index = 0;
}
void CurveManager::addCurve() {
  curves.emplace_back();

  selectNextCurve();
}

void CurveManager::selectNextPoint() {
  if (point_index == getSelectedCurve().getNumPoints() - 1) {
    point_index = 0;
  } else {
    point_index++;
  }
}

void CurveManager::selectPreviousPoint() {
  if (point_index == 0) {
    point_index = getSelectedCurve().getNumPoints() - 1;
  } else {
    point_index--;
  }
}
Pointf& CurveManager::getSelectedPoint() {
  return getSelectedCurve().getPoints().at(point_index);
}
Curve& CurveManager::getSelectedCurve() {
  return curves.at(curve_index);
}
void CurveManager::deletePoint() {
  getSelectedCurve().deletePoint(point_index);

  selectPreviousPoint();

  if (getSelectedCurve().getNumPoints() == 0) {
    modifying = false;
    knot_index = 0;
  } else {
    selectPreviousKnot();
  }
}
void CurveManager::toggleModifying() {
  modifying = !modifying;

  if (getSelectedCurve().getNumPoints() == 0) {
    modifying = false;
  }
}
bool CurveManager::isModifying() {
  return modifying;
}
void CurveManager::modifyPoint(float x, float y) {
  getSelectedCurve().modifyPoint(x, y, point_index);
}
Mode CurveManager::getMode() const {
  return mode;
}
float& CurveManager::getSelectedKnot() {
  return getSelectedCurve().getKnotAt(knot_index);
}
int CurveManager::getKnot_index() const {
  return knot_index;
}
void CurveManager::selectNextKnot() {
  knot_index++;

  if(knot_index == getSelectedCurve().getNumKnots()) {
    knot_index = 0;
  }
}
void CurveManager::selectPreviousKnot() {
  knot_index--;

  if(knot_index < 0) {
    knot_index = getSelectedCurve().getNumKnots() - 1;
  }

  if(getSelectedCurve().getNumKnots() == 0) {
    knot_index = 0;
  }
}
void CurveManager::incrKnot() {
  getSelectedCurve().incrKnotAt(knot_index);
}
void CurveManager::decrKnot() {
  getSelectedCurve().decrKnotAt(knot_index);
}
void CurveManager::saveState() {
  std::ofstream saveFile("/Users/jameslemkin/Developer/ecs175/hw4/curves.txt");

  saveFile << curves.size() << "\n";

  for (auto& curve : curves) {
    saveFile << curve.getNumPoints() << "\n";

    for (auto& point : curve.getPoints()) {
      saveFile << point.x << "\n";
      saveFile << point.y << "\n";
    }

    saveFile << curve.getNumKnots() << "\n";

    for (auto& knot : curve.getKnots()) {
      saveFile << knot << "\n";
    }
  }
}

void CurveManager::loadState() {
  std::ifstream saveFile("/Users/jameslemkin/Developer/ecs175/hw4/curves.txt");

  reset();

  int num_curves;
  saveFile >> num_curves;

  for (unsigned long i = 0; i < num_curves; i++) {
    int num_points;
    saveFile >> num_points;

    //The reset function creates the first curve so we want to make sure we don't recreate it
    if (i != 0) {
      curves.emplace_back();
    }

    for(int j = 0; j < num_points; j++) {
      float x, y;

      saveFile >> x;
      saveFile >> y;

      curves.at(i).getPoints().emplace_back(x, y);
    }

    int num_knots;
    saveFile >> num_knots;

    curves.at(i).getKnots().clear();
    for(int j = 0; j < num_knots; j++) {
      float knot;
      saveFile >> knot;

      curves.at(i).getKnots().push_back(knot);
    }
  }
}

void CurveManager::reset() {
  curves.clear();
  curves.emplace_back();
  curves.at(0).select();

  curve_index = 0;
  point_index = 0;
  knot_index = 0;

  modifying = false;

  mode = spline;
}
void CurveManager::toggleMode() {
  if (mode == bezier) {
    mode = spline;
  } else {
    mode = bezier;
  }
}
void CurveManager::incrResolution() {
  resolution++;
}
void CurveManager::decrResolution() {
  resolution--;

  if (resolution < 1) {
    resolution = 1;
  }
}
