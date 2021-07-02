ifndef __GTK_TREE_SELECTION_H__
__GTK_TREE_SELECTION_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreeview.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_SELECTION equ <gtk_tree_selection_get_type>
GTK_TREE_SELECTION macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_SELECTION, GtkTreeSelection))>
	endm
GTK_TREE_SELECTION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TREE_SELECTION, GtkTreeSelectionClass))>
	endm
GTK_IS_TREE_SELECTION macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_SELECTION))>
	endm
GTK_IS_TREE_SELECTION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TREE_SELECTION))>
	endm
GTK_TREE_SELECTION_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_SELECTION, GtkTreeSelectionClass))>
	endm

CALLBACKC(GtkTreeSelectionFunc, :ptr GtkTreeSelection, :ptr GtkTreeModel, :ptr GtkTreePath, :gboolean, :gpointer)
CALLBACKC(GtkTreeSelectionForeachFunc, :ptr GtkTreeModel, :ptr GtkTreePath, :ptr GtkTreeIter, :gpointer)

GtkTreeSelection	STRUC
parent			GObject <>
priv			ptr_t ?
GtkTreeSelection	ENDS

GtkTreeSelectionClass	STRUC
parent_class		GObjectClass <>
changed			proc :ptr GtkTreeSelection
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTreeSelectionClass	ENDS


;GType
gtk_tree_selection_get_type proto __cdecl

;void
gtk_tree_selection_set_mode proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  type: GtkSelectionMode

;GtkSelectionMode
gtk_tree_selection_get_mode proto __cdecl \
	     selection: ptr GtkTreeSelection

;void
gtk_tree_selection_set_select_function proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  func: GtkTreeSelectionFunc,
		  data: gpointer,
	       destroy: GDestroyNotify

;gpointer
gtk_tree_selection_get_user_data proto __cdecl \
	     selection: ptr GtkTreeSelection

;GtkTreeView*
gtk_tree_selection_get_tree_view proto __cdecl \
	     selection: ptr GtkTreeSelection


;GtkTreeSelectionFunc
gtk_tree_selection_get_select_function proto __cdecl \
	     selection: ptr GtkTreeSelection


;gboolean
gtk_tree_selection_get_selected proto __cdecl \
	     selection: ptr GtkTreeSelection,
		 model: ptr GtkTreeModel,
		  iter: ptr GtkTreeIter

;GList
gtk_tree_selection_get_selected_rows proto __cdecl \
	     selection: ptr GtkTreeSelection,
		 model: ptr GtkTreeModel

;gint
gtk_tree_selection_count_selected_rows proto __cdecl \
	     selection: ptr GtkTreeSelection

;void
gtk_tree_selection_selected_foreach proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  func: GtkTreeSelectionForeachFunc,
		  data: gpointer

;void
gtk_tree_selection_select_path proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  path: ptr GtkTreePath

;void
gtk_tree_selection_unselect_path proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  path: ptr GtkTreePath

;void
gtk_tree_selection_select_iter proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  iter: ptr GtkTreeIter

;void
gtk_tree_selection_unselect_iter proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  iter: ptr GtkTreeIter

;gboolean
gtk_tree_selection_path_is_selected proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  path: ptr GtkTreePath

;gboolean
gtk_tree_selection_iter_is_selected proto __cdecl \
	     selection: ptr GtkTreeSelection,
		  iter: ptr GtkTreeIter

;void
gtk_tree_selection_select_all proto __cdecl \
	     selection: ptr GtkTreeSelection

;void
gtk_tree_selection_unselect_all proto __cdecl \
	     selection: ptr GtkTreeSelection

;void
gtk_tree_selection_select_range proto __cdecl \
	     selection: ptr GtkTreeSelection,
	    start_path: ptr GtkTreePath,
	      end_path: ptr GtkTreePath

;void
gtk_tree_selection_unselect_range proto __cdecl \
	     selection: ptr GtkTreeSelection,
	    start_path: ptr GtkTreePath,
	      end_path: ptr GtkTreePath

G_END_DECLS

endif
