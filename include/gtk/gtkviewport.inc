ifndef __GTK_VIEWPORT_H__
__GTK_VIEWPORT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_VIEWPORT equ <gtk_viewport_get_type>
GTK_VIEWPORT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VIEWPORT, GtkViewport))>
	endm
GTK_VIEWPORT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_VIEWPORT, GtkViewportClass))>
	endm
GTK_IS_VIEWPORT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VIEWPORT))>
	endm
GTK_IS_VIEWPORT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_VIEWPORT))>
	endm
GTK_VIEWPORT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_VIEWPORT, GtkViewportClass))>
	endm


GtkViewport		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkViewport		ENDS

GtkViewportClass	STRUC
parent_class		GtkBinClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkViewportClass	ENDS

;GType
gtk_viewport_get_type proto __cdecl
;GtkWidget*
gtk_viewport_new proto __cdecl \
	   hadjustment: ptr GtkAdjustment,
	   vadjustment: ptr GtkAdjustment


;GtkAdjustment*
gtk_viewport_get_hadjustment proto __cdecl \
	      viewport: ptr GtkViewport

;GtkAdjustment*
gtk_viewport_get_vadjustment proto __cdecl \
	      viewport: ptr GtkViewport

;void
gtk_viewport_set_hadjustment proto __cdecl \
	      viewport: ptr GtkViewport,
	    adjustment: ptr GtkAdjustment

;void
gtk_viewport_set_vadjustment proto __cdecl \
	      viewport: ptr GtkViewport,
	    adjustment: ptr GtkAdjustment


;void
gtk_viewport_set_shadow_type proto __cdecl \
	      viewport: ptr GtkViewport,
		  type: GtkShadowType

;GtkShadowType
gtk_viewport_get_shadow_type proto __cdecl \
	      viewport: ptr GtkViewport

;GdkWindow*
gtk_viewport_get_bin_window proto __cdecl \
	      viewport: ptr GtkViewport

;GdkWindow*
gtk_viewport_get_view_window proto __cdecl \
	      viewport: ptr GtkViewport

G_END_DECLS

endif
