#pragma once
#include "navigate.hpp"
#include "shape.hpp"
#include <raylib.h>

#define MAX_SHAPES 20
struct State {
  double now;
  Vector2 mousePos;
  Color color;
  Navigator nav;
  Shape *shapes[MAX_SHAPES];
  int count;
  State();
  void Add(Shape *shape);
  void UpdateState(Vector2 mousePos, bool mouseDown);
};
