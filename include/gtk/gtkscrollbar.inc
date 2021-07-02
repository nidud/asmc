ifndef __GTK_SCROLLBAR_H__
__GTK_SCROLLBAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkrange.inc

G_BEGIN_DECLS

GTK_TYPE_SCROLLBAR equ <gtk_scrollbar_get_type>
GTK_SCROLLBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCROLLBAR, GtkScrollbar))>
	endm
GTK_SCROLLBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCROLLBAR, GtkScrollbarClass))>
	endm
GTK_IS_SCROLLBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCROLLBAR))>
	endm
GTK_IS_SCROLLBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCROLLBAR))>
	endm
GTK_SCROLLBAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCROLLBAR, GtkScrollbarClass))>
	endm

GtkScrollbar		STRUC
range			GtkRange <>
GtkScrollbar		ENDS

GtkScrollbarClass	STRUC
parent_class		GtkRangeClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkScrollbarClass	ENDS


;GType
gtk_scrollbar_get_type proto __cdecl
;GtkWidget
gtk_scrollbar_new proto __cdecl \
	   orientation: GtkOrientation,
	    adjustment: ptr GtkAdjustment

G_END_DECLS

endif
