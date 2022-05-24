ifndef __G_SIMPLE_ACTION_H__
define __G_SIMPLE_ACTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SIMPLE_ACTION                                <g_simple_action_get_type ()>
G_SIMPLE_ACTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SIMPLE_ACTION, GSimpleAction))>
  endm
G_IS_SIMPLE_ACTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SIMPLE_ACTION))>
  endm

g_simple_action_get_type proto
g_simple_action_new proto :ptr, :ptr
g_simple_action_new_stateful proto :ptr, :ptr, :ptr
g_simple_action_set_enabled proto :ptr, :gboolean
g_simple_action_set_state proto :ptr, :ptr
g_simple_action_set_state_hint proto :ptr, :ptr

endif
