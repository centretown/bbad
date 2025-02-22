#pragma once
#include "raylib.h"

struct Circle {
  float x;
  float y;
  float radius;
  Color color;
  float increment; // spokes
  RenderTexture2D texture;

  Circle();
  Circle(float x, float y, float radius, Color color);
  void Draw();
  void DrawLines();
  void Init();
  bool Contains(Vector2 point);
  bool Contains(Circle circle);
  void DrawSpokes(float increment);
};
