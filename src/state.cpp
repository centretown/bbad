#include "state.hpp"
#include "compass.hpp"
#include "raylib.h"

State::State()
    : now{0}, mousePos{0}, color{BLACK},
      compass(200, 200, 160.0f, (Color){.r = 127, .g = 127, .b = 0, .a = 255}) {
}
void State::UpdateState(Vector2 mousePos, bool mouseDown) {
  if (IsWindowFocused())
    compass.Update(mousePos, mouseDown, nav);
}
