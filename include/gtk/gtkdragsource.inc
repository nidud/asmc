ifndef __GTK_DRAG_SOURCE_H__
define __GTK_DRAG_SOURCE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_DRAG_SOURCE <gtk_drag_source_get_type ()>
GTK_DRAG_SOURCE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_DRAG_SOURCE, GtkDragSource))>
  endm
GTK_DRAG_SOURCE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_DRAG_SOURCE, GtkDragSourceClass))>
  endm
GTK_IS_DRAG_SOURCE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_DRAG_SOURCE))>
  endm
GTK_IS_DRAG_SOURCE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_DRAG_SOURCE))>
  endm
GTK_DRAG_SOURCE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_DRAG_SOURCE, GtkDragSourceClass))>
  endm

;GtkDragSource           typedef _GtkDragSource
;GtkDragSourceClass      typedef _GtkDragSourceClass

gtk_drag_source_get_type proto
gtk_drag_source_new proto
gtk_drag_source_set_content proto :ptr, :ptr
gtk_drag_source_get_content proto :ptr
gtk_drag_source_set_actions proto :ptr, :GdkDragAction
gtk_drag_source_get_actions proto :ptr
gtk_drag_source_set_icon proto :ptr, :ptr, :sdword, :sdword
gtk_drag_source_drag_cancel proto :ptr
gtk_drag_source_get_drag proto :ptr
gtk_drag_check_threshold proto :ptr, :sdword, :sdword, :sdword, :sdword

endif
