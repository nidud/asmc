ifndef __GRAPHENE_QUAD_H__
define __GRAPHENE_QUAD_H__

include graphene/graphene-types.inc
include graphene/graphene-point.inc

graphene_quad_t         STRUC
points                  graphene_point_t 4 dup(<>)
graphene_quad_t         ENDS

graphene_quad_alloc proto
graphene_quad_free proto :ptr

graphene_quad_init proto :ptr, :ptr, :ptr, :ptr, :ptr
graphene_quad_init_from_rect proto :ptr, :ptr
graphene_quad_init_from_points proto :ptr, :graphene_point_t
graphene_quad_contains proto :ptr, :ptr
graphene_quad_bounds proto :ptr, :ptr
graphene_quad_get_point proto :ptr, :dword

endif

