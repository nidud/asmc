ifndef __GDK_POPUP_LAYOUT_H__
define __GDK_POPUP_LAYOUT_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkenums.inc
include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

.enum GdkAnchorHints {
  GDK_ANCHOR_FLIP_X   = 1 shl 0,
  GDK_ANCHOR_FLIP_Y   = 1 shl 1,
  GDK_ANCHOR_SLIDE_X  = 1 shl 2,
  GDK_ANCHOR_SLIDE_Y  = 1 shl 3,
  GDK_ANCHOR_RESIZE_X = 1 shl 4,
  GDK_ANCHOR_RESIZE_Y = 1 shl 5,
  GDK_ANCHOR_FLIP     = GDK_ANCHOR_FLIP_X or GDK_ANCHOR_FLIP_Y,
  GDK_ANCHOR_SLIDE    = GDK_ANCHOR_SLIDE_X or GDK_ANCHOR_SLIDE_Y,
  GDK_ANCHOR_RESIZE   = GDK_ANCHOR_RESIZE_X or GDK_ANCHOR_RESIZE_Y,
}

define GDK_TYPE_POPUP_LAYOUT <gdk_popup_layout_get_type ()>

gdk_popup_layout_get_type proto
gdk_popup_layout_new proto :ptr, :GdkGravity, :GdkGravity
gdk_popup_layout_ref proto :ptr
gdk_popup_layout_unref proto :ptr
gdk_popup_layout_copy proto :ptr
gdk_popup_layout_equal proto :ptr, :ptr
gdk_popup_layout_set_anchor_rect proto :ptr, :ptr
gdk_popup_layout_get_anchor_rect proto :ptr
gdk_popup_layout_set_rect_anchor proto :ptr, :GdkGravity
gdk_popup_layout_get_rect_anchor proto :ptr
gdk_popup_layout_set_surface_anchor proto :ptr, :GdkGravity
gdk_popup_layout_get_surface_anchor proto :ptr
gdk_popup_layout_set_anchor_hints proto :ptr, :GdkAnchorHints
gdk_popup_layout_get_anchor_hints proto :ptr
gdk_popup_layout_set_offset proto :ptr, :sdword, :sdword
gdk_popup_layout_get_offset proto :ptr, :ptr, :ptr
gdk_popup_layout_set_shadow_width proto :ptr, :sdword, :sdword, :sdword, :sdword
gdk_popup_layout_get_shadow_width proto :ptr, :ptr, :ptr, :ptr, :ptr

endif
