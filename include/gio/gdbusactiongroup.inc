ifndef __G_DBUS_ACTION_GROUP_H__
define __G_DBUS_ACTION_GROUP_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include giotypes.inc


define G_TYPE_DBUS_ACTION_GROUP                            <g_dbus_action_group_get_type ()>
G_DBUS_ACTION_GROUP macro inst
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_DBUS_ACTION_GROUP, GDBusActionGroup)>
  endm
G_DBUS_ACTION_GROUP_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_DBUS_ACTION_GROUP, GDBusActionGroupClass)>
  endm
G_IS_DBUS_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst),  G_TYPE_DBUS_ACTION_GROUP))>
  endm
G_IS_DBUS_ACTION_GROUP_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_DBUS_ACTION_GROUP))>
  endm
G_DBUS_ACTION_GROUP_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_DBUS_ACTION_GROUP, GDBusActionGroupClass))>
  endm

g_dbus_action_group_get_type proto
g_dbus_action_group_get proto :ptr, :ptr, :ptr

endif
