ifndef __GTK_SEPARATOR_H__
__GTK_SEPARATOR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_SEPARATOR equ <gtk_separator_get_type>
GTK_SEPARATOR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEPARATOR, GtkSeparator))>
	endm
GTK_SEPARATOR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SEPARATOR, GtkSeparatorClass))>
	endm
GTK_IS_SEPARATOR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEPARATOR))>
	endm
GTK_IS_SEPARATOR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SEPARATOR))>
	endm
GTK_SEPARATOR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SEPARATOR, GtkSeparatorClass))>
	endm

GtkSeparator		STRUC
widget			GtkWidget <>
priv			ptr_t ?
GtkSeparator		ENDS

GtkSeparatorClass	STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSeparatorClass	ENDS

;GType
gtk_separator_get_type proto __cdecl
;GtkWidget
gtk_separator_new proto __cdecl \
	   orientation: GtkOrientation

G_END_DECLS

endif
