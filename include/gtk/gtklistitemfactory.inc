ifndef __GTK_LIST_ITEM_FACTORY_H__
define __GTK_LIST_ITEM_FACTORY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

;GtkListItemFactoryClass typedef _GtkListItemFactoryClass

include gdk/gdk.inc
include gtk/gtktypes.inc

define GTK_TYPE_LIST_ITEM_FACTORY <gtk_list_item_factory_get_type>
GTK_LIST_ITEM_FACTORY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LIST_ITEM_FACTORY, GtkListItemFactory))>
  endm
GTK_LIST_ITEM_FACTORY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_LIST_ITEM_FACTORY, GtkListItemFactoryClass))>
  endm
GTK_IS_LIST_ITEM_FACTORY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LIST_ITEM_FACTORY))>
  endm
GTK_IS_LIST_ITEM_FACTORY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_LIST_ITEM_FACTORY))>
  endm
GTK_LIST_ITEM_FACTORY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_LIST_ITEM_FACTORY, GtkListItemFactoryClass))>
  endm

gtk_list_item_factory_get_type proto

endif
