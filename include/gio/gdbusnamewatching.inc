ifndef __G_DBUS_NAME_WATCHING_H__
define __G_DBUS_NAME_WATCHING_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

CALLBACK(GBusNameAppearedCallback, :ptr, :ptr, :ptr, :gpointer)
CALLBACK(GBusNameVanishedCallback, :ptr, :ptr, :gpointer)

g_bus_watch_name proto :GBusType, :ptr, :GBusNameWatcherFlags, :GBusNameAppearedCallback, :GBusNameVanishedCallback, :gpointer, :GDestroyNotify
g_bus_watch_name_on_connection proto :ptr, :ptr, :GBusNameWatcherFlags, :GBusNameAppearedCallback, :GBusNameVanishedCallback, :gpointer, :GDestroyNotify
g_bus_watch_name_with_closures proto :GBusType, :ptr, :GBusNameWatcherFlags, :ptr, :ptr
g_bus_watch_name_on_connection_with_closures proto :ptr, :ptr, :GBusNameWatcherFlags, :ptr, :ptr
g_bus_unwatch_name proto :guint

endif
