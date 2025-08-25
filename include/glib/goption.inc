ifndef __G_OPTION_H__
define __G_OPTION_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc
include glib/gquark.inc

.enum GOptionFlags {
  G_OPTION_FLAG_NONE		= 0,
  G_OPTION_FLAG_HIDDEN		= 1 shl 0,
  G_OPTION_FLAG_IN_MAIN		= 1 shl 1,
  G_OPTION_FLAG_REVERSE		= 1 shl 2,
  G_OPTION_FLAG_NO_ARG		= 1 shl 3,
  G_OPTION_FLAG_FILENAME	= 1 shl 4,
  G_OPTION_FLAG_OPTIONAL_ARG	= 1 shl 5,
  G_OPTION_FLAG_NOALIAS		= 1 shl 6
}

.enum GOptionArg {
  G_OPTION_ARG_NONE,
  G_OPTION_ARG_STRING,
  G_OPTION_ARG_INT,
  G_OPTION_ARG_CALLBACK,
  G_OPTION_ARG_FILENAME,
  G_OPTION_ARG_STRING_ARRAY,
  G_OPTION_ARG_FILENAME_ARRAY,
  G_OPTION_ARG_DOUBLE,
  G_OPTION_ARG_INT64
}

CALLBACKC(GOptionArgFunc, :ptr, :ptr, :gpointer, :ptr)
CALLBACKC(GOptionParseFunc, :ptr, :ptr, :gpointer, :ptr)
CALLBACKC(GOptionErrorFunc, :ptr, :ptr, :gpointer, :ptr)

G_OPTION_ERROR equ <g_option_error_quark>

.enum GOptionError {
  G_OPTION_ERROR_UNKNOWN_OPTION,
  G_OPTION_ERROR_BAD_VALUE,
  G_OPTION_ERROR_FAILED
}

g_option_error_quark proto __cdecl

GOptionEntry		STRUC
long_name		string_t ?
short_name		gchar ?
flags			gint ?
arg			GOptionArg ?
arg_data		gpointer ?
description		string_t ?
arg_description		string_t ?
GOptionEntry		ENDS

G_OPTION_REMAINING	equ <"">

g_option_context_new proto __cdecl :ptr
g_option_context_set_summary proto __cdecl :ptr, :ptr
g_option_context_get_summary proto __cdecl :ptr
g_option_context_set_description proto __cdecl :ptr, :ptr
g_option_context_get_description proto __cdecl :ptr
g_option_context_free proto __cdecl :ptr
g_option_context_set_help_enabled proto __cdecl :ptr, :gboolean
g_option_context_get_help_enabled proto __cdecl :ptr
g_option_context_set_ignore_unknown_options proto __cdecl :ptr, :gboolean
g_option_context_get_ignore_unknown_options proto __cdecl :ptr
g_option_context_set_strict_posix proto __cdecl :ptr, :gboolean
g_option_context_get_strict_posix proto __cdecl :ptr
g_option_context_add_main_entries proto __cdecl :ptr, :ptr, :ptr
g_option_context_parse proto __cdecl :ptr, :ptr, :ptr, :ptr
g_option_context_parse_strv proto __cdecl :ptr, :ptr, :ptr
g_option_context_set_translate_func proto __cdecl :ptr, :GTranslateFunc, :gpointer, :GDestroyNotify
g_option_context_set_translation_domain proto __cdecl :ptr, :ptr
g_option_context_add_group proto __cdecl :ptr, :ptr
g_option_context_set_main_group proto __cdecl :ptr, :ptr
g_option_context_get_main_group proto __cdecl :ptr
g_option_context_get_help proto __cdecl :ptr, :gboolean, :ptr
g_option_group_new proto __cdecl :ptr, :ptr, :ptr, :gpointer, :GDestroyNotify
g_option_group_set_parse_hooks proto __cdecl :ptr, :GOptionParseFunc, :GOptionParseFunc
g_option_group_set_error_hook proto __cdecl :ptr, :GOptionErrorFunc
g_option_group_free proto __cdecl :ptr
g_option_group_ref proto __cdecl :ptr
g_option_group_unref proto __cdecl :ptr
g_option_group_add_entries proto __cdecl :ptr, :ptr
g_option_group_set_translate_func proto __cdecl :ptr, :GTranslateFunc, :gpointer, :GDestroyNotify
g_option_group_set_translation_domain proto __cdecl :ptr, :ptr

endif
