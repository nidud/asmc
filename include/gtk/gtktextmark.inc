ifndef __GTK_TEXT_MARK_H__
define __GTK_TEXT_MARK_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

define GTK_TYPE_TEXT_MARK <gtk_text_mark_get_type>
GTK_TEXT_MARK macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_TEXT_MARK, GtkTextMark))>
  endm
GTK_TEXT_MARK_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TEXT_MARK, GtkTextMarkClass))>
  endm
GTK_IS_TEXT_MARK macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_TEXT_MARK))>
  endm
GTK_IS_TEXT_MARK_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TEXT_MARK))>
  endm
GTK_TEXT_MARK_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TEXT_MARK, GtkTextMarkClass))>
  endm

_GtkTextMark            struct
parent_instance         GObject <>
segm                    gpointer ?
_GtkTextMark            ends
GtkTextMark             typedef _GtkTextMark

_GtkTextMarkClass       struct
parent_class            GObjectClass <>
padding                 gpointer 8 dup(?)
_GtkTextMarkClass       ends
GtkTextMarkClass        typedef _GtkTextMarkClass

gtk_text_mark_get_type proto
gtk_text_mark_new proto :ptr, :gboolean
gtk_text_mark_set_visible proto :ptr, :gboolean
gtk_text_mark_get_visible proto :ptr
gtk_text_mark_get_name proto :ptr
gtk_text_mark_get_deleted proto :ptr
gtk_text_mark_get_buffer proto :ptr
gtk_text_mark_get_left_gravity proto :ptr

endif
