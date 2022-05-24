ifndef __GTKBOXLAYOUT_INC
define __GTKBOXLAYOUT_INC

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkenums.inc
include gtk/gtklayoutmanager.inc

define GTK_TYPE_BOX_LAYOUT <gtk_box_layout_get_type ()>

gtk_box_layout_new proto :GtkOrientation

gtk_box_layout_set_homogeneous proto :ptr, :gboolean
gtk_box_layout_get_homogeneous proto :ptr
gtk_box_layout_set_spacing proto :ptr, :guint
gtk_box_layout_get_spacing proto :ptr
gtk_box_layout_set_baseline_position proto :ptr, :GtkBaselinePosition
gtk_box_layout_get_baseline_position proto :ptr

endif
