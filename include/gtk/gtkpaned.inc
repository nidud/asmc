ifndef __GTK_PANED_H__
__GTK_PANED_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_PANED equ <gtk_paned_get_type>
GTK_PANED macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PANED, GtkPaned))>
	endm
GTK_PANED_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_PANED, GtkPanedClass))>
	endm
GTK_IS_PANED macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PANED))>
	endm
GTK_IS_PANED_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_PANED))>
	endm
GTK_PANED_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_PANED, GtkPanedClass))>
	endm


GtkPaned		STRUC
container		GtkContainer <>
priv			ptr_t ?
GtkPaned		ENDS

GtkPanedClass		STRUC
parent_class		GtkContainerClass <>
cycle_child_focus	proc :ptr GtkPaned, :gboolean
toggle_handle_focus	proc :ptr GtkPaned
move_handle		proc :ptr GtkPaned, :GtkScrollType
cycle_handle_focus	proc :ptr GtkPaned, :gboolean
accept_position		proc :ptr GtkPaned
cancel_position		proc :ptr GtkPaned
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkPanedClass		ENDS


;GType
gtk_paned_get_type proto __cdecl
;GtkWidget
gtk_paned_new proto __cdecl \
	   orientation: GtkOrientation

;void
gtk_paned_add1 proto __cdecl \
		 paned: ptr GtkPaned,
		 child: ptr GtkWidget

;void
gtk_paned_add2 proto __cdecl \
		 paned: ptr GtkPaned,
		 child: ptr GtkWidget

;void
gtk_paned_pack1 proto __cdecl \
		 paned: ptr GtkPaned,
		 child: ptr GtkWidget,
		resize: gboolean,
		shrink: gboolean

;void
gtk_paned_pack2 proto __cdecl \
		 paned: ptr GtkPaned,
		 child: ptr GtkWidget,
		resize: gboolean,
		shrink: gboolean


;gint
gtk_paned_get_position proto __cdecl \
		 paned: ptr GtkPaned

;void
gtk_paned_set_position proto __cdecl \
		 paned: ptr GtkPaned,
	      position: gint


;GtkWidget
gtk_paned_get_child1 proto __cdecl \
		 paned: ptr GtkPaned

;GtkWidget
gtk_paned_get_child2 proto __cdecl \
		 paned: ptr GtkPaned


;GdkWindow
gtk_paned_get_handle_window proto __cdecl \
		 paned: ptr GtkPaned


;void
gtk_paned_set_wide_handle proto __cdecl \
		 paned: ptr GtkPaned,
		  wide: gboolean

;gboolean
gtk_paned_get_wide_handle proto __cdecl \
		 paned: ptr GtkPaned

G_END_DECLS

endif
