ifndef __GTK_OVERLAY_H__
__GTK_OVERLAY_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_OVERLAY equ <gtk_overlay_get_type>
GTK_OVERLAY macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_OVERLAY, GtkOverlay))>
	endm
GTK_OVERLAY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_OVERLAY, GtkOverlayClass))>
	endm
GTK_IS_OVERLAY macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_OVERLAY))>
	endm
GTK_IS_OVERLAY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_OVERLAY))>
	endm
GTK_OVERLAY_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_OVERLAY, GtkOverlayClass))>
	endm

GtkOverlay		STRUC
parent			GtkBin <>
priv			ptr_t ?
GtkOverlay		ENDS

GtkOverlayClass		STRUC
parent_class		GtkBinClass <>
get_child_position	proc :ptr GtkOverlay, :ptr GtkWidget, :ptr GtkAllocation
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
_gtk_reserved5		proc
_gtk_reserved6		proc
_gtk_reserved7		proc
_gtk_reserved8		proc
GtkOverlayClass		ENDS

;GType
gtk_overlay_get_type proto __cdecl
;GtkWidget
gtk_overlay_new proto __cdecl
;void
gtk_overlay_add_overlay proto __cdecl \
	       overlay: ptr GtkOverlay,
		widget: ptr GtkWidget

;void
gtk_overlay_reorder_overlay proto __cdecl \
	       overlay: ptr GtkOverlay,
		 child: ptr GtkWidget,
	      position: gint

;gboolean
gtk_overlay_get_overlay_pass_through proto __cdecl \
	       overlay: ptr GtkOverlay,
		widget: ptr GtkWidget

;void
gtk_overlay_set_overlay_pass_through proto __cdecl \
	       overlay: ptr GtkOverlay,
		widget: ptr GtkWidget,
	  pass_through: gboolean

G_END_DECLS

endif
