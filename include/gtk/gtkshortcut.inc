ifndef __GTK_SHORTCUT_H__
define __GTK_SHORTCUT_H__

include gtk/gtktypes.inc

define GTK_TYPE_SHORTCUT <gtk_shortcut_get_type>

gtk_shortcut_new proto :ptr, :ptr
gtk_shortcut_new_with_arguments proto :ptr, :ptr, :ptr, :vararg

gtk_shortcut_get_trigger proto :ptr
gtk_shortcut_set_trigger proto :ptr, :ptr
gtk_shortcut_get_action proto :ptr
gtk_shortcut_set_action proto :ptr, :ptr

gtk_shortcut_get_arguments proto :ptr
gtk_shortcut_set_arguments proto :ptr, :ptr

endif
