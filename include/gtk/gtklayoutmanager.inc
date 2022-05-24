ifndef __GTKLAYOUTMANAGER_INC
define __GTKLAYOUTMANAGER_INC

;include gsk/gsk.inc
include gtk/gtktypes.inc
include gtk/gtkwidget.inc
include gtk/gtklayoutchild.inc

define GTK_TYPE_LAYOUT_MANAGER <gtk_layout_manager_get_type ()>

_GtkLayoutManagerClass  struct
parent_class            GObjectClass <>
get_request_mode        proc :ptr, :ptr
measure                 proc :ptr, :ptr, :GtkOrientation, :sdword, :ptr, :ptr, :ptr, :ptr
allocate                proc :ptr, :ptr, :sdword, :sdword, :sdword
layout_child_type       GType ?
create_layout_child     proc :ptr, :ptr, :ptr
root                    proc :ptr
unroot                  proc :ptr
_padding                gpointer 16 dup(?)
_GtkLayoutManagerClass  ends
GtkLayoutManagerClass   typedef _GtkLayoutManagerClass

gtk_layout_manager_measure proto :ptr, :ptr, :GtkOrientation, :sdword, :ptr, :ptr, :ptr, :ptr
gtk_layout_manager_allocate proto :ptr, :ptr, :sdword, :sdword, :sdword
gtk_layout_manager_get_request_mode proto :ptr
gtk_layout_manager_get_widget proto :ptr
gtk_layout_manager_layout_changed proto :ptr
gtk_layout_manager_get_layout_child proto :ptr, :ptr

endif
