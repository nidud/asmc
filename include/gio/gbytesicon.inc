ifndef __G_BYTES_ICON_H__
define __G_BYTES_ICON_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_BYTES_ICON         <g_bytes_icon_get_type ()>
G_BYTES_ICON macro inst
  exitm<G_TYPE_CHECK_INSTANCE_CAST (inst, G_TYPE_BYTES_ICON, GBytesIcon)>
  endm
G_IS_BYTES_ICON macro inst
  exitm<G_TYPE_CHECK_INSTANCE_TYPE (inst, G_TYPE_BYTES_ICON)>
  endm

g_bytes_icon_get_type proto
g_bytes_icon_new proto :ptr
g_bytes_icon_get_bytes proto :ptr

endif
