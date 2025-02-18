#pragma once
#include "compass.hpp"
#include "navigate.hpp"
#include <raylib.h>

struct State {
  double now;
  Vector2 mousePos;
  Color color;
  Navigator nav;
  Compass compass;
  State();
  void UpdateState(Vector2 mousePos, bool mouseDown);
};
