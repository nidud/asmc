ifndef __G_ASYNC_RESULT_H__
define __G_ASYNC_RESULT_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_ASYNC_RESULT            <g_async_result_get_type ()>
G_ASYNC_RESULT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_ASYNC_RESULT, GAsyncResult))>
  endm
G_IS_ASYNC_RESULT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_ASYNC_RESULT))>
  endm
G_ASYNC_RESULT_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_ASYNC_RESULT, GAsyncResultIface))>
  endm

_GAsyncResultIface      struct
g_iface                 GTypeInterface <>
get_user_data           proc :ptr
get_source_object       proc :ptr
is_tagged               proc :ptr, :gpointer
_GAsyncResultIface      ends
GAsyncResultIface       typedef _GAsyncResultIface

g_async_result_get_type proto
g_async_result_get_user_data proto :ptr
g_async_result_get_source_object proto :ptr
g_async_result_legacy_propagate_error proto :ptr, :ptr
g_async_result_is_tagged proto :ptr, :gpointer

endif
