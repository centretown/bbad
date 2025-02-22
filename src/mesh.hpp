#pragma once
#include <raylib.h>

struct MeshShape {
  Mesh mesh;
  Material material;
  Matrix matrix;
  Vector3 position;
  Vector3 rotationAxis;
  float rotationAngle;
  Vector3 scale;
  Color tint;
  void *genPtr;
};

struct MeshPoly {
  int sides;
  float radius;
};

struct MeshPlane {
  float width;
  float length;
  int resX;
  int resZ;
};

typedef struct MeshCube {
  float width;
  float height;
  float length;
} MeshCube;

struct MeshSphere {
  float radius;
  int rings;
  int slices;
};

struct MeshHemisphere {
  float radius;
  int rings;
  int slices;
};

struct MeshCylinder {
  float radius;
  float height;
  int slices;
};

struct MeshCone {
  float radius;
  float height;
  int slices;
};

typedef struct MeshTorus {
  float radius;
  float size;
  int radSeg;
  int sides;
} MeshTorus;

struct MeshKnot {
  float radius;
  float size;
  int radSeg;
  int sides;
};

struct MeshHeightmap {
  Image heightmap;
  Vector3 size;
};

struct MeshCubicmap {
  Image cubicmap;
  Vector3 cubeSize;
};
