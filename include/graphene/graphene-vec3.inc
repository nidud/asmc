ifndef __GRAPHENE_VEC3_H__
define __GRAPHENE_VEC3_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc

_graphene_vec3_t        STRUC
x                       real4 ?
y                       real4 ?
z                       real4 ?
_graphene_vec3_t        ENDS
graphene_vec3_t         typedef _graphene_vec3_t

graphene_vec3_alloc proto
graphene_vec3_free proto :ptr
graphene_vec3_init proto :ptr, :real4, :real4, :real4
graphene_vec3_init_from_vec3 proto :ptr, :ptr
graphene_vec3_init_from_float proto :ptr, :ptr
graphene_vec3_to_float proto :ptr, :ptr
graphene_vec3_add proto :ptr, :ptr, :ptr
graphene_vec3_subtract proto :ptr, :ptr, :ptr
graphene_vec3_multiply proto :ptr, :ptr, :ptr
graphene_vec3_divide proto :ptr, :ptr, :ptr
graphene_vec3_cross proto :ptr, :ptr, :ptr
graphene_vec3_dot proto :ptr, :ptr
graphene_vec3_length proto :ptr
graphene_vec3_normalize proto :ptr, :ptr
graphene_vec3_scale proto :ptr, :real4, :ptr
graphene_vec3_negate proto :ptr, :ptr
graphene_vec3_equal proto :ptr, :ptr
graphene_vec3_near proto :ptr, :ptr, :real4
graphene_vec3_min proto :ptr, :ptr, :ptr
graphene_vec3_max proto :ptr, :ptr, :ptr
graphene_vec3_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_vec3_get_x proto :ptr
graphene_vec3_get_y proto :ptr
graphene_vec3_get_z proto :ptr

graphene_vec3_get_xy proto :ptr, :ptr
graphene_vec3_get_xy0 proto :ptr, :ptr
graphene_vec3_get_xyz0 proto :ptr, :ptr
graphene_vec3_get_xyz1 proto :ptr, :ptr
graphene_vec3_get_xyzw proto :ptr, :real4, :ptr

graphene_vec3_zero proto
graphene_vec3_one proto
graphene_vec3_x_axis proto
graphene_vec3_y_axis proto
graphene_vec3_z_axis proto

endif

