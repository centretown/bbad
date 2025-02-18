#pragma once
#include "navigate.hpp"
#include "raylib.h"

Vector3 KeysToVector(Vector3 vec, Vector3 base, float scale);
Vector2 KeysToVector2(Vector2 vec, Vector2 base, float scale);
Navigator InputKeyNav(double now);
Navigator InputKeys(int count, const int *keys, double now, TimedInput *timed);
