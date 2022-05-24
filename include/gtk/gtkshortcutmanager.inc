ifndef __GTK_SHORTCUT_MANAGER_H__
define __GTK_SHORTCUT_MANAGER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkshortcutcontroller.inc
include gtk/gtkwidget.inc

define GTK_TYPE_SHORTCUT_MANAGER <gtk_shortcut_manager_get_type ()>

_GtkShortcutManagerInterface struct
g_iface                 GTypeInterface <>
add_controller          proc :ptr, :ptr
remove_controller       proc :ptr, :ptr
_GtkShortcutManagerInterface ends
GtkShortcutManagerInterface typedef _GtkShortcutManagerInterface

endif
