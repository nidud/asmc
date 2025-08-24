ifndef __G_REMOTE_ACTION_GROUP_H__
define __G_REMOTE_ACTION_GROUP_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_REMOTE_ACTION_GROUP                          <g_remote_action_group_get_type ()>
G_REMOTE_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_REMOTE_ACTION_GROUP, GRemoteActionGroup))>
  endm
G_IS_REMOTE_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_REMOTE_ACTION_GROUP))>
  endm
G_REMOTE_ACTION_GROUP_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_REMOTE_ACTION_GROUP,GRemoteActionGroupInterface))>
  endm

GRemoteActionGroupInterface struct
g_iface                 GTypeInterface <>
activate_action_full    proc :ptr, :ptr, :ptr, :ptr
change_action_state_full proc :ptr, :ptr, :ptr, :ptr
GRemoteActionGroupInterface ends

g_remote_action_group_get_type proto
g_remote_action_group_activate_action_full proto :ptr, :ptr, :ptr, :ptr
g_remote_action_group_change_action_state_full proto :ptr, :ptr, :ptr, :ptr

endif
