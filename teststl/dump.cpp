#include "dump.hpp"

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
