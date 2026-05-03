ifndef __G_MENU_EXPORTER_H__
define __G_MENU_EXPORTER_H__

include gio/gdbusconnection.inc
include gio/gmenumodel.inc

g_dbus_connection_export_menu_model proto __cdecl :ptr, :ptr, :ptr, :ptr
g_dbus_connection_unexport_menu_model proto __cdecl :ptr, :guint

endif
