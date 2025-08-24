ifndef __GTK_TREE_DND_H__
define __GTK_TREE_DND_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreemodel.inc

define GTK_TYPE_TREE_ROW_DATA <gtk_tree_row_data_get_type ()>
gtk_tree_row_data_get_type proto

define GTK_TYPE_TREE_DRAG_SOURCE <gtk_tree_drag_source_get_type ()>
GTK_TREE_DRAG_SOURCE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_DRAG_SOURCE, GtkTreeDragSource))>
  endm
GTK_IS_TREE_DRAG_SOURCE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_DRAG_SOURCE))>
  endm
GTK_TREE_DRAG_SOURCE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_DRAG_SOURCE, GtkTreeDragSourceIface))>
  endm

GtkTreeDragSourceIface  struct
g_iface                 GTypeInterface <>
row_draggable           proc :ptr, :ptr
drag_data_get           proc :ptr, :ptr
drag_data_delete        proc :ptr, :ptr
GtkTreeDragSourceIface  ends

gtk_tree_drag_source_get_type proto
gtk_tree_drag_source_row_draggable proto :ptr, :ptr
gtk_tree_drag_source_drag_data_delete proto :ptr, :ptr

define GTK_TYPE_TREE_DRAG_DEST <gtk_tree_drag_dest_get_type ()>
GTK_TREE_DRAG_DEST macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_DRAG_DEST, GtkTreeDragDest))>
  endm
GTK_IS_TREE_DRAG_DEST macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_DRAG_DEST))>
  endm
GTK_TREE_DRAG_DEST_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_DRAG_DEST, GtkTreeDragDestIface))>
  endm

GtkTreeDragDestIface    struct
g_iface                 GTypeInterface <>
drag_data_received      proc :ptr, :ptr, :ptr
row_drop_possible       proc :ptr, :ptr, :ptr
GtkTreeDragDestIface    ends

gtk_tree_drag_dest_get_type proto
gtk_tree_drag_dest_drag_data_received proto :ptr, :ptr, :ptr
gtk_tree_drag_dest_row_drop_possible proto :ptr, :ptr, :ptr
gtk_tree_get_row_drag_data proto :ptr, :ptr, :ptr

endif
