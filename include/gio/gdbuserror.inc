ifndef __G_DBUS_ERROR_H__
define __G_DBUS_ERROR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_DBUS_ERROR <g_dbus_error_quark>

g_dbus_error_quark proto

g_dbus_error_is_remote_error proto :ptr
g_dbus_error_get_remote_error proto :ptr
g_dbus_error_strip_remote_error proto :ptr

_GDBusErrorEntry        struct
error_code              gint ?
dbus_error_name         ptr gchar ?
_GDBusErrorEntry        ends
GDBusErrorEntry         typedef _GDBusErrorEntry

g_dbus_error_register_error proto :GQuark, :gint, :ptr
g_dbus_error_unregister_error proto :GQuark, :gint, :ptr
g_dbus_error_register_error_domain proto :ptr, :ptr, :ptr, :guint

g_dbus_error_new_for_dbus_error proto :ptr, :ptr
g_dbus_error_encode_gerror proto :ptr


endif
