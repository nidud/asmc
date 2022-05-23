ifndef __GTK_TREE_STORE_H__
define __GTK_TREE_STORE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc
include stdarg.inc

define GTK_TYPE_TREE_STORE <gtk_tree_store_get_type>
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

;GtkTreeStorePrivate	 typedef _GtkTreeStorePrivate

_GtkTreeStore		struct
parent			GObject <>
priv			ptr GtkTreeStorePrivate ?
_GtkTreeStore		ends
GtkTreeStore		typedef _GtkTreeStore

_GtkTreeStoreClass	struct
parent_class		GObjectClass <>
padding			gpointer 8 dup(?)
_GtkTreeStoreClass	ends
GtkTreeStoreClass	typedef _GtkTreeStoreClass

gtk_tree_store_get_type proto
gtk_tree_store_new proto :sdword, :vararg
gtk_tree_store_newv proto :sdword, :ptr
gtk_tree_store_set_column_types proto :ptr, :sdword, :ptr
gtk_tree_store_set_value proto :ptr, :ptr, :sdword, :ptr
gtk_tree_store_set proto :ptr, :ptr, :vararg
gtk_tree_store_set_valuesv proto :ptr, :ptr, :ptr, :ptr, :sdword
gtk_tree_store_set_valist proto :ptr, :ptr, :va_list
gtk_tree_store_remove proto :ptr, :ptr
gtk_tree_store_insert proto :ptr, :ptr, :ptr, :sdword
gtk_tree_store_insert_before proto :ptr, :ptr, :ptr, :ptr
gtk_tree_store_insert_after proto :ptr, :ptr, :ptr, :ptr
gtk_tree_store_insert_with_values proto :ptr, :ptr, :ptr, :sdword, :vararg
gtk_tree_store_insert_with_valuesv proto :ptr, :ptr, :ptr, :sdword, :ptr, :ptr, :sdword
gtk_tree_store_prepend proto :ptr, :ptr, :ptr
gtk_tree_store_append proto :ptr, :ptr, :ptr
gtk_tree_store_is_ancestor proto :ptr, :ptr, :ptr
gtk_tree_store_iter_depth proto :ptr, :ptr
gtk_tree_store_clear proto :ptr
gtk_tree_store_iter_is_valid proto :ptr, :ptr
gtk_tree_store_reorder proto :ptr, :ptr, :ptr
gtk_tree_store_swap proto :ptr, :ptr, :ptr
gtk_tree_store_move_before proto :ptr, :ptr, :ptr
gtk_tree_store_move_after proto :ptr, :ptr, :ptr

endif
