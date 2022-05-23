ifndef __G_MENU_EXPORTER_H__
define __G_MENU_EXPORTER_H__

include gio/gdbusconnection.inc
include gio/gmenumodel.inc

;guint
g_dbus_connection_export_menu_model proto __cdecl \
            connection: ptr GDBusConnection,
           object_path: ptr gchar,
                  menu: ptr GMenuModel,
                 error: ptr GError


;void
g_dbus_connection_unexport_menu_model proto __cdecl \
            connection: ptr GDBusConnection,
             export_id: guint


endif
