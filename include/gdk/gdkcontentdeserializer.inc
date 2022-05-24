ifndef __GTK_CONTENT_DESERIALIZER_H__
define __GTK_CONTENT_DESERIALIZER_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_CONTENT_DESERIALIZER         <gdk_content_deserializer_get_type ()>
GDK_CONTENT_DESERIALIZER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_CONTENT_DESERIALIZER, GdkContentDeserializer))>
  endm
GDK_IS_CONTENT_DESERIALIZER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_CONTENT_DESERIALIZER))>
  endm

;GdkContentDeserializer  typedef _GdkContentDeserializer

CALLBACK(GdkContentDeserializeFunc, :ptr)

gdk_content_deserializer_get_type proto

gdk_content_deserializer_get_mime_type proto :ptr
gdk_content_deserializer_get_gtype proto :ptr
gdk_content_deserializer_get_value proto :ptr
gdk_content_deserializer_get_input_stream proto :ptr
gdk_content_deserializer_get_priority proto :ptr
gdk_content_deserializer_get_cancellable proto :ptr
gdk_content_deserializer_get_user_data proto :ptr
gdk_content_deserializer_set_task_data proto :ptr, :gpointer, :GDestroyNotify
gdk_content_deserializer_get_task_data proto :ptr

gdk_content_deserializer_return_success proto :ptr
gdk_content_deserializer_return_error proto :ptr, :ptr

gdk_content_formats_union_deserialize_gtypes proto :ptr
gdk_content_formats_union_deserialize_mime_types proto :ptr

gdk_content_register_deserializer proto :ptr, :GType, :GdkContentDeserializeFunc, :gpointer, :GDestroyNotify
gdk_content_deserialize_async proto :ptr, :ptr, :GType, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_content_deserialize_finish proto :ptr, :ptr, :ptr

endif
