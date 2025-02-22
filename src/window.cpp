#include "window.hpp"

void SetupWindow() {

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
}
