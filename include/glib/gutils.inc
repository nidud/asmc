ifndef __G_UTILS_H__
__G_UTILS_H__ equ <>
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
g_set_prgname proto __cdecl \
	       prgname: ptr gchar

g_get_application_name proto __cdecl
g_set_application_name proto __cdecl \
      application_name: ptr gchar

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

g_get_user_special_dir proto __cdecl \
	     directory: GUserDirectory

GDebugKey		STRUC
key			string_t ?
value			guint ?
GDebugKey		ENDS

;guint
g_parse_debug_string proto __cdecl \
		string: ptr gchar,
		  keys: ptr GDebugKey,
		 nkeys: guint


;gint
g_snprintf proto __Cdecl \
		string: ptr gchar,
		     n: gulong,
		format: ptr,
		      : vararg

;gint
g_vsnprintf proto __cdecl \
		string: ptr gchar,
		     n: gulong,
		format: ptr const,
		  args: va_list


;void
g_nullify_pointer proto __cdecl \
      nullify_location: ptr gpointer


.enum GFormatSizeFlags {
  G_FORMAT_SIZE_DEFAULT	    = 0,
  G_FORMAT_SIZE_LONG_FORMAT = 1 shl 0,
  G_FORMAT_SIZE_IEC_UNITS   = 1 shl 1
}

;gchar
g_format_size_full proto __cdecl \
		  size: guint64,
		 flags: GFormatSizeFlags

;gchar
g_format_size proto __cdecl \
		  size: guint64


;*g_format_size_for_display(goffset
g_format_size_for_display proto __cdecl

ifndef G_DISABLE_DEPRECATED
CALLBACKC(GVoidFunc)
ATEXIT macro p
	exitm<g_ATEXIT(p)>
	endm
g_atexit proto __cdecl :GVoidFunc

ifdef G_OS_WIN32
if (defined(__MINGW_H) AND NOT defined(_STDLIB_H_)) OR (defined(_MSC_VER) AND NOT defined(_INC_STDLIB))
;int
atexit proto __cdecl :ptr
endif
g_atexit macro func
	exitm<atexit(func)>
	endm
endif
endif

if 0
;gchar*
g_find_program_in_path proto __cdecl \
	       program: ptr gchar

g_bit_nth_lsf macro mask, nth_bit
	exitm<g_bit_nth_lsf_impl(mask, nth_bit)>
	endm
g_bit_nth_msf macro mask, nth_bit
	exitm<g_bit_nth_msf_impl(mask, nth_bit)>
	endm
g_bit_storage macro number
	exitm<g_bit_storage_impl(number)>
	endm
else
;gint
g_bit_nth_lsf proto __cdecl \
		  mask: gulong,
	       nth_bit: gint

g_bit_nth_msf proto __cdecl \
		  mask: gulong,
	       nth_bit: gint

g_bit_storage proto __cdecl \
		number: gulong
endif

ifndef G_DISABLE_DEPRECATED
ifndef G_PLATFORM_WIN32
else
endif
endif

endif
