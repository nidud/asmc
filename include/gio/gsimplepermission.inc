ifndef __G_SIMPLE_PERMISSION_H__
define __G_SIMPLE_PERMISSION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_SIMPLE_PERMISSION      <g_simple_permission_get_type ()>
G_SIMPLE_PERMISSION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SIMPLE_PERMISSION, GSimplePermission))>
  endm
G_IS_SIMPLE_PERMISSION macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SIMPLE_PERMISSION))>
  endm

g_simple_permission_get_type proto
g_simple_permission_new proto :gboolean

endif
