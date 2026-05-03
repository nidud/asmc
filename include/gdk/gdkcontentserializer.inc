ifndef __GTK_CONTENT_SERIALIZER_H__
define __GTK_CONTENT_SERIALIZER_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif


include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_CONTENT_SERIALIZER         <gdk_content_serializer_get_type ()>
GDK_CONTENT_SERIALIZER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_CONTENT_SERIALIZER, GdkContentSerializer))>
  endm
GDK_IS_CONTENT_SERIALIZER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_CONTENT_SERIALIZER))>
  endm

CALLBACK(GdkContentSerializeFunc, :ptr)

gdk_content_serializer_get_type proto
gdk_content_serializer_get_mime_type proto :ptr
gdk_content_serializer_get_gtype proto :ptr
gdk_content_serializer_get_value proto :ptr
gdk_content_serializer_get_output_stream proto :ptr
gdk_content_serializer_get_priority proto :ptr
gdk_content_serializer_get_cancellable proto :ptr
gdk_content_serializer_get_user_data proto :ptr
gdk_content_serializer_set_task_data proto :ptr, :gpointer, :GDestroyNotify
gdk_content_serializer_get_task_data proto :ptr
gdk_content_serializer_return_success proto :ptr
gdk_content_serializer_return_error proto :ptr, :ptr
gdk_content_formats_union_serialize_gtypes proto :ptr
gdk_content_formats_union_serialize_mime_types proto :ptr
gdk_content_register_serializer proto :GType, :ptr, :GdkContentSerializeFunc, :gpointer, :GDestroyNotify
gdk_content_serialize_async proto :ptr, :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_content_serialize_finish proto :ptr, :ptr

endif
