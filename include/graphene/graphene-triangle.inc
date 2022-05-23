ifndef __GRAPHENE_TRIANGLE_H__
define __GRAPHENE_TRIANGLE_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec3.inc

_graphene_triangle_t    STRUC
a                       graphene_vec3_t <>
b                       graphene_vec3_t <>
c                       graphene_vec3_t <>
_graphene_triangle_t    ENDS
graphene_triangle_t     typedef _graphene_triangle_t

graphene_triangle_alloc proto
graphene_triangle_free proto :ptr

graphene_triangle_init_from_point3d proto :ptr, :ptr, :ptr, :ptr
graphene_triangle_init_from_vec3 proto :ptr, :ptr, :ptr, :ptr
graphene_triangle_init_from_float proto :ptr, :ptr, :ptr, :ptr
graphene_triangle_get_points proto :ptr, :ptr, :ptr, :ptr
graphene_triangle_get_vertices proto :ptr, :ptr, :ptr, :ptr
graphene_triangle_get_area proto :ptr
graphene_triangle_get_midpoint proto :ptr, :ptr
graphene_triangle_get_normal proto :ptr, :ptr
graphene_triangle_get_plane proto :ptr, :ptr
graphene_triangle_get_bounding_box proto :ptr, :ptr
graphene_triangle_get_barycoords proto :ptr, :ptr, :ptr
graphene_triangle_get_uv proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

graphene_triangle_contains_point proto :ptr, :ptr
graphene_triangle_equal proto :ptr, :ptr

endif
