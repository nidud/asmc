ifndef __G_DBUS_PROXY_H__
define __G_DBUS_PROXY_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc
include gio/gdbusintrospection.inc

define G_TYPE_DBUS_PROXY         <g_dbus_proxy_get_type ()>
G_DBUS_PROXY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_PROXY, GDBusProxy))>
  endm
G_DBUS_PROXY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DBUS_PROXY, GDBusProxyClass))>
  endm
G_DBUS_PROXY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DBUS_PROXY, GDBusProxyClass))>
  endm
G_IS_DBUS_PROXY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_PROXY))>
  endm
G_IS_DBUS_PROXY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DBUS_PROXY))>
  endm

;GDBusProxyPrivate       typedef _GDBusProxyPrivate

_GDBusProxy             struct
parent_instance         GObject <>
priv                    ptr GDBusProxyPrivate ?
_GDBusProxy             ends
GDBusProxy              typedef _GDBusProxy

_GDBusProxyClass        struct
parent_class            GObjectClass <>
g_properties_changed    proc :ptr, :ptr, :ptr
g_signal                proc :ptr, :ptr, :ptr, :ptr
padding                 gpointer 32 dup(?)
_GDBusProxyClass        ends
GDBusProxyClass         typedef _GDBusProxyClass

g_dbus_proxy_get_type proto
g_dbus_proxy_new proto :ptr, :GDBusProxyFlags, :ptr, :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_proxy_new_finish proto :ptr, :ptr
g_dbus_proxy_new_sync proto :ptr, :GDBusProxyFlags, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_dbus_proxy_new_for_bus proto :GBusType, :GDBusProxyFlags, :ptr, :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_proxy_new_for_bus_finish proto :ptr, :ptr
g_dbus_proxy_new_for_bus_sync proto :GBusType, :GDBusProxyFlags, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_dbus_proxy_get_connection proto :ptr
g_dbus_proxy_get_flags proto :ptr
g_dbus_proxy_get_name proto :ptr
g_dbus_proxy_get_name_owner proto :ptr
g_dbus_proxy_get_object_path proto :ptr
g_dbus_proxy_get_interface_name proto :ptr
g_dbus_proxy_get_default_timeout proto :ptr
g_dbus_proxy_set_default_timeout proto :ptr, :gint
g_dbus_proxy_get_interface_info proto :ptr
g_dbus_proxy_set_interface_info proto :ptr, :ptr
g_dbus_proxy_get_cached_property proto :ptr, :ptr
g_dbus_proxy_set_cached_property proto :ptr, :ptr, :ptr
g_dbus_proxy_get_cached_property_names proto :ptr
g_dbus_proxy_call proto :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_proxy_call_finish proto :ptr, :ptr, :ptr
g_dbus_proxy_call_sync proto :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :ptr

g_dbus_proxy_call_with_unix_fd_list proto :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_dbus_proxy_call_with_unix_fd_list_finish proto :ptr, :ptr, :ptr, :ptr
g_dbus_proxy_call_with_unix_fd_list_sync proto :ptr, :ptr, :ptr, :GDBusCallFlags, :gint, :ptr, :ptr, :ptr, :ptr

endif
