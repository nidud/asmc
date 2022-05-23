ifndef __G_DBUS_AUTH_OBSERVER_H__
define __G_DBUS_AUTH_OBSERVER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc


define G_TYPE_DBUS_AUTH_OBSERVER         <g_dbus_auth_observer_get_type>
G_DBUS_AUTH_OBSERVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_DBUS_AUTH_OBSERVER, GDBusAuthObserver))>
  endm
G_IS_DBUS_AUTH_OBSERVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_DBUS_AUTH_OBSERVER))>
  endm

g_dbus_auth_observer_get_type proto
g_dbus_auth_observer_new proto
g_dbus_auth_observer_authorize_authenticated_peer proto :ptr, :ptr, :ptr
g_dbus_auth_observer_allow_mechanism proto :ptr, :ptr

endif
