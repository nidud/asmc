ifndef __GTK_BUILDER_LIST_ITEM_FACTORY_H__
define __GTK_BUILDER_LIST_ITEM_FACTORY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtklistitemfactory.inc

define GTK_TYPE_BUILDER_LIST_ITEM_FACTORY <gtk_builder_list_item_factory_get_type ()>
GTK_BUILDER_LIST_ITEM_FACTORY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_BUILDER_LIST_ITEM_FACTORY, GtkBuilderListItemFactory))>
  endm
GTK_BUILDER_LIST_ITEM_FACTORY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_TYPE_BUILDER_LIST_ITEM_FACTORY, GtkBuilderListItemFactoryClass))>
  endm
GTK_IS_BUILDER_LIST_ITEM_FACTORY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_BUILDER_LIST_ITEM_FACTORY))>
  endm
GTK_IS_BUILDER_LIST_ITEM_FACTORY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_BUILDER_LIST_ITEM_FACTORY))>
  endm
GTK_BUILDER_LIST_ITEM_FACTORY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_BUILDER_LIST_ITEM_FACTORY, GtkBuilderListItemFactoryClass))>
  endm

;GtkBuilderListItemFactory typedef _GtkBuilderListItemFactory
;GtkBuilderListItemFactoryClass typedef _GtkBuilderListItemFactoryClass

gtk_builder_list_item_factory_get_type proto

gtk_builder_list_item_factory_new_from_bytes proto :ptr, :ptr
gtk_builder_list_item_factory_new_from_resource proto :ptr, :ptr

gtk_builder_list_item_factory_get_bytes proto :ptr
gtk_builder_list_item_factory_get_resource proto :ptr
gtk_builder_list_item_factory_get_scope proto :ptr

endif
