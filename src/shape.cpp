#include "shape.hpp"
#include "raymath.h"

void Empty(void *) {};
void EmptyMove(void *, Vector3) {};
Vector3 EmptyPosition(void *) { return Vector3Zero(); };

Shape::Shape()
    : p{NULL}, draw{Empty}, drawWires{Empty}, move{EmptyMove},
      position{EmptyPosition}, load{Empty}, unload{Empty} {}

Shape::Shape(void *p)
    : p{p}, draw{Empty}, drawWires{Empty}, move{EmptyMove},
      position{EmptyPosition}, load{Empty}, unload{Empty} {}

Shape::Shape(void *p, void (*draw)(void *), void (*drawWires)(void *),
             void (*move)(void *, Vector3), Vector3 (*position)(void *))
    : p{p}, draw{draw}, drawWires{drawWires}, move{move}, position{position},
      load{Empty}, unload{Empty} {}

Shape::Shape(void *p, void (*draw)(void *), void (*move)(void *, Vector3),
             Vector3 (*position)(void *), void (*load)(void *),
             void (*unload)(void *))
    : p{p}, draw{draw}, move{move}, position{position}, load{load},
      unload{unload} {}

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
  return Shape(this, CylinderDraw, CylinderDrawWires, CylinderMove,
               CylinderPosition);
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
  return Shape(this, CubeDraw, CubeDrawWires, CubeMove, CubePosition);
};

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
  return Shape(this, SphereDraw, SphereDrawWires, SphereMove, SpherePosition);
};

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
  return Shape(this, CapsuleDraw, CapsuleDrawWires, CapsuleMove,
               CapsulePosition);
};
