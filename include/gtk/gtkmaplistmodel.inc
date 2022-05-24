ifndef __GTK_MAP_LIST_MODEL_H__
define __GTK_MAP_LIST_MODEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc

define GTK_TYPE_MAP_LIST_MODEL <gtk_map_list_model_get_type ()>

CALLBACK(GtkMapListModelMapFunc, :gpointer, :gpointer)

gtk_map_list_model_new proto :ptr, :GtkMapListModelMapFunc, :gpointer, :GDestroyNotify

gtk_map_list_model_set_map_func proto :ptr, :GtkMapListModelMapFunc, :gpointer, :GDestroyNotify
gtk_map_list_model_set_model proto :ptr, :ptr
gtk_map_list_model_get_model proto :ptr
gtk_map_list_model_has_map proto :ptr

endif
