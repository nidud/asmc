ifndef __G_CANCELLABLE_H__
define __G_CANCELLABLE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_CANCELLABLE         <g_cancellable_get_type>
G_CANCELLABLE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_CANCELLABLE, GCancellable))>
  endm
G_CANCELLABLE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_CANCELLABLE, GCancellableClass))>
  endm
G_IS_CANCELLABLE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_CANCELLABLE))>
  endm
G_IS_CANCELLABLE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_CANCELLABLE))>
  endm
G_CANCELLABLE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_CANCELLABLE, GCancellableClass))>
  endm


;GCancellablePrivate     typedef _GCancellablePrivate

_GCancellable           struct
parent_instance         GObject <>
priv                    ptr GCancellablePrivate ?
_GCancellable           ends
GCancellable            typedef _GCancellable

_GCancellableClass      struct
parent_class            GObjectClass <>
cancelled               proc :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_GCancellableClass      ends
GCancellableClass       typedef _GCancellableClass

g_cancellable_get_type proto
g_cancellable_new proto

g_cancellable_is_cancelled proto :ptr
g_cancellable_set_error_if_cancelled proto :ptr, :ptr

g_cancellable_get_fd proto :ptr
g_cancellable_make_pollfd proto :ptr, :ptr
g_cancellable_release_fd proto :ptr

g_cancellable_source_new proto :ptr

g_cancellable_get_current proto
g_cancellable_push_current proto :ptr
g_cancellable_pop_current proto :ptr
g_cancellable_reset proto :ptr
g_cancellable_connect proto :ptr, :GCallback, :gpointer, :GDestroyNotify
g_cancellable_disconnect proto :ptr, :gulong

g_cancellable_cancel proto :ptr

endif
