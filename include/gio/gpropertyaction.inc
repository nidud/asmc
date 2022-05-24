ifndef __G_PROPERTY_ACTION_H__
define __G_PROPERTY_ACTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_PROPERTY_ACTION                              <g_property_action_get_type ()>
G_PROPERTY_ACTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_PROPERTY_ACTION, GPropertyAction))>
  endm
G_IS_PROPERTY_ACTION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_PROPERTY_ACTION))>
  endm

g_property_action_get_type proto
g_property_action_new proto :ptr, :gpointer, :ptr

endif
