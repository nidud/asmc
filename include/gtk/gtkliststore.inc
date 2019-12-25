ifndef __GTK_LIST_STORE_H__
__GTK_LIST_STORE_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktreemodel.inc
include gtk/gtktreesortable.inc

G_BEGIN_DECLS

GTK_TYPE_LIST_STORE equ <gtk_list_store_get_type>
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

GtkListStore		STRUC
parent			GObject <>
priv			ptr_t ?
GtkListStore		ENDS

GtkListStoreClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkListStoreClass	ENDS

;GType
gtk_list_store_get_type proto __cdecl
;GtkListStore
gtk_list_store_new proto _CDecl \
	     n_columns: gint,
		      : vararg

;GtkListStore
gtk_list_store_newv proto __cdecl \
	     n_columns: gint,
		 types: ptr GType

;void
gtk_list_store_set_column_types proto __cdecl \
	    list_store: ptr GtkListStore,
	     n_columns: gint,
		 types: ptr GType

;void
gtk_list_store_set_value proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
		column: gint,
		 value: ptr GValue

;void
gtk_list_store_set proto _CDecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
		      : vararg

;void
gtk_list_store_set_valuesv proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	       columns: ptr gint,
		values: ptr GValue,
	      n_values: gint

;void
gtk_list_store_set_valist proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	      var_args: va_list

;gboolean
gtk_list_store_remove proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter

;void
gtk_list_store_insert proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	      position: gint

;void
gtk_list_store_insert_before proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	       sibling: ptr GtkTreeIter

;void
gtk_list_store_insert_after proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	       sibling: ptr GtkTreeIter

;void
gtk_list_store_insert_with_values proto _CDecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	      position: gint,
		      : vararg

;void
gtk_list_store_insert_with_valuesv proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	      position: gint,
	       columns: ptr gint,
		values: ptr GValue,
	      n_values: gint

;void
gtk_list_store_prepend proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter

;void
gtk_list_store_append proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter

;void
gtk_list_store_clear proto __cdecl \
	    list_store: ptr GtkListStore

;gboolean
gtk_list_store_iter_is_valid proto __cdecl \
	    list_store: ptr GtkListStore,
		  iter: ptr GtkTreeIter

;void
gtk_list_store_reorder proto __cdecl \
		 store: ptr GtkListStore,
	     new_order: ptr gint

;void
gtk_list_store_swap proto __cdecl \
		 store: ptr GtkListStore,
		     a: ptr GtkTreeIter,
		     b: ptr GtkTreeIter

;void
gtk_list_store_move_after proto __cdecl \
		 store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	      position: ptr GtkTreeIter

;void
gtk_list_store_move_before proto __cdecl \
		 store: ptr GtkListStore,
		  iter: ptr GtkTreeIter,
	      position: ptr GtkTreeIter

G_END_DECLS

endif
