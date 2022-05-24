ifndef __GTK_SIGNAL_LIST_ITEM_FACTORY_H__
define __GTK_SIGNAL_LIST_ITEM_FACTORY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtklistitemfactory.inc

define GTK_TYPE_SIGNAL_LIST_ITEM_FACTORY <gtk_signal_list_item_factory_get_type ()>
GTK_SIGNAL_LIST_ITEM_FACTORY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_SIGNAL_LIST_ITEM_FACTORY, GtkSignalListItemFactory))>
  endm
GTK_SIGNAL_LIST_ITEM_FACTORY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_SIGNAL_LIST_ITEM_FACTORY, GtkSignalListItemFactoryClass))>
  endm
GTK_IS_SIGNAL_LIST_ITEM_FACTORY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_SIGNAL_LIST_ITEM_FACTORY))>
  endm
GTK_IS_SIGNAL_LIST_ITEM_FACTORY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_SIGNAL_LIST_ITEM_FACTORY))>
  endm
GTK_SIGNAL_LIST_ITEM_FACTORY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_SIGNAL_LIST_ITEM_FACTORY, GtkSignalListItemFactoryClass))>
  endm

;GtkSignalListItemFactory typedef _GtkSignalListItemFactory
;GtkSignalListItemFactoryClass typedef _GtkSignalListItemFactoryClass

gtk_signal_list_item_factory_get_type proto
gtk_signal_list_item_factory_new proto

endif
