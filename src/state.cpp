#include "state.hpp"
#include "raylib.h"
#include "shape.hpp"
#include <cmath>

State::State() : now{0}, mousePos{0}, color{BLACK}, count(0) {}

void State::Add(Shape *shape) {
  if (count < MAX_SHAPES) {
    shapes[count] = shape;
    count++;
  }
}

void State::UpdateState(Vector2 mousePos, bool mouseDown) {
  // if (IsWindowFocused())
  //   compass.Update(mousePos, mouseDown, nav);
}
