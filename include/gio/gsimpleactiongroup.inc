ifndef __G_SIMPLE_ACTION_GROUP_H__
define __G_SIMPLE_ACTION_GROUP_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gactiongroup.inc
include gactionmap.inc

define G_TYPE_SIMPLE_ACTION_GROUP                          <g_simple_action_group_get_type>
G_SIMPLE_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SIMPLE_ACTION_GROUP, GSimpleActionGroup))>
  endm
G_SIMPLE_ACTION_GROUP_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SIMPLE_ACTION_GROUP, GSimpleActionGroupClass))>
  endm
G_IS_SIMPLE_ACTION_GROUP macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SIMPLE_ACTION_GROUP))>
  endm
G_IS_SIMPLE_ACTION_GROUP_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SIMPLE_ACTION_GROUP))>
  endm
G_SIMPLE_ACTION_GROUP_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SIMPLE_ACTION_GROUP, GSimpleActionGroupClass))>
  endm

;GSimpleActionGroupPrivate typedef _GSimpleActionGroupPrivate

_GSimpleActionGroup     struct
parent_instance         GObject <>
priv                    ptr GSimpleActionGroupPrivate ?
_GSimpleActionGroup     ends
GSimpleActionGroup      typedef _GSimpleActionGroup

_GSimpleActionGroupClass struct
parent_class            GObjectClass <>
padding                 gpointer 12 dup(?)
_GSimpleActionGroupClass ends
GSimpleActionGroupClass typedef _GSimpleActionGroupClass

g_simple_action_group_get_type proto
g_simple_action_group_new proto
g_simple_action_group_lookup proto :ptr, :ptr
g_simple_action_group_insert proto :ptr, :ptr
g_simple_action_group_remove proto :ptr, :ptr
g_simple_action_group_add_entries proto :ptr, :ptr, :gint, :gpointer

endif
