ifndef __GTK_LAYOUT_H__
__GTK_LAYOUT_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_LAYOUT equ <gtk_layout_get_type>
GTK_LAYOUT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LAYOUT, GtkLayout))>
	endm
GTK_LAYOUT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LAYOUT, GtkLayoutClass))>
	endm
GTK_IS_LAYOUT macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LAYOUT))>
	endm
GTK_IS_LAYOUT_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LAYOUT))>
	endm
GTK_LAYOUT_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LAYOUT, GtkLayoutClass))>
	endm

GtkLayout		STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkLayout		ENDS

GtkLayoutClass		STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkLayoutClass		ENDS

;GType
gtk_layout_get_type proto __cdecl
;GtkWidget*
gtk_layout_new proto __cdecl \
	   hadjustment: ptr GtkAdjustment,
	   vadjustment: ptr GtkAdjustment

;GdkWindow*
gtk_layout_get_bin_window proto __cdecl \
		layout: ptr GtkLayout

;void
gtk_layout_put proto __cdecl \
		layout: ptr GtkLayout,
	  child_widget: ptr GtkWidget,
		     x: gint,
		     y: gint


;void
gtk_layout_move proto __cdecl \
		layout: ptr GtkLayout,
	  child_widget: ptr GtkWidget,
		     x: gint,
		     y: gint


;void
gtk_layout_set_size proto __cdecl \
		layout: ptr GtkLayout,
		 width: guint,
		height: guint

;void
gtk_layout_get_size proto __cdecl \
		layout: ptr GtkLayout,
		 width: ptr guint,
		height: ptr guint


;GtkAdjustment*
gtk_layout_get_hadjustment proto __cdecl \
		layout: ptr GtkLayout

;GtkAdjustment*
gtk_layout_get_vadjustment proto __cdecl \
		layout: ptr GtkLayout

;void
gtk_layout_set_hadjustment proto __cdecl \
		layout: ptr GtkLayout,
	    adjustment: ptr GtkAdjustment

;void
gtk_layout_set_vadjustment proto __cdecl \
		layout: ptr GtkLayout,
	    adjustment: ptr GtkAdjustment

G_END_DECLS

endif
