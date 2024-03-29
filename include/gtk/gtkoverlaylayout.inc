ifndef __GTK_OVERLAY_LAYOUT_H__
define __GTK_OVERLAY_LAYOUT_H__

include gtk/gtklayoutmanager.inc

define GTK_TYPE_OVERLAY_LAYOUT <gtk_overlay_layout_get_type ()>
define GTK_TYPE_OVERLAY_LAYOUT_CHILD <gtk_overlay_layout_child_get_type ()>

gtk_overlay_layout_new proto
gtk_overlay_layout_child_set_measure proto :ptr, :gboolean
gtk_overlay_layout_child_get_measure proto :ptr
gtk_overlay_layout_child_set_clip_overlay proto :ptr, :gboolean
gtk_overlay_layout_child_get_clip_overlay proto :ptr

endif
