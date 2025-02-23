#include "shape.hpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <math.h>

void Empty(void *) {};
void EmptyMove(void *, Vector3) {};
float EmptyFloat(void *) { return 0.0f; };
Vector3 EmptyVector3(void *) { return Vector3Zero(); };

Shape::Shape()
    : p{NULL}, size{EmptyVector3}, draw{Empty}, drawWires{Empty},
      move{EmptyMove}, position{EmptyVector3}, load{Empty}, unload{Empty} {}

Shape::Shape(void *p)
    : p{p}, size{EmptyVector3}, draw{Empty}, drawWires{Empty}, move{EmptyMove},
      position{EmptyVector3}, load{Empty}, unload{Empty} {}

Shape::Shape(void *p, Vector3 (*size)(void *), void (*draw)(void *),
             void (*drawWires)(void *), void (*move)(void *, Vector3),
             Vector3 (*position)(void *))
    : p{p}, size{size}, draw{draw}, drawWires{drawWires}, move{move},
      position{position}, load{Empty}, unload{Empty} {}

Shape::Shape(void *p, Vector3 (*size)(void *), void (*draw)(void *),
             void (*drawWires)(void *), void (*move)(void *, Vector3),
             Vector3 (*position)(void *), void (*load)(void *),
             void (*unload)(void *))
    : p{p}, size{size}, draw{draw}, move{move}, position{position}, load{load},
      unload{unload} {}

Vector3 CylinderSize(void *p) {
  Cylinder *sh = (Cylinder *)p;
  float diameter = fmax(sh->radiusTop, sh->radiusBottom) * 2;
  return (Vector3){.x = diameter, .y = sh->height, .z = diameter};
}
void CylinderDraw(void *p) {
  Cylinder *sh = (Cylinder *)p;
  DrawCylinder(sh->position, sh->radiusTop, sh->radiusBottom, sh->height,
               sh->slices, sh->color);
}
void CylinderDrawWires(void *p) {
  Cylinder *sh = (Cylinder *)p;
  DrawCylinderWires(sh->position, sh->radiusTop, sh->radiusBottom, sh->height,
                    sh->slices, sh->color);
}
void CylinderMove(void *p, Vector3 v) { Move<Cylinder>(p, v); }
Vector3 CylinderPosition(void *p) { return Position<Cylinder>(p); }
Shape Cylinder::Make() {
  return Shape(this, CylinderSize, CylinderDraw, CylinderDrawWires,
               CylinderMove, CylinderPosition);
}
Vector3 CubeSize(void *p) {
  Cube *sh = (Cube *)p;
  return sh->size;
}
void CubeDraw(void *p) {
  Cube *sh = (Cube *)p;
  DrawCubeV(sh->position, sh->size, sh->color);
}
void CubeDrawWires(void *p) {
  Cube *sh = (Cube *)p;
  DrawCubeWiresV(sh->position, sh->size, sh->color);
}
void CubeMove(void *p, Vector3 v) { Move<Cube>(p, v); }
Vector3 CubePosition(void *p) { return Position<Cube>(p); }
Shape Cube::Make() {
  return Shape(this, CubeSize, CubeDraw, CubeDrawWires, CubeMove, CubePosition);
};

Vector3 SphereSize(void *p) {
  Sphere *sh = (Sphere *)p;
  float diameter = sh->radius * 2;
  return (Vector3){.x = diameter, .y = diameter, .z = diameter};
}
void SphereDraw(void *p) {
  Sphere *sh = (Sphere *)p;
  DrawSphere(sh->position, sh->radius, sh->color);
}
void SphereDrawWires(void *p) {
  Sphere *sh = (Sphere *)p;
  DrawSphereWires(sh->position, sh->radius, 20, 20, sh->color);
}
void SphereMove(void *p, Vector3 v) { Move<Sphere>(p, v); }
Vector3 SpherePosition(void *p) { return Position<Sphere>(p); }
Shape Sphere::Make() {
  return Shape(this, SphereSize, SphereDraw, SphereDrawWires, SphereMove,
               SpherePosition);
};

Vector3 CapsuleSize(void *p) {
  Capsule *sh = (Capsule *)p;
  float diffx = fabs(sh->endPos.x - sh->startPos.x);
  float diffy = fabs(sh->endPos.y - sh->startPos.y);
  float diffz = fabs(sh->endPos.z - sh->startPos.z);
  return (Vector3){.x = diffx, .y = diffy, .z = diffz};
}
void CapsuleDraw(void *p) {
  Capsule *sh = (Capsule *)p;
  DrawCapsule(sh->startPos, sh->endPos, sh->radius, sh->slices, sh->rings,
              sh->color);
}
void CapsuleDrawWires(void *p) {
  Capsule *sh = (Capsule *)p;
  DrawCapsuleWires(sh->startPos, sh->endPos, sh->radius, sh->slices, sh->rings,
                   sh->color);
}
void CapsuleMove(void *p, Vector3 position) {
  Capsule *sh = (Capsule *)p;
  Vector3 diff = Vector3Subtract(position, sh->startPos);
  sh->startPos = position;
  sh->endPos = Vector3Add(diff, sh->endPos);
}
Vector3 CapsulePosition(void *p) {
  Capsule *sh = (Capsule *)p;
  return sh->startPos;
}
Shape Capsule::Make() {
  return Shape(this, CapsuleSize, CapsuleDraw, CapsuleDrawWires, CapsuleMove,
               CapsulePosition);
};
