#include "circle.hpp"
#include "raylib.h"
#include <math.h>

Circle::Circle() : x{0}, y{0}, radius{10.0f}, color{RED} {}

Circle::Circle(float x, float y, float radius, Color color)
    : x{x}, y{y}, radius{radius}, color{color} {}

void Circle::Draw() { DrawCircle(radius, radius, radius, color); }
void Circle::DrawLines() {
  DrawCircleLines(radius + 1.0f, radius + 1.0f, radius, YELLOW);
}

bool Circle::Contains(Vector2 point) {
  float dx = point.x - (x + radius);
  float dy = point.y - (y + radius);
  return (radius * radius > (dx * dx + dy * dy));
}

bool Circle::Contains(Circle circle) {
  Circle range = *this;
  range.radius -= circle.radius;
  if (range.radius <= 0.0f)
    return false;
  Vector2 point{.x = circle.x, .y = circle.y};
  return range.Contains(point);
}

void Circle::Init() {}

void Circle::DrawSpokes(float increment) {
  float max = (increment > 0.0) ? 360.f : -360.f;
  for (float degree = 0.0f; degree < max; degree += increment) {
    float angle = degree / 180.0f * PI;
    float xx = sin(angle) * radius;
    float yy = cos(angle) * radius;
    DrawLine(radius, radius, radius + xx, radius + yy,
             Color{.r = 240, .g = 240, .b = 0, .a = 172});
  }
}
