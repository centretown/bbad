#pragma once
#include <raylib.h>

void Empty(void *);
void EmptyMove(void *, Vector3);
Vector3 EmptyVector3(void *);

class Shape {
  void *p;
  Vector3 (*size)(void *);
  void (*draw)(void *);
  void (*drawWires)(void *);
  void (*move)(void *, Vector3);
  Vector3 (*position)(void *);
  void (*load)(void *);
  void (*unload)(void *);

public:
  Shape();
  Shape(void *p);
  Shape(void *p, Vector3(void *size), void(void *draw), void(void *drawWires),
        void (*move)(void *, Vector3), Vector3 (*position)(void *));
  Shape(void *p, Vector3(void *size), void(void *draw),
        void (*drawWires)(void *), void (*move)(void *, Vector3),
        Vector3 (*position)(void *), void (*load)(void *),
        void (*unload)(void *));

  Vector3 Size() { return size(p); }
  void Draw() { draw(p); }
  void DrawWires() { drawWires(p); }
  void Move(Vector3 v) { move(p, v); }
  Vector3 Position() { return position(p); }
  void Load() { load(p); }
  void Unload() { unload(p); }
};

template <typename T> void Move(void *p, Vector3 v) {
  T *sh = (T *)p;
  sh->position = v;
}

template <typename T> Vector3 Position(void *p) {
  T *sh = (T *)p;
  return sh->position;
}

struct Cube {
  Vector3 position = {0};
  Vector3 size = {0};
  Color color = {0};
  Shape Make();
};

struct Sphere {
  Vector3 position = {0};
  float radius = 0.0f;
  Color color = {0};
  Shape Make();
};

struct Cylinder {
  Vector3 position = {0};
  float radiusTop = 0.0f;
  float radiusBottom = 0.0f;
  float height = 0.0f;
  int slices = 0;
  Color color = {0};
  Shape Make();
};

struct Capsule {
  Vector3 startPos = {0};
  Vector3 endPos = {0};
  float radius = 0.0f;
  int slices = 0;
  int rings = 0;
  Color color = {0};
  Shape Make();
};
