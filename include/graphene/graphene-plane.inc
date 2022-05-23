ifndef __GRAPHENE_PLANE_H__
define __GRAPHENE_PLANE_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec3.inc

_graphene_plane_t       STRUC
normal                  graphene_vec3_t <>
constant                real4 ?
_graphene_plane_t       ENDS
graphene_plane_t        typedef _graphene_plane_t

graphene_plane_alloc proto
graphene_plane_free proto :ptr

graphene_plane_init proto :ptr, :ptr, :real4
graphene_plane_init_from_vec4 proto :ptr, :ptr
graphene_plane_init_from_plane proto :ptr, :ptr
graphene_plane_init_from_point proto :ptr, :ptr, :ptr
graphene_plane_init_from_points proto :ptr, :ptr, :ptr, :ptr

graphene_plane_normalize proto :ptr, :ptr
graphene_plane_negate proto :ptr, :ptr
graphene_plane_equal proto :ptr, :ptr
graphene_plane_distance proto :ptr, :ptr

graphene_plane_get_normal proto :ptr, :ptr
graphene_plane_get_constant proto :ptr

graphene_plane_transform proto :ptr, :ptr, :ptr, :ptr

endif
