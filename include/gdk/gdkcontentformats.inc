ifndef __GTK_CONTENT_FORMATS_H__
define __GTK_CONTENT_FORMATS_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_CONTENT_FORMATS    <gdk_content_formats_get_type>

gdk_intern_mime_type proto :ptr

gdk_content_formats_get_type proto
gdk_content_formats_new proto :ptr, :guint
gdk_content_formats_new_for_gtype proto :GType
gdk_content_formats_parse proto :ptr
gdk_content_formats_ref proto :ptr
gdk_content_formats_unref proto :ptr

gdk_content_formats_print proto :ptr, :ptr
gdk_content_formats_to_string proto :ptr

gdk_content_formats_get_gtypes proto :ptr, :ptr
gdk_content_formats_get_mime_types proto :ptr, :ptr

gdk_content_formats_union proto :ptr, :ptr
gdk_content_formats_match proto :ptr, :ptr
gdk_content_formats_match_gtype proto :ptr, :ptr
gdk_content_formats_match_mime_type proto :ptr, :ptr
gdk_content_formats_contain_gtype proto :ptr, :GType
gdk_content_formats_contain_mime_type proto :ptr, :ptr

define GDK_TYPE_CONTENT_FORMATS_BUILDER <gdk_content_formats_builder_get_type>

;GdkContentFormatsBuilder typedef _GdkContentFormatsBuilder

gdk_content_formats_builder_get_type proto

gdk_content_formats_builder_new proto
gdk_content_formats_builder_ref proto :ptr
gdk_content_formats_builder_unref proto :ptr
gdk_content_formats_builder_free_to_formats proto :ptr
gdk_content_formats_builder_to_formats proto :ptr
gdk_content_formats_builder_add_formats proto :ptr, :ptr
gdk_content_formats_builder_add_mime_type proto :ptr, :ptr
gdk_content_formats_builder_add_gtype proto :ptr, :GType


define GDK_TYPE_FILE_LIST <gdk_file_list_get_type>
gdk_file_list_get_type proto

;GdkFileList             typedef _GdkFileList

gdk_file_list_get_files proto :ptr

endif
