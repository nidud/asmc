ifndef __G_LOADABLE_ICON_H__
define __G_LOADABLE_ICON_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_LOADABLE_ICON            <g_loadable_icon_get_type ()>
G_LOADABLE_ICON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_LOADABLE_ICON, GLoadableIcon))>
  endm
G_IS_LOADABLE_ICON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_LOADABLE_ICON))>
  endm
G_LOADABLE_ICON_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_LOADABLE_ICON, GLoadableIconIface))>
  endm

_GLoadableIconIface     struct
g_iface                 GTypeInterface <>
load                    proc :ptr, :sdword, :ptr, :ptr, :ptr
load_async              proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
load_finish             proc :ptr, :ptr, :ptr, :ptr
_GLoadableIconIface     ends
GLoadableIconIface      typedef _GLoadableIconIface

g_loadable_icon_get_type proto
g_loadable_icon_load proto :ptr, :sdword, :ptr, :ptr, :ptr
g_loadable_icon_load_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_loadable_icon_load_finish proto :ptr, :ptr, :ptr, :ptr

endif
