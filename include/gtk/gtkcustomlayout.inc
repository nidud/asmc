ifndef __GTK_CUSTOM_LAYOUT_H__
define __GTK_CUSTOM_LAYOUT_H__

include gtk/gtklayoutmanager.inc

define GTK_TYPE_CUSTOM_LAYOUT <gtk_custom_layout_get_type>

CALLBACK(GtkCustomRequestModeFunc, :ptr)
CALLBACK(GtkCustomMeasureFunc, :ptr, :GtkOrientation, :sdword, :ptr, :ptr, :ptr, :ptr)
CALLBACK(GtkCustomAllocateFunc, :ptr, :sdword, :sdword, :sdword)

gtk_custom_layout_new proto :GtkCustomRequestModeFunc, :GtkCustomMeasureFunc, :GtkCustomAllocateFunc

endif
