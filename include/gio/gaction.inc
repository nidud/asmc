ifndef __G_ACTION_H__
define __G_ACTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_ACTION                                       <g_action_get_type>
G_ACTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_ACTION, GAction))>
  endm
G_IS_ACTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_ACTION))>
  endm
G_ACTION_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_ACTION, GActionInterface))>
  endm

_GActionInterface       struct
g_iface                 GTypeInterface <>
get_name                proc :ptr
get_parameter_type      proc :ptr
get_state_type          proc :ptr
get_state_hint          proc :ptr
get_enabled             proc :ptr
get_state               proc :ptr
change_state            proc :ptr, :ptr
activate                proc :ptr, :ptr
_GActionInterface       ends
GActionInterface        typedef _GActionInterface

g_action_get_type proto

g_action_get_name proto :ptr
g_action_get_parameter_type proto :ptr
g_action_get_state_type proto :ptr
g_action_get_state_hint proto :ptr

g_action_get_enabled proto :ptr
g_action_get_state proto :ptr

g_action_change_state proto :ptr, :ptr
g_action_activate proto :ptr, :ptr

g_action_name_is_valid proto :ptr

g_action_parse_detailed_name proto :ptr, :ptr, :ptr, :ptr

g_action_print_detailed_name proto :ptr, :ptr

endif
