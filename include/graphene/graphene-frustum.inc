ifndef __GRAPHENE_FRUSTUM_H__
define __GRAPHENE_FRUSTUM_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-plane.inc

graphene_frustum_t      STRUC
planes                  graphene_plane_t 6 dup(<>)
graphene_frustum_t      ENDS

graphene_frustum_alloc proto
graphene_frustum_free proto :ptr

graphene_frustum_init proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
graphene_frustum_init_from_frustum proto :ptr, :ptr
graphene_frustum_init_from_matrix proto :ptr, :ptr

graphene_frustum_contains_point proto :ptr, :ptr

graphene_frustum_intersects_sphere proto :ptr, :ptr
graphene_frustum_intersects_box proto :ptr, :ptr

graphene_frustum_get_planes proto :ptr, :graphene_plane_t

graphene_frustum_equal proto :ptr, :ptr

endif
