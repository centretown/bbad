#include "lighting.hpp"
#include "raylib.h"
#include "rlights.h"
#include <raymath.h>

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static int lightsCount = 0; // Current amount of created lights

// Send light properties to shader
// NOTE: Light shader locations should be available
void UpdateLightValues(Shader shader, Light light) {
  // Send to shader light enabled state and type
  SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
  SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);

  // Send to shader light position values
  float position[3] = {light.position.x, light.position.y, light.position.z};
  SetShaderValue(shader, light.positionLoc, position, SHADER_UNIFORM_VEC3);

  // Send to shader light target position values
  float target[3] = {light.target.x, light.target.y, light.target.z};
  SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);

  // Send to shader light color values
  float color[4] = {
      (float)light.color.r / (float)255, (float)light.color.g / (float)255,
      (float)light.color.b / (float)255, (float)light.color.a / (float)255};
  SetShaderValue(shader, light.colorLoc, color, SHADER_UNIFORM_VEC4);
}

// Create a light and get shader locations
Light CreateLight(int type, Vector3 position, Vector3 target, Color color,
                  Shader shader) {
  Light light = {0};

  if (lightsCount < MAX_LIGHTS) {
    light.enabled = true;
    light.type = type;
    light.position = position;
    light.target = target;
    light.color = color;

    // NOTE: Lighting shader naming must be the provided ones
    light.enabledLoc = GetShaderLocation(
        shader, TextFormat("lights[%i].enabled", lightsCount));
    light.typeLoc =
        GetShaderLocation(shader, TextFormat("lights[%i].type", lightsCount));
    light.positionLoc = GetShaderLocation(
        shader, TextFormat("lights[%i].position", lightsCount));
    light.targetLoc =
        GetShaderLocation(shader, TextFormat("lights[%i].target", lightsCount));
    light.colorLoc =
        GetShaderLocation(shader, TextFormat("lights[%i].color", lightsCount));

    UpdateLightValues(shader, light);

    lightsCount++;
  }

  return light;
}

Lighting::Lighting() {
  position[0] = (Vector3){-2, 1, -2};
  position[1] = (Vector3){2, 1, 2};
  position[2] = (Vector3){-2, 1, 2};
  position[3] = (Vector3){2, 1, -2};
}

void Lighting::Create(Shader shdr, Vector3 size, Vector3 target) {
  Color colors[MAX_LIGHTS] = {GREEN, BLUE, ORANGE, YELLOW};

  this->size = size;

  position[0].x = -size.x;
  position[0].z = -size.z;
  position[1].x = size.x;
  position[1].z = size.z;
  position[2].x = -size.x;
  position[2].z = size.z;
  position[3].x = size.x;
  position[3].z = -size.z;

  shader = shdr;
  for (int i = 0; i < MAX_LIGHTS; i++) {
    lights[i] = CreateLight(0, position[i], target, colors[i], shader);
  }
}

void Lighting::Show() {
  for (int i = 0; i < MAX_LIGHTS; i++) {
    if (lights[i].enabled)
      DrawSphereEx(lights[i].position, size.x / 8, 8, 8, lights[i].color);
    else
      DrawSphereWires(lights[i].position, size.x / 8, 8, 8,
                      ColorAlpha(lights[i].color, 0.3f));
  }
}

void Lighting::Update() {
  for (int i = 0; i < MAX_LIGHTS; i++)
    UpdateLightValues(shader, lights[i]);
}
