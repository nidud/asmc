ifndef __GTKCENTERLAYOUT_INC
define __GTKCENTERLAYOUT_INC

include gtk/gtklayoutmanager.inc

define GTK_TYPE_CENTER_LAYOUT <gtk_center_layout_get_type ()>

gtk_center_layout_new proto
gtk_center_layout_set_orientation proto :ptr, :GtkOrientation
gtk_center_layout_get_orientation proto :ptr
gtk_center_layout_set_baseline_position proto :ptr, :GtkBaselinePosition
gtk_center_layout_get_baseline_position proto :ptr
gtk_center_layout_set_start_widget proto :ptr, :ptr
gtk_center_layout_get_start_widget proto :ptr
gtk_center_layout_set_center_widget proto :ptr, :ptr
gtk_center_layout_get_center_widget proto :ptr
gtk_center_layout_set_end_widget proto :ptr, :ptr
gtk_center_layout_get_end_widget proto :ptr

endif
