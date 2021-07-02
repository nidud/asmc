ifndef __G_OPTION_H__
__G_OPTION_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gerror.inc
include glib/gquark.inc

G_BEGIN_DECLS

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

CALLBACKC(GOptionArgFunc, :ptr gchar, :ptr gchar, :gpointer, :ptr ptr GError)
CALLBACKC(GOptionParseFunc, :ptr GOptionContext, :ptr GOptionGroup, :gpointer, :ptr ptr GError)
CALLBACKC(GOptionErrorFunc, :ptr GOptionContext, :ptr GOptionGroup, :gpointer, :ptr ptr GError)

G_OPTION_ERROR equ <g_option_error_quark>

.enum GOptionError {
  G_OPTION_ERROR_UNKNOWN_OPTION,
  G_OPTION_ERROR_BAD_VALUE,
  G_OPTION_ERROR_FAILED
}

;GQuark
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

;GOptionContext
g_option_context_new proto __cdecl \
      parameter_string: ptr gchar

;void
g_option_context_set_summary proto __cdecl \
	       context: ptr GOptionContext,
	       summary: ptr gchar

;const
g_option_context_get_summary proto __cdecl \
	       context: ptr GOptionContext

;void
g_option_context_set_description proto __cdecl \
	       context: ptr GOptionContext,
	   description: ptr gchar

;const
g_option_context_get_description proto __cdecl \
	       context: ptr GOptionContext

;void
g_option_context_free proto __cdecl \
	       context: ptr GOptionContext

;void
g_option_context_set_help_enabled proto __cdecl \
	       context: ptr GOptionContext,
	  help_enabled: gboolean

;gboolean
g_option_context_get_help_enabled proto __cdecl \
	       context: ptr GOptionContext

;void
g_option_context_set_ignore_unknown_options proto __cdecl \
	       context: ptr GOptionContext,
	ignore_unknown: gboolean

;gboolean
g_option_context_get_ignore_unknown_options proto __cdecl \
	       context: ptr GOptionContext


;void
g_option_context_set_strict_posix proto __cdecl \
	       context: ptr GOptionContext,
	  strict_posix: gboolean

;gboolean
g_option_context_get_strict_posix proto __cdecl \
	       context: ptr GOptionContext


;void
g_option_context_add_main_entries proto __cdecl \
	       context: ptr GOptionContext,
	       entries: ptr GOptionEntry,
    translation_domain: ptr gchar

;gboolean
g_option_context_parse proto __cdecl \
	       context: ptr GOptionContext,
		  argc: ptr gint,
		  argv: ptr gchar,
		 error: ptr GError

;gboolean
g_option_context_parse_strv proto __cdecl \
	       context: ptr GOptionContext,
	     arguments: ptr gchar,
		 error: ptr GError

;void
g_option_context_set_translate_func proto __cdecl \
	       context: ptr GOptionContext,
		  func: GTranslateFunc,
		  data: gpointer,
	destroy_notify: GDestroyNotify

;void
g_option_context_set_translation_domain proto __cdecl \
	       context: ptr GOptionContext,
		domain: ptr gchar


;void
g_option_context_add_group proto __cdecl \
	       context: ptr GOptionContext,
		_group: ptr GOptionGroup

;void
g_option_context_set_main_group proto __cdecl \
	       context: ptr GOptionContext,
		_group: ptr GOptionGroup

;GOptionGroup
g_option_context_get_main_group proto __cdecl \
	       context: ptr GOptionContext

;gchar
g_option_context_get_help proto __cdecl \
	       context: ptr GOptionContext,
	     main_help: gboolean,
		_group: ptr GOptionGroup


;GOptionGroup
g_option_group_new proto __cdecl \
		  name: ptr gchar,
	   description: ptr gchar,
      help_description: ptr gchar,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
g_option_group_set_parse_hooks proto __cdecl \
		_group: ptr GOptionGroup,
	pre_parse_func: GOptionParseFunc,
       post_parse_func: GOptionParseFunc

;void
g_option_group_set_error_hook proto __cdecl \
		_group: ptr GOptionGroup,
	    error_func: GOptionErrorFunc

;void
g_option_group_free proto __cdecl \
		_group: ptr GOptionGroup

;GOptionGroup
g_option_group_ref proto __cdecl \
		_group: ptr GOptionGroup

;void
g_option_group_unref proto __cdecl \
		_group: ptr GOptionGroup

;void
g_option_group_add_entries proto __cdecl \
		_group: ptr GOptionGroup,
	       entries: ptr GOptionEntry

;void
g_option_group_set_translate_func proto __cdecl \
		_group: ptr GOptionGroup,
		  func: GTranslateFunc,
		  data: gpointer,
	destroy_notify: GDestroyNotify

;void
g_option_group_set_translation_domain proto __cdecl \
		_group: ptr GOptionGroup,
		domain: ptr gchar

G_END_DECLS

endif
