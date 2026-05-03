ifndef __G_CONTENT_TYPE_H__
define __G_CONTENT_TYPE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

g_content_type_equals proto :ptr, :ptr
g_content_type_is_a proto :ptr, :ptr
g_content_type_is_mime_type proto :ptr, :ptr
g_content_type_is_unknown proto :ptr
g_content_type_get_description proto :ptr
g_content_type_get_mime_type proto :ptr
g_content_type_get_icon proto :ptr
g_content_type_get_symbolic_icon proto :ptr
g_content_type_get_generic_icon_name proto :ptr
g_content_type_can_be_executable proto :ptr
g_content_type_from_mime_type proto :ptr
g_content_type_guess proto :ptr, :ptr, :gsize, :ptr
g_content_type_guess_for_tree proto :ptr
g_content_types_get_registered proto

ifndef __GTK_DOC_IGNORE__
g_content_type_get_mime_dirs proto
g_content_type_set_mime_dirs proto :ptr
endif

endif
