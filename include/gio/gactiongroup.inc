ifndef __G_ACTION_GROUP_H__
define __G_ACTION_GROUP_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_ACTION_GROUP                                 <g_action_group_get_type>
G_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst),  G_TYPE_ACTION_GROUP, GActionGroup))>
  endm
G_IS_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_ACTION_GROUP))>
  endm
G_ACTION_GROUP_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_ACTION_GROUP, GActionGroupInterface))>
  endm

_GActionGroupInterface  struct
g_iface                 GTypeInterface <>
has_action              proc :ptr, :ptr
list_actions            proc :ptr
get_action_enabled      proc :ptr, :ptr
get_action_parameter_type proc :ptr, :ptr
get_action_state_type   proc :ptr, :ptr
get_action_state_hint   proc :ptr, :ptr
get_action_state        proc :ptr, :ptr
change_action_state     proc :ptr, :ptr, :ptr
activate_action         proc :ptr, :ptr, :ptr
action_added            proc :ptr, :ptr
action_removed          proc :ptr, :ptr
action_enabled_changed  proc :ptr, :ptr, :gboolean
action_state_changed    proc :ptr, :ptr, :ptr
query_action            proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
_GActionGroupInterface  ends
GActionGroupInterface   typedef _GActionGroupInterface

g_action_group_get_type proto

g_action_group_has_action proto :ptr, :ptr
g_action_group_list_actions proto :ptr

g_action_group_get_action_parameter_type proto :ptr, :ptr
g_action_group_get_action_state_type proto :ptr, :ptr
g_action_group_get_action_state_hint proto :ptr, :ptr

g_action_group_get_action_enabled proto :ptr, :ptr

g_action_group_get_action_state proto :ptr, :ptr
g_action_group_change_action_state proto :ptr, :ptr, :ptr

g_action_group_activate_action proto :ptr, :ptr, :ptr


g_action_group_action_added proto :ptr, :ptr
g_action_group_action_removed proto :ptr, :ptr
g_action_group_action_enabled_changed proto :ptr, :ptr, :gboolean

g_action_group_action_state_changed proto :ptr, :ptr, :ptr

g_action_group_query_action proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

endif
