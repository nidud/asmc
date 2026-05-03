ifndef __G_DBUS_NAME_OWNING_H__
define __G_DBUS_NAME_OWNING_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

CALLBACK(GBusAcquiredCallback, :ptr, :ptr, :gpointer)
CALLBACK(GBusNameAcquiredCallback, :ptr, :ptr, :gpointer)
CALLBACK(GBusNameLostCallback, :ptr, :ptr, :gpointer)

g_bus_own_name proto :GBusType, :ptr, :GBusNameOwnerFlags, :GBusAcquiredCallback, :GBusNameAcquiredCallback, :GBusNameLostCallback, :gpointer, :GDestroyNotify
g_bus_own_name_on_connection proto :ptr, :ptr, :GBusNameOwnerFlags, :GBusNameAcquiredCallback, :GBusNameLostCallback, :gpointer, :GDestroyNotify
g_bus_own_name_with_closures proto :GBusType, :ptr, :GBusNameOwnerFlags, :ptr, :ptr, :ptr
g_bus_own_name_on_connection_with_closures proto :ptr, :ptr, :GBusNameOwnerFlags, :ptr, :ptr
g_bus_unown_name proto :guint

endif
