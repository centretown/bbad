#pragma once
#include "raylib.h"

struct Circle {
  float x;
  float y;
  float radius;
  Color color;
  Circle();
  Circle(float x, float y, float radius, Color color);
  void Draw();
  void DrawLines();
  bool Contains(Vector2 point);
  bool Contains(Circle circle);
};
