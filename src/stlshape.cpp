#include <stl.h>

#include "facet_color.hpp"
#include "stlshape.hpp"

Vector3 StlShapeSize(void *p) {
  StlShape *sh = (StlShape *)p;
  float diameter = sh->stlFile.stats.bounding_diameter;
  return (Vector3){.x = diameter, .y = diameter, .z = diameter};
}

void StlShapeDraw(void *p) {
  StlShape *sh = (StlShape *)p;
  int count = sh->stlFile.stats.number_of_facets;
  stl_facet *facets = sh->stlFile.facet_start;

  for (int i = 0; i < count; i++) {
    stl_facet *facet = &facets[i];
    FacetColor facetColor(facet->extra);
    Color color = (facetColor.IsValid())
                      ? facetColor.GetColor()
                      : (Color){.r = 0, .g = 255, .b = 255, .a = 255};
    DrawTriangle3D(facet->vertex[0], facet->vertex[1], facet->vertex[2], color);
  }
}

void StlShapeDrawWires(void *p) {
  StlShape *sh = (StlShape *)p;
  int count = sh->stlFile.stats.number_of_facets;
  stl_facet *facets = sh->stlFile.facet_start;

  for (int i = 0; i < count; i++) {
    stl_facet *facet = &facets[i];
    FacetColor facetColor(facet->extra);
    Color color = (facetColor.IsValid())
                      ? facetColor.GetColor()
                      : (Color){.r = 0, .g = 255, .b = 255, .a = 172};
    DrawTriangle3D(facet->vertex[0], facet->vertex[1], facet->vertex[2], color);
  }
}

void StlShapeMove(void *p, Vector3 v) { Move<StlShape>(p, v); }
Vector3 StlShapePosition(void *p) { return Position<StlShape>(p); }

void StlShapeLoad(void *p) {
  StlShape *sh = (StlShape *)p;
  stl_open(&sh->stlFile, sh->fileName);
}

void StlShapeUnLoad(void *p) {
  StlShape *sh = (StlShape *)p;
  stl_close(&sh->stlFile);
}

Shape StlShape::Make() {
  return Shape(this, StlShapeSize, StlShapeDraw, StlShapeDrawWires,
               StlShapeMove, StlShapePosition, StlShapeLoad, StlShapeUnLoad);
};
