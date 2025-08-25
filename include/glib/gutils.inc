ifndef __G_UTILS_H__
define __G_UTILS_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include stdarg.inc

g_get_user_name proto __cdecl
g_get_real_name proto __cdecl
g_get_home_dir proto __cdecl
g_get_tmp_dir proto __cdecl
g_get_host_name proto __cdecl
g_get_prgname proto __cdecl
g_set_prgname proto __cdecl :ptr

g_get_application_name proto __cdecl
g_set_application_name proto __cdecl :ptr

g_reload_user_special_dirs_cache proto __cdecl
g_get_user_data_dir proto __cdecl
g_get_user_config_dir proto __cdecl
g_get_user_cache_dir proto __cdecl
g_get_system_data_dirs proto __cdecl

ifdef G_OS_WIN32
a_dirs_for_module proto __cdecl
endif

if defined (G_OS_WIN32) AND defined (G_CAN_INLINE) AND NOT defined (__cplusplus)
endif

g_get_system_config_dirs proto __cdecl
g_get_user_runtime_dir proto __cdecl

.enum GUserDirectory {
  G_USER_DIRECTORY_DESKTOP,
  G_USER_DIRECTORY_DOCUMENTS,
  G_USER_DIRECTORY_DOWNLOAD,
  G_USER_DIRECTORY_MUSIC,
  G_USER_DIRECTORY_PICTURES,
  G_USER_DIRECTORY_PUBLIC_SHARE,
  G_USER_DIRECTORY_TEMPLATES,
  G_USER_DIRECTORY_VIDEOS,
  G_USER_N_DIRECTORIES
}

g_get_user_special_dir proto __cdecl :GUserDirectory

GDebugKey		STRUC
key			string_t ?
value			guint ?
GDebugKey		ENDS

g_parse_debug_string proto __cdecl :ptr, :ptr, :guint
g_snprintf proto __Cdecl :ptr, :gulong, :ptr, :vararg
g_vsnprintf proto __cdecl :ptr, :gulong, :ptr, :ptr
g_nullify_pointer proto __cdecl :ptr

.enum GFormatSizeFlags {
  G_FORMAT_SIZE_DEFAULT	    = 0,
  G_FORMAT_SIZE_LONG_FORMAT = 1 shl 0,
  G_FORMAT_SIZE_IEC_UNITS   = 1 shl 1
}

g_format_size_full proto __cdecl :guint64, :GFormatSizeFlags
g_format_size proto __cdecl :guint64
g_format_size_for_display proto __cdecl

ifndef G_DISABLE_DEPRECATED
CALLBACKC(GVoidFunc)
ATEXIT macro p
	exitm<g_ATEXIT(p)>
	endm
g_atexit proto __cdecl :GVoidFunc

ifdef G_OS_WIN32
if (defined(__MINGW_H) AND NOT defined(_STDLIB_H_)) OR (defined(_MSC_VER) AND NOT defined(_INC_STDLIB))
atexit proto __cdecl :ptr
endif
g_atexit macro func
	exitm<atexit(func)>
	endm
endif
endif

g_bit_nth_lsf proto __cdecl :gulong, :gint
g_bit_nth_msf proto __cdecl :gulong, :gint
g_bit_storage proto __cdecl :gulong

endif
