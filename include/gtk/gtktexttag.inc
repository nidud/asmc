ifndef __GTK_TEXT_TAG_H__
define __GTK_TEXT_TAG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

;GtkTextIter             typedef _GtkTextIter
;GtkTextTagTable         typedef _GtkTextTagTable

define GTK_TYPE_TEXT_TAG <gtk_text_tag_get_type ()>
GTK_TEXT_TAG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TEXT_TAG, GtkTextTag))>
  endm
GTK_TEXT_TAG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_TAG, GtkTextTagClass))>
  endm
GTK_IS_TEXT_TAG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TEXT_TAG))>
  endm
GTK_IS_TEXT_TAG_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_TAG))>
  endm
GTK_TEXT_TAG_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_TAG, GtkTextTagClass))>
  endm

;GtkTextTagPrivate       typedef _GtkTextTagPrivate

_GtkTextTag             struct
parent_instance         GObject <>
priv                    ptr GtkTextTagPrivate ?
_GtkTextTag             ends
GtkTextTag              typedef _GtkTextTag

_GtkTextTagClass        struct
parent_class            GObjectClass <>
padding                 gpointer 8 dup(?)
_GtkTextTagClass        ends
GtkTextTagClass         typedef _GtkTextTagClass

gtk_text_tag_get_type proto
gtk_text_tag_new proto :ptr
gtk_text_tag_get_priority proto :ptr
gtk_text_tag_set_priority proto :ptr, :sdword
gtk_text_tag_changed proto :ptr, :gboolean

endif

