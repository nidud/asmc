ifndef __GRAPHENE_VEC2_H__
define __GRAPHENE_VEC2_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc

_graphene_vec2_t        STRUC
x                       real4 ?
y                       real4 ?
_graphene_vec2_t        ENDS
graphene_vec2_t         typedef _graphene_vec2_t

graphene_vec2_alloc proto
graphene_vec2_free proto :ptr
graphene_vec2_init proto :ptr, :real4, :real4
graphene_vec2_init_from_vec2 proto :ptr, :ptr
graphene_vec2_init_from_float proto :ptr, :ptr
graphene_vec2_to_float proto :ptr, :ptr
graphene_vec2_add proto :ptr, :ptr, :ptr
graphene_vec2_subtract proto :ptr, :ptr, :ptr
graphene_vec2_multiply proto :ptr, :ptr, :ptr
graphene_vec2_divide proto :ptr, :ptr, :ptr
graphene_vec2_dot proto :ptr, :ptr
graphene_vec2_length proto :ptr
graphene_vec2_normalize proto :ptr, :ptr
graphene_vec2_scale proto :ptr, :real4, :ptr
graphene_vec2_negate proto :ptr, :ptr
graphene_vec2_near proto :ptr, :ptr, :real4
graphene_vec2_equal proto :ptr, :ptr

graphene_vec2_min proto :ptr, :ptr, :ptr
graphene_vec2_max proto :ptr, :ptr, :ptr
graphene_vec2_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_vec2_get_x proto :ptr
graphene_vec2_get_y proto :ptr

graphene_vec2_zero proto
graphene_vec2_one proto
graphene_vec2_x_axis proto
graphene_vec2_y_axis proto

endif

