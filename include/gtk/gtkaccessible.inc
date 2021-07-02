ifndef __GTK_ACCESSIBLE_H__
__GTK_ACCESSIBLE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include atk/atk.inc
include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_ACCESSIBLE equ <gtk_accessible_get_type>
GTK_ACCESSIBLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ACCESSIBLE, GtkAccessible))>
	endm
GTK_ACCESSIBLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ACCESSIBLE, GtkAccessibleClass))>
	endm
GTK_IS_ACCESSIBLE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ACCESSIBLE))>
	endm
GTK_IS_ACCESSIBLE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ACCESSIBLE))>
	endm
GTK_ACCESSIBLE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ACCESSIBLE, GtkAccessibleClass))>
	endm


GtkAccessible		STRUC
parent			AtkObject <>
priv			ptr_t ?
GtkAccessible		ENDS

GtkAccessibleClass	STRUC
parent_class		AtkObjectClass <>
connect_widget_destroyed proc :ptr GtkAccessible
widget_set		proc :ptr GtkAccessible
widget_unset		proc :ptr GtkAccessible
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkAccessibleClass	ENDS

;GType
gtk_accessible_get_type proto __cdecl

;void
gtk_accessible_set_widget proto __cdecl \
	    accessible: ptr GtkAccessible,
		widget: ptr GtkWidget

;GtkWidget
gtk_accessible_get_widget proto __cdecl \
	    accessible: ptr GtkAccessible


;void
gtk_accessible_connect_widget_destroyed proto __cdecl \
	    accessible: ptr GtkAccessible


G_END_DECLS

endif
