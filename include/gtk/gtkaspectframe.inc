ifndef __GTK_ASPECT_FRAME_H__
define __GTK_ASPECT_FRAME_H__


if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_ASPECT_FRAME <gtk_aspect_frame_get_type ()>
GTK_ASPECT_FRAME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ASPECT_FRAME, GtkAspectFrame))>
  endm
GTK_IS_ASPECT_FRAME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ASPECT_FRAME))>
  endm

gtk_aspect_frame_get_type proto
gtk_aspect_frame_new proto :real4, :real4, :real4, :gboolean

gtk_aspect_frame_set_xalign proto :ptr, :real4
gtk_aspect_frame_get_xalign proto :ptr

gtk_aspect_frame_set_yalign proto :ptr, :real4
gtk_aspect_frame_get_yalign proto :ptr

gtk_aspect_frame_set_ratio proto :ptr, :real4
gtk_aspect_frame_get_ratio proto :ptr

gtk_aspect_frame_set_obey_child proto :ptr, :gboolean
gtk_aspect_frame_get_obey_child proto :ptr

gtk_aspect_frame_set_child proto :ptr, :ptr
gtk_aspect_frame_get_child proto :ptr

endif
