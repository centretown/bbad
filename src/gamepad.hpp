
#pragma once

#include "navigate.hpp"
#include "raylib.h"

typedef struct Pad {
  bool registered;
  int axisCount;
  float axisValues[6];
  int lastButtonPressed;
  double lastButtonTime;
  float lastAxisValue;
  double lastAxisTime;
  double buttonDelay;
  char name[80];
} Pad;

const char *AxisName(int axis);
Rectangle ButtonsToRectangle(Rectangle rec, Rectangle recbase, float scale);
Vector3 AxesToVectorPro(Vector3 vec, float scale, Vector3 min, Vector3 max);
Vector3 AxesToVector(Vector3 vec, float scale);
Vector3 ButtonsToVector(Vector3 vec, Vector3 base, float scale);
Rectangle ButtonsToRectangle(Rectangle rec, Rectangle recbase, float scale);
Navigator InputGamepadNav(double now);
Vector2 GamePadToVector2(Vector2 vec, Vector2 base, float scale);
