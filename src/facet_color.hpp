#pragma once

#include <raylib.h>

struct FacetColor {
  union {
    char bytes[2];
    struct {
      int blue : 5;
      int green : 5;
      int red : 5;
      int valid : 1;
    };
  };

  FacetColor(char b[2]) {
    bytes[0] = b[0];
    bytes[1] = b[1];
  }
  bool IsValid() { return valid == 1; };
  Color GetColor() {
    Color c = {0};
    c.r = red;
    c.g = green;
    c.b = blue;
    c.a = 255;
    return c;
  };
};
