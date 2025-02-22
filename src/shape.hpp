#pragma once
#include <raylib.h>

void Empty(void *);
void EmptyMove(void *, Vector3);
Vector3 EmptyPosition(void *);

class Shape {
  void *p;
  void (*draw)(void *);
  void (*drawWires)(void *);
  void (*move)(void *, Vector3);
  Vector3 (*position)(void *);
  void (*load)(void *);
  void (*unload)(void *);

public:
  Shape();
  Shape(void *p);
  Shape(void *p, void(void *draw), void(void *drawWires),
        void (*move)(void *, Vector3), Vector3 (*position)(void *));
  Shape(void *p, void(void *draw), void (*move)(void *, Vector3),
        Vector3 (*position)(void *), void (*load)(void *),
        void (*unload)(void *));

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
  Vector3 position;
  Vector3 size;
  Color color;
  Shape Make();
};

struct Sphere {
  Vector3 position;
  float radius;
  Color color;
  Shape Make();
};

struct Cylinder {
  Vector3 position;
  float radiusTop;
  float radiusBottom;
  float height;
  int slices;
  Color color;
  Shape Make();
};

struct Capsule {
  Vector3 startPos;
  Vector3 endPos;
  float radius;
  int slices;
  int rings;
  Color color;
  Shape Make();
};
