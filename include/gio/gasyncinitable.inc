ifndef __G_ASYNC_INITABLE_H__
define __G_ASYNC_INITABLE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc
include gio/ginitable.inc

define G_TYPE_ASYNC_INITABLE            <g_async_initable_get_type ()>
G_ASYNC_INITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_ASYNC_INITABLE, GAsyncInitable))>
  endm
G_IS_ASYNC_INITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_ASYNC_INITABLE))>
  endm
G_ASYNC_INITABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_ASYNC_INITABLE, GAsyncInitableIface))>
  endm
G_TYPE_IS_ASYNC_INITABLE macro type
  exitm<g_type_is_aype), G_TYPE_ASYNC_INITABLE))>
  endm

_GAsyncInitableIface    struct
g_iface                 GTypeInterface <>
init_async              proc :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
init_finish             proc :ptr, :ptr, :ptr
_GAsyncInitableIface    ends
GAsyncInitableIface     typedef _GAsyncInitableIface

g_async_initable_get_type proto
g_async_initable_init_async proto :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_async_initable_init_finish proto :ptr, :ptr, :ptr
g_async_initable_new_async proto :GType, :sdword, :ptr, :GAsyncReadyCallback, :gpointer, :ptr, :vararg

g_async_initable_newv_async proto :GType, :guint, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer

g_async_initable_new_valist_async proto :GType, :ptr, :va_list, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
g_async_initable_new_finish proto :ptr, :ptr, :ptr

endif
