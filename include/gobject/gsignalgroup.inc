ifndef __G_SIGNAL_GROUP_H__
define __G_SIGNAL_GROUP_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc
include gobject/gobject.inc
include gobject/gsignal.inc

G_SIGNAL_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SIGNAL_GROUP, GSignalGroup))>
  endm
G_IS_SIGNAL_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SIGNAL_GROUP))>
  endm
define G_TYPE_SIGNAL_GROUP    (g_signal_group_get_type())


;GSignalGroup            typedef _GSignalGroup

g_signal_group_get_type proto
g_signal_group_new proto :GType
g_signal_group_set_target proto :ptr, :gpointer
g_signal_group_dup_target proto :ptr
g_signal_group_block proto :ptr
g_signal_group_unblock proto :ptr
g_signal_group_connect_object proto :ptr, :ptr, :GCallback, :gpointer, :GConnectFlags
g_signal_group_connect_data proto :ptr, :ptr, :GCallback, :gpointer, :GClosureNotify, :GConnectFlags
g_signal_group_connect proto :ptr, :ptr, :GCallback, :gpointer
g_signal_group_connect_after proto :ptr, :ptr, :GCallback, :gpointer
g_signal_group_connect_swapped proto :ptr, :ptr, :GCallback, :gpointer

endif
