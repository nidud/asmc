ifndef __GSK_ROUNDED_RECT_H__
define __GSK_ROUNDED_RECT_H__

if not defined (__GSK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gsk/gsk.h can be included directly.">
endif

include gsk/gsktypes.inc

GSK_ROUNDED_RECT_INIT macro _x,_y,_w,_h
  exitm<.err>
  endm
if 0
_GskRoundedRect         STRUC
bounds                  graphene_rect_t <>
corner                  graphene_size_t 4 dup(?)
_GskRoundedRect         ENDS
GskRoundedRect          typedef _GskRoundedRect
endif

gsk_rounded_rect_init proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gsk_rounded_rect_init_copy proto :ptr, :ptr
gsk_rounded_rect_init_from_rect proto :ptr, :ptr, :real4

gsk_rounded_rect_normalize proto :ptr

gsk_rounded_rect_offset proto :ptr, :real4, :real4
gsk_rounded_rect_shrink proto :ptr, :real4, :real4, :real4, :real4

gsk_rounded_rect_is_rectilinear proto :ptr
gsk_rounded_rect_contains_point proto :ptr, :ptr
gsk_rounded_rect_contains_rect proto :ptr, :ptr
gsk_rounded_rect_intersects_rect proto :ptr, :ptr

endif
