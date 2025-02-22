#include "gamepad.hpp"
#include "keyboard.hpp"
#include "raylib.h"
#include "state.hpp"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static State state;
const Camera camera = (Camera){
    .position = (Vector3){.x = 3.0f, .y = 3.0f, .z = 2.0f},
    .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
    .fovy = 60.0f,
    .projection = CAMERA_PERSPECTIVE,
};

Vector2 Navigate(Vector2 pos, bool down) {
  Vector2 vec = {0};
  Vector2 base = {0};
  vec = GamePadToVector2(vec, base, 8.0f);
  vec = KeysToVector2(vec, base, 8.0f);
  return vec;
}

void Loop() {
  state.now = GetTime();
  Vector2 mousePos = GetMousePosition();
  bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  Vector2 vec = Navigate(mousePos, mouseDown);
  // state.nav = InputGamepadNav(state.now);
  // if (state.nav.cmd == NAV_NONE) {
  //   state.nav = InputKeyNav(state.now);
  // }
  state.UpdateState(mousePos, mouseDown);
  BeginDrawing();

  ClearBackground(state.color);
  // state.compass.Draw();
  BeginMode3D(camera);
  // for (int i = 0; i < state.count; i++) {
  //   state.shapes[i]->Draw();
  // }
  EndMode3D();
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

  // ShapeT<SphereShape> sphere = (ShapeT<SphereShape>{});
  // state.Add(&sphere);

  // state.sphere.Move(Vector3{.x = .5, .y = .5, .z = 1});
  // state.sphere.shape.radius = .5;
  // state.sphere.shape.color = BLUE;

  // state.compass.Init(200.0f, 200.0f, 150.0f, GREEN);
  // RenderTexture rtexture = LoadRenderTexture(radius * 2, radius * 2);
  // BeginTextureMode(texture);
  // Draw();
  // DrawLines();
  // DrawSpokes(15.0f);
  // EndTextureMode();

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(Loop, 60, 1);
#else
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    Loop();
  }
#endif

  CloseWindow();
  return 0;
}
