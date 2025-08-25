ifndef __G_KEY_FILE_H__
define __G_KEY_FILE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gbytes.inc
include glib/gerror.inc

.enum GKeyFileError {
    G_KEY_FILE_ERROR_UNKNOWN_ENCODING,
    G_KEY_FILE_ERROR_PARSE,
    G_KEY_FILE_ERROR_NOT_FOUND,
    G_KEY_FILE_ERROR_KEY_NOT_FOUND,
    G_KEY_FILE_ERROR_GROUP_NOT_FOUND,
    G_KEY_FILE_ERROR_INVALID_VALUE
    }

G_KEY_FILE_ERROR equ (g_key_file_error_quark ())

g_key_file_error_quark proto __cdecl

.enum GKeyFileFlags {
    G_KEY_FILE_NONE              = 0,
    G_KEY_FILE_KEEP_COMMENTS     = 1 shl 0,
    G_KEY_FILE_KEEP_TRANSLATIONS = 1 shl 1
    }

g_key_file_new proto __cdecl
g_key_file_ref proto __cdecl :ptr
g_key_file_unref proto __cdecl :ptr
g_key_file_free proto __cdecl :ptr
g_key_file_set_list_separator proto __cdecl :ptr, :gchar
g_key_file_load_from_file proto __cdecl :ptr, :ptr, :GKeyFileFlags, :ptr
g_key_file_load_from_data proto __cdecl :ptr, :ptr, :gsize, :GKeyFileFlags, :ptr
g_key_file_load_from_bytes proto __cdecl :ptr, :ptr, :GKeyFileFlags, :ptr
g_key_file_load_from_dirs proto __cdecl :ptr, :ptr, :ptr, :ptr, :GKeyFileFlags, :ptr
g_key_file_load_from_data_dirs proto __cdecl :ptr, :ptr, :ptr, :GKeyFileFlags, :ptr
g_key_file_to_data proto __cdecl :ptr, :ptr, :ptr
g_key_file_save_to_file proto __cdecl :ptr, :ptr, :ptr
g_key_file_get_start_group proto __cdecl :ptr
g_key_file_get_groups proto __cdecl :ptr, :ptr
g_key_file_get_keys proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_has_group proto __cdecl :ptr, :ptr
g_key_file_has_key proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_get_value proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_value proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_get_string proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_string proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_get_locale_string proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_get_locale_for_key proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_locale_string proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_get_boolean proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_boolean proto __cdecl :ptr, :ptr, :ptr, :gboolean
g_key_file_get_integer proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_integer proto __cdecl :ptr, :ptr, :ptr, :gint
g_key_file_get_int64 proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_int64 proto __cdecl :ptr, :ptr, :ptr, :gint64
g_key_file_get_uint64 proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_uint64 proto __cdecl :ptr, :ptr, :ptr, :guint64
g_key_file_get_double proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_set_double proto __cdecl :ptr, :ptr, :ptr, :gdouble
g_key_file_get_string_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_set_string_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :gsize
g_key_file_get_locale_string_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_set_locale_string_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :gsize
g_key_file_get_boolean_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_set_boolean_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :gsize
g_key_file_get_integer_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_set_double_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :gsize
g_key_file_get_double_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_set_integer_list proto __cdecl :ptr, :ptr, :ptr, :ptr, :gsize
g_key_file_set_comment proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr
g_key_file_get_comment proto __cdecl :ptr, :ptr, :ptr, :ptr

g_key_file_remove_comment proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_remove_key proto __cdecl :ptr, :ptr, :ptr, :ptr
g_key_file_remove_group proto __cdecl :ptr, :ptr, :ptr

define G_KEY_FILE_DESKTOP_GROUP                <"Desktop Entry">

define G_KEY_FILE_DESKTOP_KEY_TYPE             <"Type">
define G_KEY_FILE_DESKTOP_KEY_VERSION          <"Version">
define G_KEY_FILE_DESKTOP_KEY_NAME             <"Name">
define G_KEY_FILE_DESKTOP_KEY_GENERIC_NAME     <"GenericName">
define G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY       <"NoDisplay">
define G_KEY_FILE_DESKTOP_KEY_COMMENT          <"Comment">
define G_KEY_FILE_DESKTOP_KEY_ICON             <"Icon">
define G_KEY_FILE_DESKTOP_KEY_HIDDEN           <"Hidden">
define G_KEY_FILE_DESKTOP_KEY_ONLY_SHOW_IN     <"OnlyShowIn">
define G_KEY_FILE_DESKTOP_KEY_NOT_SHOW_IN      <"NotShowIn">
define G_KEY_FILE_DESKTOP_KEY_TRY_EXEC         <"TryExec">
define G_KEY_FILE_DESKTOP_KEY_EXEC             <"Exec">
define G_KEY_FILE_DESKTOP_KEY_PATH             <"Path">
define G_KEY_FILE_DESKTOP_KEY_TERMINAL         <"Terminal">
define G_KEY_FILE_DESKTOP_KEY_MIME_TYPE        <"MimeType">
define G_KEY_FILE_DESKTOP_KEY_CATEGORIES       <"Categories">
define G_KEY_FILE_DESKTOP_KEY_STARTUP_NOTIFY   <"StartupNotify">
define G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS <"StartupWMClass">
define G_KEY_FILE_DESKTOP_KEY_URL              <"URL">
define G_KEY_FILE_DESKTOP_KEY_DBUS_ACTIVATABLE <"DBusActivatable">
define G_KEY_FILE_DESKTOP_KEY_ACTIONS          <"Actions">

define G_KEY_FILE_DESKTOP_TYPE_APPLICATION     <"Application">
define G_KEY_FILE_DESKTOP_TYPE_LINK            <"Link">
define G_KEY_FILE_DESKTOP_TYPE_DIRECTORY       <"Directory">

endif
