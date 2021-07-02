ifndef __GTK_DRAWING_AREA_H__
__GTK_DRAWING_AREA_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_DRAWING_AREA equ <gtk_drawing_area_get_type>
GTK_DRAWING_AREA macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_DRAWING_AREA, GtkDrawingArea))>
	endm
GTK_DRAWING_AREA_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_DRAWING_AREA, GtkDrawingAreaClass))>
	endm
GTK_IS_DRAWING_AREA macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_DRAWING_AREA))>
	endm
GTK_IS_DRAWING_AREA_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_DRAWING_AREA))>
	endm
GTK_DRAWING_AREA_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_DRAWING_AREA, GtkDrawingAreaClass))>
	endm


GtkDrawingArea		STRUC
widget			GtkWidget <>
dummy			gpointer ?
GtkDrawingArea		ENDS

GtkDrawingAreaClass	STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkDrawingAreaClass	ENDS

;GType
gtk_drawing_area_get_type proto __cdecl
;GtkWidget*
gtk_drawing_area_new proto __cdecl

G_END_DECLS

endif
