ifndef __GTK_DROP_TARGET_H__
define __GTK_DROP_TARGET_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

;GtkDropTarget           typedef _GtkDropTarget

define GTK_TYPE_DROP_TARGET <gtk_drop_target_get_type>
GTK_DROP_TARGET macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_DROP_TARGET, GtkDropTarget))>
  endm
GTK_DROP_TARGET_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_DROP_TARGET, GtkDropTargetClass))>
  endm
GTK_IS_DROP_TARGET macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_DROP_TARGET))>
  endm
GTK_IS_DROP_TARGET_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_DROP_TARGET))>
  endm
GTK_DROP_TARGET_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_DROP_TARGET, GtkDropTargetClass))>
  endm

;GtkDropTargetClass      typedef _GtkDropTargetClass

gtk_drop_target_get_type proto
gtk_drop_target_new proto :GType, :GdkDragAction
gtk_drop_target_set_gtypes proto :ptr, :ptr, :gsize
gtk_drop_target_get_gtypes proto :ptr, :ptr
gtk_drop_target_get_formats proto :ptr
gtk_drop_target_set_actions proto :ptr, :GdkDragAction
gtk_drop_target_get_actions proto :ptr
gtk_drop_target_set_preload proto :ptr, :gboolean
gtk_drop_target_get_preload proto :ptr
gtk_drop_target_get_drop proto :ptr
gtk_drop_target_get_current_drop proto :ptr
gtk_drop_target_get_value proto :ptr
gtk_drop_target_reject proto :ptr

endif
