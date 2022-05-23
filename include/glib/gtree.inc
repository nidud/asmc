ifndef __G_TREE_H__
define __G_TREE_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gnode.inc

undef G_TREE_DEBUG

;GTree                   typedef _GTree
;GTreeNode               typedef _GTreeNode

CALLBACK(GTraverseFunc, :gpointer, :gpointer, :gpointer)
CALLBACK(GTraverseNodeFunc, :ptr, :gpointer)

g_tree_new proto :GCompareFunc
g_tree_new_with_data proto :GCompareDataFunc, :gpointer
g_tree_new_full proto :GCompareDataFunc, :gpointer, :GDestroyNotify, :GDestroyNotify
g_tree_node_first proto :ptr
g_tree_node_last proto :ptr
g_tree_node_previous proto :ptr
g_tree_node_next proto :ptr
g_tree_ref proto :ptr
g_tree_unref proto :ptr
g_tree_destroy proto :ptr
g_tree_insert_node proto :ptr, :gpointer, :gpointer
g_tree_insert proto :ptr, :gpointer, :gpointer
g_tree_replace_node proto :ptr, :gpointer, :gpointer
g_tree_replace proto :ptr, :gpointer, :gpointer
g_tree_remove proto :ptr, :gconstpointer

g_tree_remove_all proto :ptr

g_tree_steal proto :ptr, :gconstpointer
g_tree_node_key proto :ptr
g_tree_node_value proto :ptr
g_tree_lookup_node proto :ptr, :gconstpointer
g_tree_lookup proto :ptr, :gconstpointer
g_tree_lookup_extended proto :ptr, :gconstpointer, :ptr, :ptr
g_tree_foreach proto :ptr, :GTraverseFunc, :gpointer
g_tree_foreach_node proto :ptr, :GTraverseNodeFunc, :gpointer

g_tree_traverse proto :ptr, :GTraverseFunc, :GTraverseType, :gpointer

g_tree_search_node proto :ptr, :GCompareFunc, :gconstpointer
g_tree_search proto :ptr, :GCompareFunc, :gconstpointer
g_tree_lower_bound proto :ptr, :gconstpointer
g_tree_upper_bound proto :ptr, :gconstpointer
g_tree_height proto :ptr
g_tree_nnodes proto :ptr

ifdef G_TREE_DEBUG

ifndef __GTK_DOC_IGNORE__
g_tree_dump proto :ptr
endif
endif

endif
