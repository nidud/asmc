ifndef __GTK_FRAME_H__
define __GTK_FRAME_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_FRAME <gtk_frame_get_type>
GTK_FRAME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FRAME, GtkFrame))>
  endm
GTK_FRAME_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FRAME, GtkFrameClass))>
  endm
GTK_IS_FRAME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FRAME))>
  endm
GTK_IS_FRAME_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FRAME))>
  endm
GTK_FRAME_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FRAME, GtkFrameClass))>
  endm

_GtkFrame               struct
parent_instance         GtkWidget <>
_GtkFrame               ends
GtkFrame                typedef _GtkFrame


_GtkFrameClass          struct
parent_class            GtkWidgetClass <>
compute_child_allocation proc :ptr, :ptr
padding                 gpointer 8 dup(?)
_GtkFrameClass          ends
GtkFrameClass           typedef _GtkFrameClass


gtk_frame_get_type proto
gtk_frame_new proto :ptr

gtk_frame_set_label proto :ptr, :ptr
gtk_frame_get_label proto :ptr

gtk_frame_set_label_widget proto :ptr, :ptr
gtk_frame_get_label_widget proto :ptr
gtk_frame_set_label_align proto :ptr, :real4
gtk_frame_get_label_align proto :ptr

gtk_frame_set_child proto :ptr, :ptr
gtk_frame_get_child proto :ptr

endif
