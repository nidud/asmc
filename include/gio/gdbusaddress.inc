ifndef __G_DBUS_ADDRESS_H__
define __G_DBUS_ADDRESS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

g_dbus_address_escape_value proto :ptr
g_dbus_is_address proto :ptr
g_dbus_is_supported_address proto :ptr, :ptr
g_dbus_address_get_stream proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_address_get_stream_finish proto :ptr, :ptr, :ptr
g_dbus_address_get_stream_sync proto :ptr, :ptr, :ptr, :ptr
g_dbus_address_get_for_bus_sync proto :GBusType, :ptr, :ptr

endif
