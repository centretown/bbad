#pragma once

#include <stl.h>

#include "shape.hpp"

struct StlShape {
  char fileName[256] = {0};
  Vector3 position = {0};
  Color color = {0};
  stl_file stlFile = {0};
  Shape Make();
};
