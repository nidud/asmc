ifndef __GTK_TEXT_CHILD_H__
define __GTK_TEXT_CHILD_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include glib-object.inc
include gtk/gtkwidget.inc

define GTK_TYPE_TEXT_CHILD_ANCHOR <gtk_text_child_anchor_get_type ()>
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

_GtkTextChildAnchor     struct
parent_instance         GObject <>
_segment                gpointer ?
_GtkTextChildAnchor     ends
GtkTextChildAnchor      typedef _GtkTextChildAnchor

_GtkTextChildAnchorClass struct
parent_class            GObjectClass <>
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkTextChildAnchorClass ends
GtkTextChildAnchorClass typedef _GtkTextChildAnchorClass

gtk_text_child_anchor_get_type proto
gtk_text_child_anchor_new proto
gtk_text_child_anchor_new_with_replacement proto :ptr
gtk_text_child_anchor_get_widgets proto :ptr, :ptr
gtk_text_child_anchor_get_deleted proto :ptr

endif
