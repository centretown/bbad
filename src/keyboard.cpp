#include "keyboard.hpp"
#include "navigate.hpp"

Vector2 KeysToVector2(Vector2 vec, Vector2 home, float scale) {
  if (IsKeyDown(KEY_LEFT)) {
    vec.x -= scale;
    return vec;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    vec.x += scale;
    return vec;
  }
  if (IsKeyDown(KEY_UP)) {
    vec.y -= scale;
    return vec;
  }
  if (IsKeyDown(KEY_DOWN)) {
    vec.y += scale;
    return vec;
  }
  if (IsKeyDown(KEY_HOME)) {
    vec = home;
    return vec;
  }
  return vec;
}

Vector3 KeysToVector(Vector3 vec, Vector3 home, float scale) {
  if (IsKeyDown(KEY_LEFT)) {
    vec.x -= scale;
    return vec;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    vec.x += scale;
    return vec;
  }
  if (IsKeyDown(KEY_UP)) {
    vec.y += scale;
    return vec;
  }
  if (IsKeyDown(KEY_DOWN)) {
    vec.y -= scale;
    return vec;
  }
  if (IsKeyDown(KEY_PAGE_UP)) {
    vec.z += scale;
    return vec;
  }
  if (IsKeyDown(KEY_PAGE_DOWN)) {
    vec.z -= scale;
    return vec;
  }
  if (IsKeyDown(KEY_HOME)) {
    vec = home;
    return vec;
  }
  return vec;
}

static TimedInput keyIn = {
    .interval = 0.35f, .lastTime = 0.0f, .nextTime = 0.0f, .lastInput = 0};

Navigator InputKeys(int count, const int *keys, double now,
                    TimedInput *timed = &keyIn) {
  Navigator nav = {.cmd = NAV_NONE, .ratio = 1.0f};
  for (int i = 0; i < count; i++) {
    if (IsKeyDown(keys[i]) && now >= keyIn.nextTime) {
      keyIn.nextTime = now + keyIn.interval;
      nav.cmd = i;
      return nav;
    }
  }
  return nav;
}

Navigator InputKeyNav(double now) {
  const static int navKeys[] = {
      KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_HOME, KEY_BACKSPACE,
  };
  const static int navKeysCount = sizeof(navKeys) / sizeof(navKeys[0]);
  return InputKeys(navKeysCount, navKeys, now);
}
