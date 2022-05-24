ifndef __G_ACTION_MAP_H__
define __G_ACTION_MAP_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_ACTION_MAP <g_action_map_get_type ()>
G_ACTION_MAP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_ACTION_MAP, GActionMap))>
  endm
G_IS_ACTION_MAP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_ACTION_MAP))>
  endm
G_ACTION_MAP_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_ACTION_MAP, GActionMapInterface))>
  endm

_GActionMapInterface    struct
g_iface                 GTypeInterface <>
lookup_action           proc :ptr, :ptr
add_action              proc :ptr, :ptr
remove_action           proc :ptr, :ptr
_GActionMapInterface    ends
GActionMapInterface     typedef _GActionMapInterface

_GActionEntry           struct
name                    ptr gchar ?
activate                proc :ptr, :ptr, :gpointer
parameter_type          ptr gchar ?
state                   ptr gchar ?
change_state            proc :ptr, :ptr, :gpointer
padding                 gsize 3 dup(?)
_GActionEntry           ends
GActionEntry            typedef _GActionEntry

g_action_map_get_type proto

g_action_map_lookup_action proto :ptr, :ptr
g_action_map_add_action proto :ptr, :ptr
g_action_map_remove_action proto :ptr, :ptr
g_action_map_add_action_entries proto :ptr, :ptr, :gint, :gpointer

endif
