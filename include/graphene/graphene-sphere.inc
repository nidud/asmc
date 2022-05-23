ifndef __GRAPHENE_SPHERE_H__
define __GRAPHENE_SPHERE_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec3.inc

_graphene_sphere_t      STRUC
center                  graphene_vec3_t <>
radius                  real4 ?
_graphene_sphere_t      ENDS
graphene_sphere_t       typedef _graphene_sphere_t

graphene_sphere_alloc proto
graphene_sphere_free proto :ptr

graphene_sphere_init proto :ptr, :ptr, :real4

graphene_sphere_init_from_points proto :ptr, :dword, :ptr, :ptr
graphene_sphere_init_from_vectors proto :ptr, :dword, :ptr, :ptr

graphene_sphere_get_center proto :ptr, :ptr
graphene_sphere_get_radius proto :ptr
graphene_sphere_is_empty proto :ptr
graphene_sphere_equal proto :ptr, :ptr
graphene_sphere_contains_point proto :ptr, :ptr
graphene_sphere_distance proto :ptr, :ptr
graphene_sphere_get_bounding_box proto :ptr, :ptr
graphene_sphere_translate proto :ptr, :ptr, :ptr

endif
