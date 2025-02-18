#pragma once
#include "circle.hpp"
#include "navigate.hpp"
#include "raylib.h"

struct Compass {
  Circle outer;
  Circle inner;
  Color needleColor;
  Vector2 mousePos;
  Compass();
  Compass(int x, int y, float radius, Color color);
  void Init(int x, int y, float radius, Color color);
  void Update(Vector2 mousePos, bool mouseDown, Navigator nav);
  void Draw();
  void DrawSpokes(float increment);
  void Navigate();
};
