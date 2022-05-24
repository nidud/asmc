ifndef __GTK_FIXED_LAYOUT_H__
define __GTK_FIXED_LAYOUT_H__

include gtk/gtklayoutmanager.inc

define GTK_TYPE_FIXED_LAYOUT <gtk_fixed_layout_get_type ()>
define GTK_TYPE_FIXED_LAYOUT_CHILD <gtk_fixed_layout_child_get_type ()>

gtk_fixed_layout_new proto
gtk_fixed_layout_child_set_transform proto :ptr, :ptr
gtk_fixed_layout_child_get_transform proto :ptr

endif

