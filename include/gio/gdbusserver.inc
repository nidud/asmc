ifndef __G_DBUS_SERVER_H__
define __G_DBUS_SERVER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_DBUS_SERVER         <g_dbus_server_get_type>
G_DBUS_SERVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_SERVER, GDBusServer))>
  endm
G_IS_DBUS_SERVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_SERVER))>
  endm

g_dbus_server_get_type proto
g_dbus_server_new_sync proto :ptr, :GDBusServerFlags, :ptr, :ptr, :ptr, :ptr
g_dbus_server_get_client_address proto :ptr
g_dbus_server_get_guid proto :ptr
g_dbus_server_get_flags proto :ptr
g_dbus_server_start proto :ptr
g_dbus_server_stop proto :ptr
g_dbus_server_is_active proto :ptr

endif
