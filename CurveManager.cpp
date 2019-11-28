//
// Created by James Lemkin on 11/26/19.
//

#include "CurveManager.h"
CurveManager::CurveManager() {
  curves.emplace_back();
  curves.at(0).select();

  curve_index = 0;
  point_index = 0;

  modifying = false;

  mode = bezier;
}

void CurveManager::displayCurves() {
  for (const auto& curve : curves) {
    curve.display(100, mode);
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
}
void CurveManager::addCurve() {
  curves.emplace_back();

  getSelectedCurve().deselect();

  curve_index = (int) curves.size() - 1;

  getSelectedCurve().select();

  point_index = 0;
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
}
void CurveManager::toggleModifying() {
  modifying = !modifying;
}
bool CurveManager::isModifying() {
  return modifying;
}
void CurveManager::modifyPoint(float x, float y) {
  getSelectedCurve().modifyPoint(x, y, point_index);
}

