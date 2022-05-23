ifndef __G_DBUS_UTILS_H__
define __G_DBUS_UTILS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc


g_dbus_is_guid proto :ptr
g_dbus_generate_guid proto

g_dbus_is_name proto :ptr
g_dbus_is_unique_name proto :ptr
g_dbus_is_member_name proto :ptr
g_dbus_is_interface_name proto :ptr
g_dbus_is_error_name proto :ptr

g_dbus_gvariant_to_gvalue proto :ptr, :ptr
g_dbus_gvalue_to_gvariant proto :ptr, :ptr
g_dbus_escape_object_path_bytestring proto :ptr
g_dbus_escape_object_path proto :ptr
g_dbus_unescape_object_path proto :ptr


endif
