ifndef __G_DBUS_MENU_MODEL_H__
define __G_DBUS_MENU_MODEL_H__

include gio/gdbusconnection.inc

define G_TYPE_DBUS_MENU_MODEL          <g_dbus_menu_model_get_type ()>
G_DBUS_MENU_MODEL macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_DBUS_MENU_MODEL, GDBusMenuModel))>
  endm
G_IS_DBUS_MENU_MODEL macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_DBUS_MENU_MODEL))>
  endm

g_dbus_menu_model_get_type proto
g_dbus_menu_model_get proto :ptr, :ptr, :ptr

endif
