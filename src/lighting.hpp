#pragma once

#include "rlights.h"

#include <raylib.h>

struct Lighting {
  Shader shader = {0};
  Vector3 position[MAX_LIGHTS] = {0};
  Light lights[MAX_LIGHTS] = {0};
  Vector3 size;
  Lighting();
  void Create(Shader shader, Vector3 size, Vector3 target);
  void Show();
  void Update();
};
