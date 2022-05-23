ifndef __GTK_LIST_ITEM_H__
define __GTK_LIST_ITEM_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_LIST_ITEM <gtk_list_item_get_type>
GTK_LIST_ITEM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LIST_ITEM, GtkListItem))>
  endm
GTK_LIST_ITEM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_LIST_ITEM, GtkListItemClass))>
  endm
GTK_IS_LIST_ITEM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LIST_ITEM))>
  endm
GTK_IS_LIST_ITEM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_LIST_ITEM))>
  endm
GTK_LIST_ITEM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_LIST_ITEM, GtkListItemClass))>
  endm

;GtkListItem             typedef _GtkListItem
;GtkListItemClass        typedef _GtkListItemClass

gtk_list_item_get_type proto

gtk_list_item_get_item proto :ptr
gtk_list_item_get_position proto :ptr
gtk_list_item_get_selected proto :ptr
gtk_list_item_get_selectable proto :ptr
gtk_list_item_set_selectable proto :ptr, :gboolean
gtk_list_item_get_activatable proto :ptr
gtk_list_item_set_activatable proto :ptr, :gboolean

gtk_list_item_set_child proto :ptr, :ptr
gtk_list_item_get_child proto :ptr

endif
