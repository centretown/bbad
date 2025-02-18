#include "compass.hpp"
#include "gamepad.hpp"
#include "keyboard.hpp"
#include "navigate.hpp"
#include <math.h>
#include <raylib.h>

Compass::Compass(int x, int y, float radius, Color color) {
  Init(x, y, radius, color);
}

void Compass::Init(int x, int y, float radius, Color color) {
  mousePos = {0};
  outer.x = inner.x = x;
  outer.y = inner.y = y;
  outer.radius = radius;
  inner.radius = radius / 5;
  inner.color = color;
  outer.color = {.r = color.g, .g = color.b, .b = color.r, .a = 63};
}
void Compass::Draw() {
  outer.Draw();
  inner.Draw();
  inner.DrawLines();
  DrawSpokes(30.0f);
}

void Compass::DrawSpokes(float increment) {
  float max = (increment > 0.0) ? 360.f : -360.f;
  for (float degree = 0.0f; degree < max; degree += increment) {
    float angle = degree / 180.0f * PI;
    float x = sin(angle) * outer.radius;
    float y = cos(angle) * outer.radius;
    DrawLine(outer.x, outer.y, outer.x + x, outer.y - y,
             Color{.r = 240, .g = 240, .b = 0, .a = 172});
  }
}

void Compass::Update(Vector2 pos, bool down, Navigator nav) {
  mousePos = pos;
  if (!down) {
    Navigate();
    return;
  }

  bool bullseye = inner.Contains(pos);
  if (!bullseye) {
    Navigate();
    return;
  }
  Circle innerNew = inner;
  innerNew.y = pos.y;
  innerNew.x = pos.x;
  if (outer.Contains(innerNew)) {
    inner = innerNew;
  }
  return;
}

void Compass::Navigate() {
  Vector2 vec = {.x = inner.x, .y = inner.y};
  Vector2 base = {.x = outer.x, .y = outer.y};
  vec = GamePadToVector2(vec, base, 8.0f);
  vec = KeysToVector2(vec, base, 8.0f);
  Circle innerNew = inner;
  innerNew.x = vec.x;
  innerNew.y = vec.y;
  if (outer.Contains(innerNew)) {
    inner = innerNew;
  }
}
