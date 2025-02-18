#pragma once

#include "navigate.hpp"
#include "raylib.h"

typedef struct MouseIn {
  int currentItem;
  int hoverItem;
} MouseIn;

Navigator InputMouseNav(double now, Vector2 point);
MouseIn InputMouseRects(Vector2 point, Rectangle *rects, int rectCount);
