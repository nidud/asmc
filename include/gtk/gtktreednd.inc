ifndef __GTK_TREE_DND_H__
__GTK_TREE_DND_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreemodel.inc
include gtk/gtkdnd.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_DRAG_SOURCE equ <gtk_tree_drag_source_get_type>
GTK_TREE_DRAG_SOURCE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_DRAG_SOURCE, GtkTreeDragSource))>
	endm
GTK_IS_TREE_DRAG_SOURCE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_DRAG_SOURCE))>
	endm
GTK_TREE_DRAG_SOURCE_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_DRAG_SOURCE, GtkTreeDragSourceIface))>
	endm

GtkTreeDragSourceIface	STRUC
g_iface			GTypeInterface <>
row_draggable		proc :ptr GtkTreeDragSource, :ptr GtkTreePath
drag_data_get		proc :ptr GtkTreeDragSource, :ptr GtkTreePath, :ptr GtkSelectionData
drag_data_delete	proc :ptr GtkTreeDragSource, :ptr GtkTreePath
GtkTreeDragSourceIface	ENDS

;GType
gtk_tree_drag_source_get_type proto __cdecl

;gboolean
gtk_tree_drag_source_row_draggable proto __cdecl \
	   drag_source: ptr GtkTreeDragSource,
		  path: ptr GtkTreePath


;gboolean
gtk_tree_drag_source_drag_data_delete proto __cdecl \
	   drag_source: ptr GtkTreeDragSource,
		  path: ptr GtkTreePath


;gboolean
gtk_tree_drag_source_drag_data_get proto __cdecl \
	   drag_source: ptr GtkTreeDragSource,
		  path: ptr GtkTreePath,
	selection_data: ptr GtkSelectionData


GTK_TYPE_TREE_DRAG_DEST equ (gtk_tree_drag_dest_get_type ())
GTK_TREE_DRAG_DEST macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_DRAG_DEST, GtkTreeDragDest))>
	endm
GTK_IS_TREE_DRAG_DEST macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_DRAG_DEST))>
	endm
GTK_TREE_DRAG_DEST_GET_IFACE macro obj
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_TREE_DRAG_DEST, GtkTreeDragDestIface))>
	endm

GtkTreeDragDestIface	STRUC
g_iface			GTypeInterface <>
drag_data_received	proc :ptr GtkTreeDragDest, :ptr GtkTreePath, :ptr GtkSelectionData
row_drop_possible	proc :ptr GtkTreeDragDest, :ptr GtkTreePath, :ptr GtkSelectionData
GtkTreeDragDestIface	ENDS

;GType
gtk_tree_drag_dest_get_type proto __cdecl

;gboolean
gtk_tree_drag_dest_drag_data_received proto __cdecl \
	     drag_dest: ptr GtkTreeDragDest,
		  dest: ptr GtkTreePath,
	selection_data: ptr GtkSelectionData



;gboolean
gtk_tree_drag_dest_row_drop_possible proto __cdecl \
	     drag_dest: ptr GtkTreeDragDest,
	     dest_path: ptr GtkTreePath,
	selection_data: ptr GtkSelectionData



;gboolean
gtk_tree_set_row_drag_data proto __cdecl \
	selection_data: ptr GtkSelectionData,
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath

;gboolean
gtk_tree_get_row_drag_data proto __cdecl \
	selection_data: ptr GtkSelectionData,
	    tree_model: ptr GtkTreeModel,
		  path: ptr GtkTreePath

G_END_DECLS

endif
