#include <raylib.h>
#include <raymath.h>

#include "stl.h"

#define RLIGHTS_IMPLEMENTATION
#include "../src/rlights.h"

#include "../src/gamepad.hpp"
#include "../src/keyboard.hpp"
#include "../src/shape.hpp"
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
    .position = (Vector3){.x = 3.0f, .y = -100.0f, .z = 2.0f},
    .target = (Vector3){.x = 0.0f, .y = 0.0f, .z = 0.0f},
    .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
    .fovy = 60.0f,
    .projection = CAMERA_PERSPECTIVE,
};

Cube cube = {
    .position = {.x = 1.0f, .y = 0.0f, .z = 0.0f},
    .size = {.x = .5f, .y = .3f, .z = .3},
    .color = BLUE,
};

Shape shape = cube.Make();

static Shader shader = {0};
static int ambientLoc = 0;
static Light lights[MAX_LIGHTS] = {0};

// Create lights
void CreateLights() {
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

  lights[0] = CreateLight(LIGHT_POINT, (Vector3){-2, 1, -2}, Vector3Zero(),
                          YELLOW, shader);
  lights[1] =
      CreateLight(LIGHT_POINT, (Vector3){2, 1, 2}, Vector3Zero(), RED, shader);
  lights[2] = CreateLight(LIGHT_POINT, (Vector3){-2, 1, 2}, Vector3Zero(),
                          GREEN, shader);
  lights[3] = CreateLight(LIGHT_POINT, (Vector3){2, 1, -2}, Vector3Zero(), BLUE,
                          shader);
}

void PrintStlData(const char *fileName, stl_file *stl) {
  printf("file: %s\n"
         "\t degenerate_facets=%d \n"
         "\t edges_fixed=%d \n"
         "\t facets_added=%d \n"
         "\t facets_removed=%d \n"
         "\t facets_reversed=%d \n"
         "\t normals_fixed=%d \n"
         "\t number_of_parts=%d \n"
         "\t original_num_facets=%d \n"
         "\t number_of_facets=%d \n"
         "\t bounding_diameter=%f \n"
         "\t shortest_edge=%f \n"
         "\t facets_malloced=%d \n"
         "\t volume=%f \n",
         fileName, stl->stats.degenerate_facets, stl->stats.edges_fixed,
         stl->stats.facets_added, stl->stats.facets_removed,
         stl->stats.facets_reversed, stl->stats.normals_fixed,
         stl->stats.number_of_parts, stl->stats.original_num_facets,
         stl->stats.number_of_facets, stl->stats.bounding_diameter,
         stl->stats.shortest_edge, stl->stats.facets_malloced,
         stl->stats.volume);
}

void PrintFacets(stl_file *stl) {
  for (int i = 0; i < stl->stats.number_of_facets; i++) {
    stl_facet *facet = &stl->facet_start[i];
    printf("Facet %d\n"

           "\tnormal  [x=%.3f, y=%.3f, z=%.3f]\n"
           "\tvertex0 [x=%.3f, y=%.3f, z=%.3f]\n"
           "\tvertex1 [x=%.3f, y=%.3f, z=%.3f]\n"
           "\tvertex2 [x=%.3f, y=%.3f, z=%.3f]\n"
           "\textra   [%x %x]\n",

           i, facet->normal.x, facet->normal.y, facet->normal.z,
           facet->vertex[0].x, facet->vertex[0].y, facet->vertex[0].z,
           facet->vertex[1].x, facet->vertex[1].y, facet->vertex[1].z,
           facet->vertex[2].x, facet->vertex[2].y, facet->vertex[2].z,
           (uint8_t)facet->extra[0], (uint8_t)facet->extra[1]);
  }
}

// void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color);
// void DrawTriangleStrip3D(const Vector3 *points, int pointCount, Color color);
stl_file stlFile = {0};
stl_file *stl = &stlFile;

void DrawFacet(stl_facet *facets, int start, int stop) {
  for (int i = start; i < stop; i++) {
    stl_facet *facet = &facets[i];
    DrawTriangle3D(facet->vertex[0], facet->vertex[1], facet->vertex[2],
                   (Color){.r = 0, .g = 255, .b = 255, .a = 255});
  }
}

void Loop() {
  float cameraPos[3] = {0};
  SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos,
                 SHADER_UNIFORM_VEC3);

  BeginDrawing();
  ClearBackground(BLACK);
  DrawFPS(0, 0);
  DrawText(TextFormat("Camera Position"), 8, 40, 24, GREEN);
  DrawText(TextFormat("X=%.2f, Y=%.2f, Z=%.2f", camera.position.x,
                      camera.position.y, camera.position.z),
           16, 80, 24, YELLOW);
  BeginMode3D(camera);
  BeginShaderMode(shader);

  DrawFacet(stl->facet_start, 0, stl->stats.number_of_facets);
  // DrawPlane(Vector3Zero(), (Vector2){4.0, 4.0}, WHITE);

  EndShaderMode();
  EndMode3D();
  EndDrawing();

  camera.position = AxesToVector(camera.position, .5f);
  camera.position = ButtonsToVector(camera.position, Vector3{0}, .5f);
  camera.position = KeysToVector(camera.position, Vector3{0}, .5f);
}

void ShowWindow() {
  SetupWindow();
  CreateLights();

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
  char fileName[256] = {0};
  strncpy(fileName, src, sizeof(fileName) - 1);

  stl_open(&stlFile, fileName);

  PrintFacets(stl);
  PrintStlData(fileName, stl);

  ShowWindow();
  return ret;
}
