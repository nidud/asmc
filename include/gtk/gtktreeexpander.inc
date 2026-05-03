ifndef __GTK_TREE_EXPANDER_H__
define __GTK_TREE_EXPANDER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktreelistmodel.inc
include gtk/gtkwidget.inc

define GTK_TYPE_TREE_EXPANDER <gtk_tree_expander_get_type ()>

gtk_tree_expander_new proto
gtk_tree_expander_get_child proto :ptr
gtk_tree_expander_set_child proto :ptr, :ptr
gtk_tree_expander_get_item proto :ptr
gtk_tree_expander_get_list_row proto :ptr
gtk_tree_expander_set_list_row proto :ptr, :ptr
gtk_tree_expander_get_indent_for_icon proto :ptr
gtk_tree_expander_set_indent_for_icon proto :ptr, :gboolean

endif
