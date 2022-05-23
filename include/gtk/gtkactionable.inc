ifndef __GTK_ACTIONABLE_H__
define __GTK_ACTIONABLE_H__

include glib-object.inc
include gdk/gdk.inc

define GTK_TYPE_ACTIONABLE <gtk_actionable_get_type>
GTK_ACTIONABLE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), GTK_TYPE_ACTIONABLE, GtkActionable))>
  endm
GTK_IS_ACTIONABLE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), GTK_TYPE_ACTIONABLE))>
  endm
GTK_ACTIONABLE_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_ACTIONABLE, GtkActionableInterface))>
  endm

;GtkActionable           typedef _GtkActionable

_GtkActionableInterface struct
g_iface                 GTypeInterface <>
get_action_name         proc :ptr
set_action_name         proc :ptr, :ptr
get_action_target_value proc :ptr
set_action_target_value proc :ptr, :ptr
_GtkActionableInterface ends
GtkActionableInterface  typedef _GtkActionableInterface

gtk_actionable_get_type proto

gtk_actionable_get_action_name proto :ptr
gtk_actionable_set_action_name proto :ptr, :ptr

gtk_actionable_get_action_target_value proto :ptr
gtk_actionable_set_action_target_value proto :ptr, :ptr

gtk_actionable_set_action_target proto :ptr, :ptr, :vararg

gtk_actionable_set_detailed_action_name proto :ptr, :ptr

endif
