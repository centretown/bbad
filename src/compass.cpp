#include "compass.hpp"
#include "circle.hpp"
#include "gamepad.hpp"
#include "keyboard.hpp"
#include "navigate.hpp"
#include <math.h>
#include <raylib.h>

Compass::Compass(int x, int y, float radius, Color color) {
  // Init(x, y, radius, color);
}

void Compass::Init(int x, int y, float radius, Color color) {
  mousePos = {0};
  outer.radius = radius;
  inner.radius = radius / 5;

  outer.x = x - outer.radius;
  outer.y = y - outer.radius;
  inner.x = outer.x + outer.radius - inner.radius;
  inner.y = outer.y + outer.radius - inner.radius;
  inner.color = color;
  outer.color = {.r = color.g, .g = color.b, .b = color.r, .a = 255};

  BeginDrawing();

  inner.texture = LoadRenderTexture(inner.radius * 2, inner.radius * 2);
  BeginTextureMode(inner.texture);
  ClearBackground(Color{0});
  inner.Draw();
  EndTextureMode();

  outer.texture = LoadRenderTexture(outer.radius * 2, outer.radius * 2);
  BeginTextureMode(outer.texture);
  ClearBackground(Color{0});
  outer.Draw();
  outer.DrawSpokes(5.0f);
  outer.DrawLines();
  EndTextureMode();

  EndDrawing();
}

void Compass::Draw() {
  DrawTexture(outer.texture.texture, outer.x, outer.y, WHITE);
  DrawTexture(inner.texture.texture, inner.x, inner.y, WHITE);
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
