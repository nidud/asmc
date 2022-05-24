ifndef __GTKLAYOUTCHILD_INC
define __GTKLAYOUTCHILD_INC

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_LAYOUT_CHILD <gtk_layout_child_get_type ()>

_GtkLayoutChildClass    struct
parent_class            GObjectClass <>
_GtkLayoutChildClass    ends
GtkLayoutChildClass     typedef _GtkLayoutChildClass

gtk_layout_child_get_layout_manager proto :ptr
gtk_layout_child_get_child_widget proto :ptr

endif