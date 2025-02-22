#include "../src/shape.hpp"
#include "../src/window.hpp"
#include "raylib.h"
#include <cstddef>
#include <raymath.h>

const Camera camera = (Camera){
    .position = (Vector3){.x = .0f, .y = .0f, .z = 2.5f},
    .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
    .fovy = 140.0f,
    .projection = CAMERA_PERSPECTIVE,
};

Sphere sphere = {
    .position = {.x = -4.0f, .y = -2.0f, .z = .1f},
    .radius = .3f,
    .color = RED,
};

Cube cube = {
    .position = {.x = -2.0f, .y = 0.0f, .z = .3f},
    .size = {.x = .3f, .y = .3f, .z = .3},
    .color = BLUE,
};

Cylinder cylinder = {
    .position = {.x = 2.0f, .y = 1.0f, .z = 2.0f},
    .radiusTop = .5f,
    .radiusBottom = .3f,
    .height = .2f,
    .slices = 10,
    .color = YELLOW,
};

Capsule capsule = {
    .startPos = {.x = 4.0f, .y = 2.0f, .z = .0f},
    .endPos = {.x = 4.5f, .y = .2f, .z = -.3f},
    .radius = .4f,
    .slices = 10,
    .rings = 10,
    .color = GREEN,
};

Shape shapes[] = {sphere.Make(), cube.Make(), cylinder.Make(), capsule.Make()};
const size_t shapeCount = sizeof(shapes) / sizeof(shapes[0]);

const Vector3 still = Vector3Zero();
const Vector3 farther = Vector3{.x = .0f, .y = -.0f, .z = -.05f};
const Vector3 nearer = Vector3{.x = .0f, .y = .0f, .z = .05f};

// const Vector3 rotateLeftX = Vector3{.x = .05f, .y = -.0f, .z = -.0f};
// const Vector3 rotateLeftX = Vector3{.x = .05f, .y = -.0f, .z = -.0f};
// const Vector3 nearer = Vector3{.x = .0f, .y = .05f, .z = .05f};

Vector3 current = farther;

size_t shift = 1;
size_t cycles = 0;
const size_t maxCycles = 100;

enum {
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
};

Vector2 corners[4];

void Loop() {

  BeginDrawing();
  ClearBackground(BLACK);
  BeginMode3D(camera);

  for (size_t i = 0; i < shapeCount; i++) {
    Shape *shape = &shapes[i];
    shape->DrawWires();
    Vector3 pos = shape->Position();
    shape->Move(pos);
  }

  EndMode3D();
  EndDrawing();

  cycles += shift;
  if (cycles == 0) {
    current = still;
    shift = 0;
  } else if (cycles == maxCycles - 1) {
    current = still;
    shift = 0;
  }
}

int main() {

  SetupWindow();

  for (size_t i = 0; i < shapeCount; i++) {
    Shape *shape = &shapes[i];
    shape->Load();
  }

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    Loop();
  }

  for (size_t i = 0; i < shapeCount; i++) {
    Shape *shape = &shapes[i];
    shape->Unload();
  }
  CloseWindow();
}
