ifndef __GRAPHENE_RAY_H__
define __GRAPHENE_RAY_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec3.inc

graphene_ray_t          STRUC
origin                  graphene_vec3_t <>
direction               graphene_vec3_t <>
graphene_ray_t          ENDS

.enum graphene_ray_intersection_kind_t {
  GRAPHENE_RAY_INTERSECTION_KIND_NONE,
  GRAPHENE_RAY_INTERSECTION_KIND_ENTER,
  GRAPHENE_RAY_INTERSECTION_KIND_LEAVE,
}

graphene_ray_alloc proto
graphene_ray_free proto :ptr

graphene_ray_init proto :ptr, :ptr, :ptr
graphene_ray_init_from_ray proto :ptr, :ptr
graphene_ray_init_from_vec3 proto :ptr, :ptr, :ptr
graphene_ray_get_origin proto :ptr, :ptr
graphene_ray_get_direction proto :ptr, :ptr

graphene_ray_get_position_at proto :ptr, :real4, :ptr
graphene_ray_get_distance_to_point proto :ptr, :ptr
graphene_ray_get_distance_to_plane proto :ptr, :ptr

graphene_ray_equal proto :ptr, :ptr

graphene_ray_get_closest_point_to_point proto :ptr, :ptr, :ptr

graphene_ray_intersect_sphere proto :ptr, :ptr, :ptr
graphene_ray_intersects_sphere proto :ptr, :ptr
graphene_ray_intersect_box proto :ptr, :ptr, :ptr
graphene_ray_intersects_box proto :ptr, :ptr
graphene_ray_intersect_triangle proto :ptr, :ptr, :ptr
graphene_ray_intersects_triangle proto :ptr, :ptr

endif
