ifndef __GRAPHENE_RECT_H__
define __GRAPHENE_RECT_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-point.inc
include graphene/graphene-size.inc
include graphene/graphene-vec2.inc

GRAPHENE_RECT_INIT macro _x,_y,_w,_h
  exitm<{ { _x, _y }, { _w, _h } }>
  endm

define GRAPHENE_RECT_INIT_ZERO <GRAPHENE_RECT_INIT (0.0, 0.0, 0.0, 0.0)>

graphene_rect_t         STRUC
origin                  graphene_point_t <>
size                    graphene_size_t <>
graphene_rect_t         ENDS

graphene_rect_alloc proto
graphene_rect_free proto :ptr
graphene_rect_init proto :ptr, :real4, :real4, :real4, :real4
graphene_rect_init_from_rect proto :ptr, :ptr

graphene_rect_equal proto :ptr, :ptr
graphene_rect_normalize proto :ptr
graphene_rect_normalize_r proto :ptr, :ptr
graphene_rect_get_center proto :ptr, :ptr
graphene_rect_get_top_left proto :ptr, :ptr
graphene_rect_get_top_right proto :ptr, :ptr
graphene_rect_get_bottom_right proto :ptr, :ptr
graphene_rect_get_bottom_left proto :ptr, :ptr
graphene_rect_get_vertices proto :ptr, :graphene_vec2_t
graphene_rect_get_x proto :ptr
graphene_rect_get_y proto :ptr
graphene_rect_get_width proto :ptr
graphene_rect_get_height proto :ptr
graphene_rect_get_area proto :ptr

graphene_rect_union proto :ptr, :ptr, :ptr
graphene_rect_intersection proto :ptr, :ptr, :ptr
graphene_rect_contains_point proto :ptr, :ptr
graphene_rect_contains_rect proto :ptr, :ptr
graphene_rect_offset proto :ptr, :real4, :real4
graphene_rect_offset_r proto :ptr, :real4, :real4, :ptr
graphene_rect_inset proto :ptr, :real4, :real4
graphene_rect_inset_r proto :ptr, :real4, :real4, :ptr
graphene_rect_round_to_pixel proto :ptr
graphene_rect_round proto :ptr, :ptr
graphene_rect_round_extents proto :ptr, :ptr
graphene_rect_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_rect_expand proto :ptr, :ptr, :ptr

graphene_rect_zero proto

graphene_rect_scale proto :ptr, :real4, :real4, :ptr

endif
