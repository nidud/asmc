ifndef __GTK_BIN_H__
__GTK_BIN_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_BIN equ <gtk_bin_get_type>
GTK_BIN macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BIN, GtkBin))>
	endm
GTK_BIN_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_BIN, GtkBinClass))>
	endm
GTK_IS_BIN macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BIN))>
	endm
GTK_IS_BIN_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BIN))>
	endm
GTK_BIN_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BIN, GtkBinClass))>
	endm


GtkBin			STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkBin			ENDS

GtkBinClass		STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkBinClass		ENDS


;GType
gtk_bin_get_type proto __cdecl

;GtkWidget
gtk_bin_get_child proto __cdecl \
		   bin: ptr GtkBin

_gtk_bin_set_child proto __cdecl \
		   bin: ptr GtkBin,
		widget: ptr GtkWidget


G_END_DECLS

endif
