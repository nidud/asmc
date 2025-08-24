ifndef __GRAPHENE_VEC4_H__
define __GRAPHENE_VEC4_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc

graphene_vec4_t         STRUC
x                       real4 ?
y                       real4 ?
z                       real4 ?
w                       real4 ?
graphene_vec4_t         ENDS

graphene_vec4_alloc proto
graphene_vec4_free proto :ptr
graphene_vec4_init proto :ptr, :real4, :real4, :real4, :real4
graphene_vec4_init_from_vec4 proto :ptr, :ptr
graphene_vec4_init_from_vec3 proto :ptr, :ptr, :real4
graphene_vec4_init_from_vec2 proto :ptr, :ptr, :real4, :real4
graphene_vec4_init_from_float proto :ptr, :ptr
graphene_vec4_to_float proto :ptr, :ptr
graphene_vec4_add proto :ptr, :ptr, :ptr
graphene_vec4_subtract proto :ptr, :ptr, :ptr
graphene_vec4_multiply proto :ptr, :ptr, :ptr
graphene_vec4_divide proto :ptr, :ptr, :ptr
graphene_vec4_dot proto :ptr, :ptr
graphene_vec4_length proto :ptr
graphene_vec4_normalize proto :ptr, :ptr
graphene_vec4_scale proto :ptr, :real4, :ptr
graphene_vec4_negate proto :ptr, :ptr
graphene_vec4_equal proto :ptr, :ptr
graphene_vec4_near proto :ptr, :ptr, :real4

graphene_vec4_min proto :ptr, :ptr, :ptr
graphene_vec4_max proto :ptr, :ptr, :ptr
graphene_vec4_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_vec4_get_x proto :ptr
graphene_vec4_get_y proto :ptr
graphene_vec4_get_z proto :ptr
graphene_vec4_get_w proto :ptr

graphene_vec4_get_xy proto :ptr, :ptr
graphene_vec4_get_xyz proto :ptr, :ptr

graphene_vec4_zero proto
graphene_vec4_one proto
graphene_vec4_x_axis proto
graphene_vec4_y_axis proto
graphene_vec4_z_axis proto
graphene_vec4_w_axis proto

endif

