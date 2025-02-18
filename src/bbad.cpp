#include "raylib.h"
#include "state.hpp"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static State state;

void Loop() {
  state.now = GetTime();
  Vector2 mousePos = GetMousePosition();
  bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  // state.nav = InputGamepadNav(state.now);
  // if (state.nav.cmd == NAV_NONE) {
  //   state.nav = InputKeyNav(state.now);
  // }
  state.UpdateState(mousePos, mouseDown);
  BeginDrawing();

  ClearBackground(state.color);
  state.compass.Draw();
  EndDrawing();
}

int main() {
#if defined(PLATFORM_WEB)
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT |
                 FLAG_WINDOW_MAXIMIZED);
#else
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT |
                 FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE);
#endif

  InitWindow(1260, 720, "Centretown - BBAD");

#if defined(PLATFORM_WEB)
  int monitor = GetCurrentMonitor();
  SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
#endif

  SetWindowPosition(0, 0);

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(Loop, 60, 1);
#else
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    Loop();
  }
#endif

  return 0;
}
