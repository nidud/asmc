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

;GBookmarkFile
g_bookmark_file_new proto __cdecl
;void
g_bookmark_file_free proto __cdecl \
	      bookmark: ptr GBookmarkFile


;gboolean
g_bookmark_file_load_from_file proto __cdecl \
	      bookmark: ptr GBookmarkFile,
	      filename: ptr gchar,
		 error: ptr GError

;gboolean
g_bookmark_file_load_from_data proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		  data: ptr gchar,
		length: gsize,
		 error: ptr GError

;gboolean
g_bookmark_file_load_from_data_dirs proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		  file: ptr gchar,
	     full_path: ptr gchar,
		 error: ptr GError

;gchar
g_bookmark_file_to_data proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		length: ptr gsize,
		 error: ptr GError

;gboolean
g_bookmark_file_to_file proto __cdecl \
	      bookmark: ptr GBookmarkFile,
	      filename: ptr gchar,
		 error: ptr GError


;void
g_bookmark_file_set_title proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 title: ptr gchar

;gchar
g_bookmark_file_get_title proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 error: ptr GError

;void
g_bookmark_file_set_description proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
	   description: ptr gchar

;gchar
g_bookmark_file_get_description proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 error: ptr GError

;void
g_bookmark_file_set_mime_type proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
	     mime_type: ptr gchar

;gchar
g_bookmark_file_get_mime_type proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 error: ptr GError

;void
g_bookmark_file_set_groups proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		groups: ptr gchar,
		length: gsize

;void
g_bookmark_file_add_group proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		   grp: ptr gchar

;gboolean
g_bookmark_file_has_group proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		   grp: ptr gchar,
		 error: ptr GError

;gchar
g_bookmark_file_get_groups proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		length: ptr gsize,
		 error: ptr GError

;void
g_bookmark_file_add_application proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  name: ptr gchar,
		  exec: ptr gchar

;gboolean
g_bookmark_file_has_application proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  name: ptr gchar,
		 error: ptr GError

;gchar
g_bookmark_file_get_applications proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		length: ptr gsize,
		 error: ptr GError

g_bookmark_file_set_app_info proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  name: ptr gchar,
		  exec: ptr gchar,
		 count: gint,
		 stamp: time_t,
		 error: ptr GError

;gboolean
g_bookmark_file_set_application_info proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		  name: ptr char_t,
		  exec: ptr char_t,
		 count: SINT,
		 stamp: ptr GDateTime,
		 error: ptr GError

g_bookmark_file_get_app_info proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  name: ptr gchar,
		  exec: ptr gchar,
		 count: ptr guint,
		 stamp: ptr time_t,
		 error: ptr GError

;gboolean
g_bookmark_file_get_application_info proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		  name: ptr char_t,
		  exec: ptr char_t,
		 count: ptr SINT,
		 stamp: ptr GDateTime,
		 error: ptr GError

;void
g_bookmark_file_set_is_private proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
	    is_private: gboolean

;gboolean
g_bookmark_file_get_is_private proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 error: ptr GError

;void
g_bookmark_file_set_icon proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  href: ptr gchar,
	     mime_type: ptr gchar

;gboolean
g_bookmark_file_get_icon proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  href: ptr gchar,
	     mime_type: ptr gchar,
		 error: ptr GError

;void
g_bookmark_file_set_added proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 added: time_t

;void
g_bookmark_file_set_added_date_time proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		 added: ptr GDateTime


g_bookmark_file_get_added proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 error: ptr GError
;GDateTime
g_bookmark_file_get_added_date_time proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		 error: ptr GError


;void
g_bookmark_file_set_modified proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
	      modified: time_t

;void
g_bookmark_file_set_modified_date_time proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
	      modified: ptr GDateTime


g_bookmark_file_get_modified proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		 error: ptr GError

;GDateTime
g_bookmark_file_get_modified_date_time proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		 error: ptr GError

;void
g_bookmark_file_set_visited proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
	       visited: time_t

;void
g_bookmark_file_set_visited_date_time proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
	       visited: ptr GDateTime

g_bookmark_file_get_visited proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		 error: ptr GError
;GDateTime
g_bookmark_file_get_visited_date_time proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr char_t,
		 error: ptr GError

;gboolean
g_bookmark_file_has_item proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar

;gint
g_bookmark_file_get_size proto __cdecl \
	      bookmark: ptr GBookmarkFile

;gchar
g_bookmark_file_get_uris proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		length: ptr gsize

;gboolean
g_bookmark_file_remove_group proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		   grp: ptr gchar,
		 error: ptr GError

;gboolean
g_bookmark_file_remove_application proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		  name: ptr gchar,
		 error: ptr GError

;gboolean
g_bookmark_file_remove_item proto __cdecl \
	      bookmark: ptr GBookmarkFile,
		   uri: ptr gchar,
		 error: ptr GError

;gboolean
g_bookmark_file_move_item proto __cdecl \
	      bookmark: ptr GBookmarkFile,
	       old_uri: ptr gchar,
	       new_uri: ptr gchar,
		 error: ptr GError


endif
