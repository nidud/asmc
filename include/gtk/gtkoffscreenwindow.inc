ifndef __GTK_OFFSCREEN_WINDOW_H__
__GTK_OFFSCREEN_WINDOW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

G_BEGIN_DECLS

GTK_TYPE_OFFSCREEN_WINDOW equ <gtk_offscreen_window_get_type>
GTK_OFFSCREEN_WINDOW macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_OFFSCREEN_WINDOW, GtkOffscreenWindow))>
	endm
GTK_OFFSCREEN_WINDOW_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_OFFSCREEN_WINDOW, GtkOffscreenWindowClass))>
	endm
GTK_IS_OFFSCREEN_WINDOW macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_OFFSCREEN_WINDOW))>
	endm
GTK_IS_OFFSCREEN_WINDOW_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_OFFSCREEN_WINDOW))>
	endm
GTK_OFFSCREEN_WINDOW_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_OFFSCREEN_WINDOW, GtkOffscreenWindowClass))>
	endm

GtkOffscreenWindow	STRUC
parent_object		GtkWindow <>
GtkOffscreenWindow	ENDS

GtkOffscreenWindowClass STRUC
parent_class		GtkWindowClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkOffscreenWindowClass ENDS

;GType
gtk_offscreen_window_get_type proto __cdecl

;GtkWidget
gtk_offscreen_window_new proto __cdecl
;cairo_surface_t
gtk_offscreen_window_get_surface proto __cdecl \
	     offscreen: ptr GtkOffscreenWindow

;GdkPixbuf
gtk_offscreen_window_get_pixbuf proto __cdecl \
	     offscreen: ptr GtkOffscreenWindow

G_END_DECLS

endif
