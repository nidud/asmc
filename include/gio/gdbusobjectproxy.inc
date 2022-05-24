ifndef __G_DBUS_OBJECT_PROXY_H__
define __G_DBUS_OBJECT_PROXY_H__

include gio/giotypes.inc

define G_TYPE_DBUS_OBJECT_PROXY         <g_dbus_object_proxy_get_type ()>
G_DBUS_OBJECT_PROXY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_OBJECT_PROXY, GDBusObjectProxy))>
  endm
G_DBUS_OBJECT_PROXY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_DBUS_OBJECT_PROXY, GDBusObjectProxyClass))>
  endm
G_DBUS_OBJECT_PROXY_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_DBUS_OBJECT_PROXY, GDBusObjectProxyClass))>
  endm
G_IS_DBUS_OBJECT_PROXY macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_OBJECT_PROXY))>
  endm
G_IS_DBUS_OBJECT_PROXY_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_DBUS_OBJECT_PROXY))>
  endm

;GDBusObjectProxyPrivate typedef _GDBusObjectProxyPrivate

_GDBusObjectProxy       struct
parent_instance         GObject <>
priv                    ptr GDBusObjectProxyPrivate ?
_GDBusObjectProxy       ends
GDBusObjectProxy        typedef _GDBusObjectProxy

_GDBusObjectProxyClass  struct
parent_class            GObjectClass <>
padding                 gpointer 8 dup(?)
_GDBusObjectProxyClass  ends
GDBusObjectProxyClass   typedef _GDBusObjectProxyClass

g_dbus_object_proxy_get_type proto
g_dbus_object_proxy_new proto :ptr, :ptr
g_dbus_object_proxy_get_connection proto :ptr

endif
