ifndef __GTK_EVENT_BOX_H__
__GTK_EVENT_BOX_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_EVENT_BOX equ <gtk_event_box_get_type>
GTK_EVENT_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EVENT_BOX, GtkEventBox))>
	endm
GTK_EVENT_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_EVENT_BOX, GtkEventBoxClass))>
	endm
GTK_IS_EVENT_BOX macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EVENT_BOX))>
	endm
GTK_IS_EVENT_BOX_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_EVENT_BOX))>
	endm
GTK_EVENT_BOX_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_EVENT_BOX, GtkEventBoxClass))>
	endm

GtkEventBox		STRUC
bin			GtkBin <>
priv			ptr_t ?
GtkEventBox		ENDS

GtkEventBoxClass	STRUC
parent_class		GtkBinClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkEventBoxClass	ENDS

;GType
gtk_event_box_get_type proto __cdecl
;GtkWidget*
gtk_event_box_new proto __cdecl
;gboolean
gtk_event_box_get_visible_window proto __cdecl \
	     event_box: ptr GtkEventBox

;void
gtk_event_box_set_visible_window proto __cdecl \
	     event_box: ptr GtkEventBox,
	visible_window: gboolean

;gboolean
gtk_event_box_get_above_child proto __cdecl \
	     event_box: ptr GtkEventBox

;void
gtk_event_box_set_above_child proto __cdecl \
	     event_box: ptr GtkEventBox,
	   above_child: gboolean


G_END_DECLS

endif
