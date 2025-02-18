#include "mouse.hpp"
#include <math.h>

bool PointInRect(Vector2 point, Rectangle rect) {
  return (point.x >= rect.x && point.x < rect.x + rect.width) &&
         (point.y >= rect.y && point.y < rect.y + rect.height);
}

int InputPoint(Vector2 point, int count, const Rectangle *rects) {
  for (int i = 0; i < count; i++) {
    if (PointInRect(point, rects[i])) {
      return i;
    }
  }
  return NAV_NONE;
}

static TimedInput mouseIn = {
    .interval = 0.35f,
    .lastTime = 0.0f,
    .nextTime = 0.0f,
    .lastInput = 0,
};

bool InputMouseButton(Rectangle rect, double now, Vector2 point) {
  if (PointInRect(point, rect)) {
    if (now >= mouseIn.nextTime && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      mouseIn.nextTime = now + mouseIn.interval;
      return true;
    }
  }
  return false;
}

int InputMouse(int count, const Rectangle *rects, double now,
               Vector2 mousePos) {
  int cmd = InputPoint(mousePos, count, rects);
  if (cmd != NAV_NONE) {
    if (now >= mouseIn.nextTime && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      mouseIn.nextTime = now + mouseIn.interval;
      return cmd;
    }
  }

  return NAV_NONE;
}

MouseIn InputMouseRects(Vector2 point, int rectCount, Rectangle *rects,
                        double now = 0.0f) {
  MouseIn result = {.currentItem = -1, .hoverItem = -1};
  for (int i = 0; i < rectCount; i++) {
    if (PointInRect(point, rects[i])) {
      result.hoverItem = i;
      if (now > 0.0f && now >= mouseIn.nextTime) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
          result.currentItem = i;
        }
      }
      return result;
    }
  }
  return result;
}
