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

CALLBACKC(GNodeTraverseFunc, :ptr GNode, :gpointer)
CALLBACKC(GNodeForeachFunc, :ptr GNode, :gpointer)
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

G_NODE_IS_ROOT macro node
	exitm<.err>
	endm

G_NODE_IS_LEAF macro node
	exitm<((node).children == NULL)>
	endm

;GNode*
g_node_new proto __cdecl \
		  data: gpointer

;void
g_node_destroy proto __cdecl \
		  root: ptr GNode

;void
g_node_unlink proto __cdecl \
		  node: ptr GNode

;GNode*
g_node_copy_deep proto __cdecl \
		  node: ptr GNode,
	     copy_func: GCopyFunc,
		  data: gpointer

;GNode*
g_node_copy proto __cdecl \
		  node: ptr GNode

;GNode*
g_node_insert proto __cdecl \
		parent: ptr GNode,
	      position: gint,
		  node: ptr GNode

;GNode*
g_node_insert_before proto __cdecl \
		parent: ptr GNode,
	       sibling: ptr GNode,
		  node: ptr GNode

;GNode*
g_node_insert_after proto __cdecl \
		parent: ptr GNode,
	       sibling: ptr GNode,
		  node: ptr GNode

;GNode*
g_node_prepend proto __cdecl \
		parent: ptr GNode,
		  node: ptr GNode

;guint
g_node_n_nodes proto __cdecl \
		  root: ptr GNode,
		 flags: GTraverseFlags

;GNode*
g_node_get_root proto __cdecl \
		  node: ptr GNode

;gboolean
g_node_is_ancestor proto __cdecl \
		  node: ptr GNode,
	    descendant: ptr GNode

;guint
g_node_depth proto __cdecl \
		  node: ptr GNode

;GNode*
g_node_find proto __cdecl \
		  root: ptr GNode,
		 order: GTraverseType,
		 flags: GTraverseFlags,
		  data: gpointer


g_node_append macro parent, node
	exitm<.err>
	endm
g_node_insert_data macro parent, position, data
	exitm<.err>
	endm
g_node_insert_data_after macro parent, sibling, data
	exitm<.err>
	endm
g_node_insert_data_before macro parent, sibling, data
	exitm<.err>
	endm
g_node_prepend_data macro parent, data
	exitm<.err>
	endm
g_node_append_data macro parent, data
	exitm<.err>
	endm

g_node_traverse proto __cdecl \
		  root: ptr GNode,
		 order: GTraverseType,
		 flags: GTraverseFlags,
	     max_depth: gint,
		  func: GNodeTraverseFunc,
		  data: gpointer

;guint
g_node_max_height proto __cdecl \
		  root: ptr GNode

;void
g_node_children_foreach proto __cdecl \
		  node: ptr GNode,
		 flags: GTraverseFlags,
		  func: GNodeForeachFunc,
		  data: gpointer

;void
g_node_reverse_children proto __cdecl \
		  node: ptr GNode

;guint
g_node_n_children proto __cdecl \
		  node: ptr GNode

;GNode*
g_node_nth_child proto __cdecl \
		  node: ptr GNode,
		     n: guint

g_node_last_child proto __cdecl \
		  node: ptr GNode

g_node_find_child proto __cdecl \
		  node: ptr GNode,
		 flags: GTraverseFlags,
		  data: gpointer

;gint
g_node_child_position proto __cdecl \
		  node: ptr GNode,
		 child: ptr GNode

;gint
g_node_child_index proto __cdecl \
		  node: ptr GNode,
		  data: gpointer

;GNode*
g_node_first_sibling proto __cdecl \
		  node: ptr GNode

;GNode*
g_node_last_sibling proto __cdecl \
		  node: ptr GNode

g_node_prev_sibling macro node
	exitm<.err>
	endm

g_node_next_sibling macro node
	exitm<.err>
	endm

g_node_first_child macro node
	exitm<.err>
	endm

endif
