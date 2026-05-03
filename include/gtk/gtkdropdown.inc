ifndef __GTK_DROP_DOWN_H__
define __GTK_DROP_DOWN_H__

include gtk/gtkwidget.inc
include gtk/gtkexpression.inc

define GTK_TYPE_DROP_DOWN <gtk_drop_down_get_type ()>

gtk_drop_down_new proto :ptr, :ptr
gtk_drop_down_new_from_strings proto :ptr
gtk_drop_down_set_model proto :ptr, :ptr
gtk_drop_down_get_model proto :ptr
gtk_drop_down_set_selected proto :ptr, :guint
gtk_drop_down_get_selected proto :ptr
gtk_drop_down_get_selected_item proto :ptr
gtk_drop_down_set_factory proto :ptr, :ptr
gtk_drop_down_get_factory proto :ptr
gtk_drop_down_set_list_factory proto :ptr, :ptr
gtk_drop_down_get_list_factory proto :ptr
gtk_drop_down_set_expression proto :ptr, :ptr
gtk_drop_down_get_expression proto :ptr
gtk_drop_down_set_enable_search proto :ptr, :gboolean
gtk_drop_down_get_enable_search proto :ptr
gtk_drop_down_set_show_arrow proto :ptr, :gboolean
gtk_drop_down_get_show_arrow proto :ptr

endif
