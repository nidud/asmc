ifndef __G_NODE_H__
define __G_NODE_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmem.inc

.enum GTraverseFlags {
  G_TRAVERSE_LEAVES	= 1 shl 0,
  G_TRAVERSE_NON_LEAVES = 1 shl 1,
  G_TRAVERSE_ALL	= G_TRAVERSE_LEAVES or G_TRAVERSE_NON_LEAVES,
  G_TRAVERSE_MASK	= 0x03,
  G_TRAVERSE_LEAFS	= G_TRAVERSE_LEAVES,
  G_TRAVERSE_NON_LEAFS	= G_TRAVERSE_NON_LEAVES
}

.enum GTraverseType {
  G_IN_ORDER,
  G_PRE_ORDER,
  G_POST_ORDER,
  G_LEVEL_ORDER
}

CALLBACKC(GNodeTraverseFunc, :ptr, :gpointer)
CALLBACKC(GNodeForeachFunc, :ptr, :gpointer)
ifndef GCopyFunc
CALLBACKC(GCopyFunc, :gconstpointer, :gpointer)
endif

GNode			STRUC
data			gpointer ?
next			ptr_t ?
prev			ptr_t ?
parent			ptr_t ?
children		ptr_t ?
GNode			ENDS

G_NODE_IS_LEAF macro node
	exitm<(node.children == NULL)>
	endm

g_node_new proto __cdecl :ptr
g_node_destroy proto __cdecl :ptr
g_node_unlink proto __cdecl :ptr
g_node_copy_deep proto __cdecl :ptr, :GCopyFunc, :ptr
g_node_copy proto __cdecl :ptr
g_node_insert proto __cdecl :ptr, :gint, :ptr
g_node_insert_before proto __cdecl :ptr, :ptr, :ptr
g_node_insert_after proto __cdecl :ptr, :ptr, :ptr
g_node_prepend proto __cdecl :ptr, :ptr
g_node_n_nodes proto __cdecl :ptr, :GTraverseFlags
g_node_get_root proto __cdecl :ptr
g_node_is_ancestor proto __cdecl :ptr, :ptr
g_node_depth proto __cdecl :ptr
g_node_find proto __cdecl :ptr, :GTraverseType, :GTraverseFlags, :gpointer

g_node_traverse proto __cdecl :ptr,:GTraverseType, :GTraverseFlags, :gint, :GNodeTraverseFunc, :ptr
g_node_max_height proto __cdecl :ptr
g_node_children_foreach proto __cdecl :ptr, :GTraverseFlags, :GNodeForeachFunc, :ptr
g_node_reverse_children proto __cdecl :ptr
g_node_n_children proto __cdecl :ptr
g_node_nth_child proto __cdecl :ptr, :guint
g_node_last_child proto __cdecl :ptr
g_node_find_child proto __cdecl :ptr, :GTraverseFlags, :ptr
g_node_child_position proto __cdecl :ptr, :ptr
g_node_child_index proto __cdecl :ptr, :ptr
g_node_first_sibling proto __cdecl :ptr
g_node_last_sibling proto __cdecl :ptr

endif
