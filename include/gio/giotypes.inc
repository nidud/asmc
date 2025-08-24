ifndef __GIO_TYPES_H__
define __GIO_TYPES_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gioenums.inc

CALLBACK(GAsyncReadyCallback, :ptr, :ptr, :gpointer)
CALLBACK(GFileProgressCallback, :goffset, :goffset, :gpointer)
CALLBACK(GFileReadMoreCallback, :ptr, :goffset, :gpointer)
CALLBACK(GFileMeasureProgressCallback, :gboolean, :guint64, :guint64, :guint64, :gpointer)
CALLBACK(GIOSchedulerJobFunc, :ptr, :ptr, :gpointer)
CALLBACK(GSimpleAsyncThreadFunc, :ptr, :ptr, :ptr)
CALLBACK(GSocketSourceFunc, :ptr, :GIOCondition, :gpointer)
CALLBACK(GDatagramBasedSourceFunc, :ptr, :GIOCondition, :gpointer)

GInputVector            struct
buffer                  gpointer ?
size                    gsize ?
GInputVector            ends

GInputMessage           struct
address                 ptr GSocketAddress ?
vectors                 ptr GInputVector ?
num_vectors             guint ?
bytes_received          gsize ?
flags                   gint ?
control_messages        ptr GSocketControlMessage ?
num_control_messages    ptr guint ?
GInputMessage           ends

GOutputVector           struct
buffer                  gconstpointer ?
size                    gsize ?
GOutputVector           ends


GOutputMessage          struct
address                 ptr GSocketAddress ?
vectors                 ptr GOutputVector ?
num_vectors             guint ?
bytes_sent              guint ?
control_messages        ptr GSocketControlMessage ?
num_control_messages    guint ?
GOutputMessage          ends

CALLBACK(GCancellableSourceFunc, :ptr, :gpointer)
CALLBACK(GPollableSourceFunc, :ptr, :gpointer)

CALLBACK(GDBusProxyTypeFunc, :ptr, :ptr, :ptr, :gpointer)

endif
