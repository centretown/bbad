#include "circle.hpp"

Circle::Circle() : x{0}, y{0}, radius{0}, color{0} {}

Circle::Circle(float x, float y, float radius, Color color)
    : x{x}, y{y}, radius{radius}, color{color} {}

void Circle::Draw() { DrawCircle(x, y, radius, color); }
void Circle::DrawLines() {
  DrawCircleLines(x, y, radius + 1.0f, BLACK);
  DrawCircleLines(x, y, radius + 2.0f, BLACK);
  DrawCircleLines(x, y, radius + 3.0f, BLACK);
}

bool Circle::Contains(Vector2 point) {
  float dx = point.x - x;
  float dy = point.y - y;
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
