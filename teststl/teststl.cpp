#include <raylib.h>
#include <raymath.h>

// #define RAYGUI_IMPLEMENTATION
// #include <raygui.h>

#include "dump.hpp"

#include "../src/gamepad.hpp"
#include "../src/keyboard.hpp"
#include "../src/lighting.hpp"
#include "../src/shape.hpp"
#include "../src/stlshape.hpp"
#include "../src/window.hpp"

#include <cfloat>
#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

Camera camera = (Camera){
    .position = (Vector3){.x = 2.0f, .y = 4.0f, .z = 6.0f},
    .target = (Vector3){.x = 0.0f, .y = 0.5f, .z = 0.0f},
    .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
    .fovy = 45.0f,
    .projection = CAMERA_PERSPECTIVE,
};

Cube cube = {
    .position = {.x = 1.0f, .y = 0.0f, .z = 0.0f},
    .size = {.x = .5f, .y = .3f, .z = .3},
    .color = BLUE,
};

StlShape stlShape = {
    .position = {.x = 1.0f, .y = 0.0f, .z = 0.0f},
    .color = RED,
};

Shape shape = stlShape.Make();

// void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color);
// void DrawTriangleStrip3D(const Vector3 *points, int pointCount, Color color);
// stl_file stlFile = {0};
// stl_file *stl = &stlFile;

static Shader shader;
static int ambientLoc = 0;
// static Light lights[MAX_LIGHTS] = {0};

static Lighting lighting;

// Create lights
void CreateLighting() {

  shader = LoadShader(
      TextFormat("../resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
      TextFormat("../resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));

  // Get some required shader locations
  shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
  // NOTE: "matModel" location name is automatically assigned on shader loading,
  // no need to get the location again if using that uniform name
  // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader,
  // "matModel");
  ambientLoc = GetShaderLocation(shader, "ambient");
  float value[4] = {0.1f, 0.1f, 0.1f, 1.0f};
  SetShaderValue(shader, ambientLoc, value, SHADER_UNIFORM_VEC4);

  Vector3 size = shape.Size();
  lighting.Create(shader, size, camera.target);
  camera.position = Vector3Scale(size, 2.0f);
}

void Loop() {
  // Vector3 pos = shape.Position();
  // float cameraPos[3] = {pos.x, pos.y, pos.z};
  // SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
  //                SHADER_UNIFORM_VEC3);

  Vector3 shapeSize = shape.Size();
  Vector3 pos = shape.Position();

  lighting.Update();

  BeginDrawing();
  ClearBackground(BLACK);
  DrawFPS(0, 0);
  DrawText(TextFormat("Camera Position"), 8, 40, 24, GREEN);
  DrawText(TextFormat("X=%.2f, Y=%.2f, Z=%.2f", camera.position.x,
                      camera.position.y, camera.position.z),
           16, 80, 24, YELLOW);
  DrawText(TextFormat("X=%.2f, Y=%.2f, Z=%.2f", shapeSize.x, shapeSize.y,
                      shapeSize.z),
           16, 120, 24, YELLOW);
  DrawText(TextFormat("X=%.2f, Y=%.2f, Z=%.2f", pos.x, pos.y, pos.z), 16, 160,
           24, YELLOW);
  BeginMode3D(camera);
  BeginShaderMode(shader);

  shape.Draw();
  // Vector2 size = Vector2{.x = shapeSize.x, .y = shapeSize.z};
  // DrawFacet(stl->facet_start, 0, stl->stats.number_of_facets);
  // DrawPlane(Vector3Zero(), size, WHITE);

  EndShaderMode();

  lighting.Show();

  DrawGrid(10, shapeSize.x / 5);

  EndMode3D();
  EndDrawing();

  camera.position = AxesToVector(camera.position, 1.0f);
  camera.position = ButtonsToVector(camera.position, Vector3{0}, 1.0f);
  camera.position = KeysToVector(camera.position, Vector3{0}, 1.0f);
}

void ShowWindow() {
  SetupWindow();
  CreateLighting();

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(Loop, 60, 1);
#else
  SetTargetFPS(60);            // Set our game to run at 60 frames-per-second
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    Loop();
  }
#endif

  shape.Unload();
  UnloadShader(shader);
  CloseWindow();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("path to stl file is required.\n");
    return 1;
  }

  struct stat status;
  int ret = stat(argv[1], &status);
  if (ret != 0) {
    printf("error occured %d %s\n", errno, strerror(errno));
    return ret;
  }

  const char *src = argv[1];
  strncpy(stlShape.fileName, src, sizeof(stlShape.fileName) - 1);
  shape.Load();

  PrintFacets(&stlShape.stlFile);
  PrintStlData(stlShape.fileName, &stlShape.stlFile);

  ShowWindow();
  return ret;
}
