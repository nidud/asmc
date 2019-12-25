ifndef __GTK_SPINNER_H__
__GTK_SPINNER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_SPINNER equ <gtk_spinner_get_type>
GTK_SPINNER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SPINNER, GtkSpinner))>
	endm
GTK_SPINNER_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_TYPE_SPINNER,  GtkSpinnerClass))>
	endm
GTK_IS_SPINNER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SPINNER))>
	endm
GTK_IS_SPINNER_CLASS macro obj
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((obj), GTK_TYPE_SPINNER))>
	endm
GTK_SPINNER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SPINNER, GtkSpinnerClass))>
	endm

GtkSpinner		STRUC
parent			GtkWidget <>
priv			ptr_t ?
GtkSpinner		ENDS

GtkSpinnerClass		STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSpinnerClass		ENDS

;GType
gtk_spinner_get_type proto __cdecl
;GtkWidget
gtk_spinner_new proto __cdecl
;void
gtk_spinner_start proto __cdecl \
	       spinner: ptr GtkSpinner

;void
gtk_spinner_stop proto __cdecl \
	       spinner: ptr GtkSpinner

G_END_DECLS

endif
