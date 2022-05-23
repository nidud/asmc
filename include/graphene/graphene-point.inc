ifndef __GRAPHENE_POINT_H__
define __GRAPHENE_POINT_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc

GRAPHENE_POINT_INIT macro _x,_y
  exitm<{ _x, _y }>
  endm

define GRAPHENE_POINT_INIT_ZERO        <GRAPHENE_POINT_INIT (0.0, 0.0)>

_graphene_point_t       STRUC
x                       real4 ?
y                       real4 ?
_graphene_point_t       ENDS
graphene_point_t        typedef _graphene_point_t

graphene_point_alloc proto
graphene_point_free proto :ptr

graphene_point_init proto :ptr, :real4, :real4
graphene_point_init_from_point proto :ptr, :ptr
graphene_point_init_from_vec2 proto :ptr, :ptr
graphene_point_equal proto :ptr, :ptr

graphene_point_distance proto :ptr, :ptr, :ptr, :ptr
graphene_point_near proto :ptr, :ptr, :real4
graphene_point_interpolate proto :ptr, :ptr, :real8, :ptr
graphene_point_to_vec2 proto :ptr, :ptr
graphene_point_zero proto

endif

