ifndef __GTK_ORIENTABLE_H__
__GTK_ORIENTABLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_ORIENTABLE equ <gtk_orientable_get_type>
GTK_ORIENTABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ORIENTABLE, GtkOrientable))>
	endm
GTK_ORIENTABLE_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_CAST ((vtable), GTK_TYPE_ORIENTABLE, GtkOrientableIface))>
	endm
GTK_IS_ORIENTABLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ORIENTABLE))>
	endm
GTK_IS_ORIENTABLE_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((vtable), GTK_TYPE_ORIENTABLE))>
	endm
GTK_ORIENTABLE_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_ORIENTABLE, GtkOrientableIface))>
	endm


GtkOrientableIface	STRUC
base_iface		GTypeInterface <>
GtkOrientableIface	ENDS

;GType
gtk_orientable_get_type proto __cdecl

;void
gtk_orientable_set_orientation proto __cdecl \
	    orientable: ptr GtkOrientable,
	   orientation: GtkOrientation

;GtkOrientation
gtk_orientable_get_orientation proto __cdecl \
	    orientable: ptr GtkOrientable

G_END_DECLS

endif
