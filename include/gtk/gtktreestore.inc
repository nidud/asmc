ifndef __GTK_TREE_STORE_H__
__GTK_TREE_STORE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc
include stdarg.inc

G_BEGIN_DECLS

GTK_TYPE_TREE_STORE equ <gtk_tree_store_get_type>
GTK_TREE_STORE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TREE_STORE, GtkTreeStore))>
	endm
GTK_TREE_STORE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_TREE_STORE, GtkTreeStoreClass))>
	endm
GTK_IS_TREE_STORE macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TREE_STORE))>
	endm
GTK_IS_TREE_STORE_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_TREE_STORE))>
	endm
GTK_TREE_STORE_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_TREE_STORE, GtkTreeStoreClass))>
	endm

GtkTreeStore		STRUC
parent			GObject <>
priv			ptr_t ?
GtkTreeStore		ENDS

GtkTreeStoreClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkTreeStoreClass	ENDS

;GType
gtk_tree_store_get_type proto __cdecl
;GtkTreeStore
gtk_tree_store_new proto _CDecl \
	     n_columns: gint,
		      : vararg

;GtkTreeStore
gtk_tree_store_newv proto __cdecl \
	     n_columns: gint,
		 types: ptr GType

;void
gtk_tree_store_set_column_types proto __cdecl \
	    tree_store: ptr GtkTreeStore,
	     n_columns: gint,
		 types: ptr GType



;void
gtk_tree_store_set_value proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		column: gint,
		 value: ptr GValue

;void
gtk_tree_store_set proto _CDecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		      : vararg

;void
gtk_tree_store_set_valuesv proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
	       columns: ptr gint,
		values: ptr GValue,
	      n_values: gint

;void
gtk_tree_store_set_valist proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
	      var_args: va_list

;gboolean
gtk_tree_store_remove proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter

;void
gtk_tree_store_insert proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter,
	      position: gint

;void
gtk_tree_store_insert_before proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter,
	       sibling: ptr GtkTreeIter

;void
gtk_tree_store_insert_after proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter,
	       sibling: ptr GtkTreeIter

;void
gtk_tree_store_insert_with_values proto _CDecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter,
	      position: gint,
		      : vararg

;void
gtk_tree_store_insert_with_valuesv proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter,
	      position: gint,
	       columns: ptr gint,
		values: ptr GValue,
	      n_values: gint

;void
gtk_tree_store_prepend proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter

;void
gtk_tree_store_append proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
		parent: ptr GtkTreeIter

;gboolean
gtk_tree_store_is_ancestor proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
	    descendant: ptr GtkTreeIter

;gint
gtk_tree_store_iter_depth proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter

;void
gtk_tree_store_clear proto __cdecl \
	    tree_store: ptr GtkTreeStore

;gboolean
gtk_tree_store_iter_is_valid proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter

;void
gtk_tree_store_reorder proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		parent: ptr GtkTreeIter,
	     new_order: ptr gint

;void
gtk_tree_store_swap proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		     a: ptr GtkTreeIter,
		     b: ptr GtkTreeIter

;void
gtk_tree_store_move_before proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
	      position: ptr GtkTreeIter

;void
gtk_tree_store_move_after proto __cdecl \
	    tree_store: ptr GtkTreeStore,
		  iter: ptr GtkTreeIter,
	      position: ptr GtkTreeIter

G_END_DECLS

endif
