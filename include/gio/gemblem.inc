ifndef __G_EMBLEM_H__
define __G_EMBLEM_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gioenums.inc

define G_TYPE_EMBLEM         <g_emblem_get_type ()>
G_EMBLEM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_EMBLEM, GEmblem))>
  endm
G_EMBLEM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_EMBLEM, GEmblemClass))>
  endm
G_IS_EMBLEM macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_EMBLEM))>
  endm
G_IS_EMBLEM_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_EMBLEM))>
  endm
G_EMBLEM_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_EMBLEM, GEmblemClass))>
  endm

g_emblem_get_type proto

g_emblem_new proto :ptr
g_emblem_new_with_origin proto :ptr, :GEmblemOrigin
g_emblem_get_icon proto :ptr
g_emblem_get_origin proto :ptr

endif
