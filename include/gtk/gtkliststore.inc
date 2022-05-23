ifndef __GTK_LIST_STORE_H__
define __GTK_LIST_STORE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc

define GTK_TYPE_LIST_STORE <gtk_list_store_get_type>
GTK_LIST_STORE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LIST_STORE, GtkListStore))>
  endm
GTK_LIST_STORE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_LIST_STORE, GtkListStoreClass))>
  endm
GTK_IS_LIST_STORE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LIST_STORE))>
  endm
GTK_IS_LIST_STORE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_LIST_STORE))>
  endm
GTK_LIST_STORE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_LIST_STORE, GtkListStoreClass))>
  endm

;GtkListStorePrivate	 typedef _GtkListStorePrivate

_GtkListStore		struct
parent			GObject <>
priv			ptr GtkListStorePrivate ?
_GtkListStore		ends
GtkListStore		typedef _GtkListStore

_GtkListStoreClass	struct
parent_class		GObjectClass <>
padding			gpointer 8 dup(?)
_GtkListStoreClass	ends
GtkListStoreClass	typedef _GtkListStoreClass


gtk_list_store_get_type proto
gtk_list_store_new proto :sdword, :vararg
gtk_list_store_newv proto :sdword, :ptr
gtk_list_store_set_column_types proto :ptr, :sdword, :ptr
gtk_list_store_set_value proto :ptr, :ptr, :sdword, :ptr
gtk_list_store_set proto :ptr, :ptr, :vararg
gtk_list_store_set_valuesv proto :ptr, :ptr, :ptr, :ptr, :sdword
gtk_list_store_set_valist proto :ptr, :ptr, :va_list
gtk_list_store_remove proto :ptr, :ptr
gtk_list_store_insert proto :ptr, :ptr, :sdword
gtk_list_store_insert_before proto :ptr, :ptr, :ptr
gtk_list_store_insert_after proto :ptr, :ptr, :ptr
gtk_list_store_insert_with_values proto :ptr, :ptr, :sdword, :vararg
gtk_list_store_insert_with_valuesv proto :ptr, :ptr, :sdword, :ptr, :ptr, :sdword
gtk_list_store_prepend proto :ptr, :ptr
gtk_list_store_append proto :ptr, :ptr
gtk_list_store_clear proto :ptr
gtk_list_store_iter_is_valid proto :ptr, :ptr
gtk_list_store_reorder proto :ptr, :ptr
gtk_list_store_swap proto :ptr, :ptr, :ptr
gtk_list_store_move_after proto :ptr, :ptr, :ptr
gtk_list_store_move_before proto :ptr, :ptr, :ptr

endif
