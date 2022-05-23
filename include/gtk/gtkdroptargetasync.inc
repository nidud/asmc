ifndef __GTK_DROP_TARGET_ASYNC_H__
define __GTK_DROP_TARGET_ASYNC_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

;GtkDropTargetAsync      typedef _GtkDropTargetAsync
;GtkDropTargetAsyncClass typedef _GtkDropTargetAsyncClass


define GTK_TYPE_DROP_TARGET_ASYNC <gtk_drop_target_async_get_type>
GTK_DROP_TARGET_ASYNC macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_DROP_TARGET_ASYNC, GtkDropTargetAsync))>
  endm
GTK_DROP_TARGET_ASYNC_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_DROP_TARGET_ASYNC, GtkDropTargetAsyncClass))>
  endm
GTK_IS_DROP_TARGET_ASYNC macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_DROP_TARGET_ASYNC))>
  endm
GTK_IS_DROP_TARGET_ASYNC_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_DROP_TARGET_ASYNC))>
  endm
GTK_DROP_TARGET_ASYNC_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_DROP_TARGET_ASYNC, GtkDropTargetAsyncClass))>
  endm

gtk_drop_target_async_get_type proto
gtk_drop_target_async_new proto :ptr, :GdkDragAction
gtk_drop_target_async_set_formats proto :ptr, :ptr
gtk_drop_target_async_get_formats proto :ptr
gtk_drop_target_async_set_actions proto :ptr, :GdkDragAction
gtk_drop_target_async_get_actions proto :ptr
gtk_drop_target_async_reject_drop proto :ptr, :ptr

endif
