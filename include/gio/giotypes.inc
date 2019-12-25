ifndef __GIO_TYPES_H__
__GIO_TYPES_H__ equ <>
if NOT defined (__GIO_GIO_H_INSIDE__) AND NOT defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gioenums.inc

G_BEGIN_DECLS

CALLBACKC(GAsyncReadyCallback, :ptr GObject, :ptr GAsyncResult, :gpointer)
CALLBACKC(GFileProgressCallback, :goffset, :goffset, :gpointer)
CALLBACKC(GFileReadMoreCallback, :string_t, :goffset, :gpointer)
CALLBACKC(GFileMeasureProgressCallback, :gboolean, :guint64, :guint64, :guint64, :gpointer)
CALLBACKC(GIOSchedulerJobFunc, :ptr GIOSchedulerJob, :ptr GCancellable, :gpointer)
CALLBACKC(GSimpleAsyncThreadFunc, :ptr GSimpleAsyncResult, :ptr GObject, :ptr GCancellable)
CALLBACKC(GSocketSourceFunc, :ptr GSocket, :GIOCondition, :gpointer)
CALLBACKC(GDatagramBasedSourceFunc, :ptr GDatagramBased, :GIOCondition, :gpointer)

GInputVector		STRUC
buffer			gpointer ?
size			gsize ?
GInputVector		ENDS

GInputMessage		STRUC
address			ptr_t ?
vectors			ptr_t ?
num_vectors		guint ?
bytes_received		gsize ?
flags			gint ?
control_messages	ptr_t ?
num_control_messages	ptr_t ?
GInputMessage		ENDS

GOutputVector		STRUC
buffer			gconstpointer ?
size			gsize ?
GOutputVector		ENDS

GOutputMessage		STRUC
address			ptr_t ?
vectors			ptr_t ?
num_vectors		guint ?
bytes_sent		guint ?
control_messages	ptr_t ?
num_control_messages	guint ?
GOutputMessage		ENDS

CALLBACKC(GCancellableSourceFunc, :ptr GCancellable, :gpointer)
CALLBACKC(GPollableSourceFunc, :ptr GObject, :gpointer)
CALLBACKC(GDBusProxyTypeFunc, :ptr GDBusObjectManagerClient, :ptr gchar, :ptr gchar, :gpointer)

G_END_DECLS

endif
