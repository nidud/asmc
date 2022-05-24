ifndef __G_DEBUG_CONTROLLER_DBUS_H__
define __G_DEBUG_CONTROLLER_DBUS_H__

include glib.inc
include glib-object.inc

define G_TYPE_DEBUG_CONTROLLER_DBUS <g_debug_controller_dbus_get_type ()>

_GDebugControllerDBusClass struct
parent_class            GObjectClass <>
authorize               proc :ptr, :ptr
padding                 gpointer 12 dup(?)
_GDebugControllerDBusClass ends
GDebugControllerDBusClass typedef _GDebugControllerDBusClass

g_debug_controller_dbus_new proto :ptr, :ptr, :ptr
g_debug_controller_dbus_stop proto :ptr

endif
