ifndef __G_ICON_H__
define __G_ICON_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_ICON            <g_icon_get_type ()>
G_ICON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_ICON, GIcon))>
  endm
G_IS_ICON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_ICON))>
  endm
G_ICON_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_ICON, GIconIface))>
  endm

_GIconIface             struct
g_iface                 GTypeInterface <>
hash                    proc :ptr
equal                   proc :ptr, :ptr
to_tokens               proc :ptr, :ptr, :ptr
from_tokens             proc :ptr, :gint, :gint, :ptr
serialize               proc :ptr
_GIconIface             ends
GIconIface              typedef _GIconIface

g_icon_get_type proto

g_icon_hash proto :gconstpointer
g_icon_equal proto :ptr, :ptr
g_icon_to_string proto :ptr
g_icon_new_for_string proto :ptr, :ptr

g_icon_serialize proto :ptr
g_icon_deserialize proto :ptr

endif
