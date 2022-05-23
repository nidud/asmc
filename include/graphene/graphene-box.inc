ifndef __GRAPHENE_BOX_H__
define __GRAPHENE_BOX_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec3.inc

_graphene_box_t         STRUC
min                     graphene_vec3_t <>
max                     graphene_vec3_t <>
_graphene_box_t         ENDS
graphene_box_t          typedef _graphene_box_t

graphene_box_alloc proto
graphene_box_free proto :ptr

graphene_box_init proto :ptr, :ptr, :ptr
graphene_box_init_from_points proto :ptr, :dword, :ptr
graphene_box_init_from_vectors proto :ptr, :dword, :ptr
graphene_box_init_from_box proto :ptr, :ptr
graphene_box_init_from_vec3 proto :ptr, :ptr, :ptr

graphene_box_expand proto :ptr, :ptr, :ptr
graphene_box_expand_vec3 proto :ptr, :ptr, :ptr
graphene_box_expand_scalar proto :ptr, :real4, :ptr
graphene_box_union proto :ptr, :ptr, :ptr
graphene_box_intersection proto :ptr, :ptr, :ptr

graphene_box_get_width proto :ptr
graphene_box_get_height proto :ptr
graphene_box_get_depth proto :ptr
graphene_box_get_size proto :ptr, :ptr
graphene_box_get_center proto :ptr, :ptr
graphene_box_get_min proto :ptr, :ptr
graphene_box_get_max proto :ptr, :ptr
graphene_box_get_vertices proto :ptr, :graphene_vec3_t
graphene_box_get_bounding_sphere proto :ptr, :ptr

graphene_box_contains_point proto :ptr, :ptr
graphene_box_contains_box proto :ptr, :ptr

graphene_box_equal proto :ptr, :ptr

graphene_box_zero proto
graphene_box_one proto
graphene_box_minus_one proto
graphene_box_one_minus_one proto
graphene_box_infinite proto
graphene_box_empty proto

endif

