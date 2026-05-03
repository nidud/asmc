ifndef __G_BOOKMARK_FILE_H__
define __G_BOOKMARK_FILE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gdatetime.inc
include glib/gerror.inc
include time.inc

define G_BOOKMARK_FILE_ERROR (g_bookmark_file_error_quark ())

.enum GBookmarkFileError {
    G_BOOKMARK_FILE_ERROR_INVALID_URI,
    G_BOOKMARK_FILE_ERROR_INVALID_VALUE,
    G_BOOKMARK_FILE_ERROR_APP_NOT_REGISTERED,
    G_BOOKMARK_FILE_ERROR_URI_NOT_FOUND,
    G_BOOKMARK_FILE_ERROR_READ,
    G_BOOKMARK_FILE_ERROR_UNKNOWN_ENCODING,
    G_BOOKMARK_FILE_ERROR_WRITE,
    G_BOOKMARK_FILE_ERROR_FILE_NOT_FOUND
    }

g_bookmark_file_error_quark proto __cdecl
g_bookmark_file_new proto __cdecl
g_bookmark_file_free proto __cdecl :ptr
g_bookmark_file_load_from_file proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_load_from_data proto __cdecl :ptr, :ptr, :gsize, :ptr
g_bookmark_file_load_from_data_dirs proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_to_data proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_to_file proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_title proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_title proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_description proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_description proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_mime_type proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_mime_type proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_groups proto __cdecl :ptr, :ptr, :ptr, :gsize
g_bookmark_file_add_group proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_has_group proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_get_groups proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_add_application proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_has_application proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_get_applications proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_set_app_info proto __cdecl :ptr, :ptr, :ptr, :ptr, :gint, :time_t, :ptr
g_bookmark_file_set_application_info proto __cdecl :ptr, :ptr, :ptr, :ptr, :SINT, :ptr, :ptr
g_bookmark_file_get_app_info proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_bookmark_file_get_application_info proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_bookmark_file_set_is_private proto __cdecl :ptr, :ptr, :gboolean
g_bookmark_file_get_is_private proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_icon proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_get_icon proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_bookmark_file_set_added proto __cdecl :ptr, :ptr, :time_t
g_bookmark_file_set_added_date_time proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_added proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_added_date_time proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_modified proto __cdecl :ptr, :ptr, :time_t
g_bookmark_file_set_modified_date_time proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_modified proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_modified_date_time proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_set_visited proto __cdecl :ptr, :ptr, :time_t
g_bookmark_file_set_visited_date_time proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_visited proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_get_visited_date_time proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_has_item proto __cdecl :ptr, :ptr
g_bookmark_file_get_size proto __cdecl :ptr
g_bookmark_file_get_uris proto __cdecl :ptr, :ptr
g_bookmark_file_remove_group proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_remove_application proto __cdecl :ptr, :ptr, :ptr, :ptr
g_bookmark_file_remove_item proto __cdecl :ptr, :ptr, :ptr
g_bookmark_file_move_item proto __cdecl :ptr, :ptr, :ptr, :ptr

endif
