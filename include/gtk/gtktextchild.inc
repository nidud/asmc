ifndef __GTK_TEXT_CHILD_H__
__GTK_TEXT_CHILD_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include glib-object.inc

GTK_TYPE_TEXT_CHILD_ANCHOR equ <gtk_text_child_anchor_get_type>
GTK_TEXT_CHILD_ANCHOR macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_TEXT_CHILD_ANCHOR, GtkTextChildAnchor))>
	endm
GTK_TEXT_CHILD_ANCHOR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_CHILD_ANCHOR, GtkTextChildAnchorClass))>
	endm
GTK_IS_TEXT_CHILD_ANCHOR macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_TEXT_CHILD_ANCHOR))>
	endm
GTK_IS_TEXT_CHILD_ANCHOR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_CHILD_ANCHOR))>
	endm
GTK_TEXT_CHILD_ANCHOR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_CHILD_ANCHOR, GtkTextChildAnchorClass))>
	endm

GtkTextChildAnchor	STRUC
parent_instance		GObject <>
_segment		gpointer ?
GtkTextChildAnchor	ENDS

GtkTextChildAnchorClass STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTextChildAnchorClass ENDS

;GType
gtk_text_child_anchor_get_type proto __cdecl

;GtkTextChildAnchor*
gtk_text_child_anchor_new proto __cdecl

;GList*
gtk_text_child_anchor_get_widgets proto __cdecl \
		anchor: ptr GtkTextChildAnchor

;gboolean
gtk_text_child_anchor_get_deleted proto __cdecl \
		anchor: ptr GtkTextChildAnchor

endif
