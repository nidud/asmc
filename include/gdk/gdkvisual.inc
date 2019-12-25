ifndef __GDK_VISUAL_H__
__GDK_VISUAL_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

GDK_TYPE_VISUAL equ <gdk_visual_get_type>
GDK_VISUAL macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_VISUAL, GdkVisual))>
	endm
GDK_IS_VISUAL macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_VISUAL))>
	endm

.enum GdkVisualType {
  GDK_VISUAL_STATIC_GRAY,
  GDK_VISUAL_GRAYSCALE,
  GDK_VISUAL_STATIC_COLOR,
  GDK_VISUAL_PSEUDO_COLOR,
  GDK_VISUAL_TRUE_COLOR,
  GDK_VISUAL_DIRECT_COLOR
}

;GType
gdk_visual_get_type proto __cdecl

;gint
gdk_visual_get_best_depth proto __cdecl
;GdkVisualType
gdk_visual_get_best_type proto __cdecl
;GdkVisual*
gdk_visual_get_system proto __cdecl
;GdkVisual*
gdk_visual_get_best proto __cdecl
;GdkVisual*
gdk_visual_get_best_with_depth proto __cdecl \
		 depth: gint

;GdkVisual*
gdk_visual_get_best_with_type proto __cdecl \
	   visual_type: GdkVisualType

;GdkVisual*
gdk_visual_get_best_with_both proto __cdecl \
		 depth: gint,
	   visual_type: GdkVisualType


;void
gdk_query_depths proto __cdecl \
		depths: ptr gint,
		 count: ptr gint

;void
gdk_query_visual_types proto __cdecl \
	  visual_types: ptr GdkVisualType,
		 count: ptr gint


;GList*
gdk_list_visuals proto __cdecl

;GdkScreen
gdk_visual_get_screen proto __cdecl \
		visual: ptr GdkVisual


;GdkVisualType
gdk_visual_get_visual_type proto __cdecl \
		visual: ptr GdkVisual

;gint
gdk_visual_get_depth proto __cdecl \
		visual: ptr GdkVisual

;GdkByteOrder
gdk_visual_get_byte_order proto __cdecl \
		visual: ptr GdkVisual

;gint
gdk_visual_get_colormap_size proto __cdecl \
		visual: ptr GdkVisual

;gint
gdk_visual_get_bits_per_rgb proto __cdecl \
		visual: ptr GdkVisual

;void
gdk_visual_get_red_pixel_details proto __cdecl \
		visual: ptr GdkVisual,
		  mask: ptr guint32,
		 shift: ptr gint,
	     precision: ptr gint

;void
gdk_visual_get_green_pixel_details proto __cdecl \
		visual: ptr GdkVisual,
		  mask: ptr guint32,
		 shift: ptr gint,
	     precision: ptr gint

;void
gdk_visual_get_blue_pixel_details proto __cdecl \
		visual: ptr GdkVisual,
		  mask: ptr guint32,
		 shift: ptr gint,
	     precision: ptr gint

endif
