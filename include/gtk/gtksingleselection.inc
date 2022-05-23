ifndef __GTK_SINGLE_SELECTION_H__
define __GTK_SINGLE_SELECTION_H__

include gtk/gtktypes.inc

define GTK_TYPE_SINGLE_SELECTION <gtk_single_selection_get_type>

gtk_single_selection_new proto :ptr
gtk_single_selection_get_model proto :ptr
gtk_single_selection_set_model proto :ptr, :ptr
gtk_single_selection_get_selected proto :ptr
gtk_single_selection_set_selected proto :ptr, :guint
gtk_single_selection_get_selected_item proto :ptr
gtk_single_selection_get_autoselect proto :ptr
gtk_single_selection_set_autoselect proto :ptr, :gboolean
gtk_single_selection_get_can_unselect proto :ptr
gtk_single_selection_set_can_unselect proto :ptr, :gboolean

endif
