ifndef __GTK_INVISIBLE_H__
__GTK_INVISIBLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_INVISIBLE equ <gtk_invisible_get_type>
GTK_INVISIBLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_INVISIBLE, GtkInvisible))>
	endm
GTK_INVISIBLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_INVISIBLE, GtkInvisibleClass))>
	endm
GTK_IS_INVISIBLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_INVISIBLE))>
	endm
GTK_IS_INVISIBLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_INVISIBLE))>
	endm
GTK_INVISIBLE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_INVISIBLE, GtkInvisibleClass))>
	endm


GtkInvisible		STRUC
widget			GtkWidget <>
priv			ptr_t ?
GtkInvisible		ENDS

GtkInvisibleClass	STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkInvisibleClass	ENDS

;GType
gtk_invisible_get_type proto __cdecl

;GtkWidget*
gtk_invisible_new proto __cdecl
;GtkWidget*
gtk_invisible_new_for_screen proto __cdecl \
		screen: ptr GdkScreen

;void
gtk_invisible_set_screen proto __cdecl \
	     invisible: ptr GtkInvisible,
		screen: ptr GdkScreen

;GdkScreen*
gtk_invisible_get_screen proto __cdecl \
	     invisible: ptr GtkInvisible

G_END_DECLS

endif
