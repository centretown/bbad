#pragma once

typedef struct TimedInput {
  double interval;
  double lastTime; // when last input set
  double nextTime; // when last input set
  int lastInput;   // set to 0 after interval
} TimedInput;

enum : int {
  NAV_NONE = -1,
  NAV_LEFT = 0,
  NAV_RIGHT,
  NAV_UP,
  NAV_DOWN,
  NAV_HOME,
  NAV_BACK,
  NAV_COUNT,
};

typedef struct Navigator {
  int cmd;
  float ratio;
} Navigator;
