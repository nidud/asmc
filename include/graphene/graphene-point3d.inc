ifndef __GRAPHENE_POINT3D_H__
define __GRAPHENE_POINT3D_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc

GRAPHENE_POINT3D_INIT macro _x,_y,_z
  exitm<{ _x, _y, _z }>
  endm

define GRAPHENE_POINT3D_INIT_ZERO      <GRAPHENE_POINT3D_INIT (0.0, 0.0, 0.0)>

graphene_point3d_t      STRUC
x                       real4 ?
y                       real4 ?
z                       real4 ?
graphene_point3d_t      ENDS

graphene_point3d_alloc proto
graphene_point3d_free proto :ptr

graphene_point3d_init proto :ptr, :real4, :real4, :real4
graphene_point3d_init_from_point proto :ptr, :ptr
graphene_point3d_init_from_vec3 proto :ptr, :ptr
graphene_point3d_to_vec3 proto :ptr, :ptr

graphene_point3d_equal proto :ptr, :ptr
graphene_point3d_near proto :ptr, :ptr, :real4

graphene_point3d_scale proto :ptr, :real4, :ptr
graphene_point3d_cross proto :ptr, :ptr, :ptr
graphene_point3d_dot proto :ptr, :ptr
graphene_point3d_length proto :ptr
graphene_point3d_normalize proto :ptr, :ptr
graphene_point3d_distance proto :ptr, :ptr, :ptr

graphene_point3d_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_point3d_normalize_viewport proto :ptr, :ptr, :real4, :real4, :ptr

graphene_point3d_zero proto

endif

