ifndef __G_MESSAGES_H__
define __G_MESSAGES_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include stdarg.inc
include glib/gatomic.inc
include glib/gtypes.inc
include glib/gmacros.inc
include glib/gvariant.inc

g_printf_string_upper_bound proto __cdecl :ptr, :ptr

define G_LOG_LEVEL_USER_SHIFT 8

.enum GLogLevelFlags {
    G_LOG_FLAG_RECURSION	  = 1 shl 0,
    G_LOG_FLAG_FATAL		  = 1 shl 1,
    G_LOG_LEVEL_ERROR		  = 1 shl 2,
    G_LOG_LEVEL_CRITICAL	  = 1 shl 3,
    G_LOG_LEVEL_WARNING		  = 1 shl 4,
    G_LOG_LEVEL_MESSAGE		  = 1 shl 5,
    G_LOG_LEVEL_INFO		  = 1 shl 6,
    G_LOG_LEVEL_DEBUG		  = 1 shl 7,
    G_LOG_LEVEL_MASK		  = not (G_LOG_FLAG_RECURSION or G_LOG_FLAG_FATAL)
    }


define G_LOG_FATAL_MASK (G_LOG_FLAG_RECURSION OR G_LOG_LEVEL_ERROR)

CALLBACKC(GLogFunc, :ptr, :GLogLevelFlags, :ptr, :gpointer)

g_log_set_handler proto __cdecl :ptr, :GLogLevelFlags, :GLogFunc, :ptr
g_log_set_handler_full proto __cdecl :ptr, :GLogLevelFlags, :GLogFunc, :ptr, :GDestroyNotify
g_log_remove_handler proto __cdecl :ptr, :guint
g_log_default_handler proto __cdecl :ptr, :GLogLevelFlags, :ptr, :ptr
g_log_set_default_handler proto __cdecl :ptr, :ptr
g_log proto __Cdecl :ptr, :GLogLevelFlags, :ptr, :vararg
g_logv proto __cdecl :ptr, :GLogLevelFlags, :ptr, :ptr
g_log_set_fatal_mask proto __cdecl :ptr, :GLogLevelFlags
g_log_set_always_fatal proto __cdecl :GLogLevelFlags

.enum GLogWriterOutput {
    G_LOG_WRITER_HANDLED = 1,
    G_LOG_WRITER_UNHANDLED = 0,
    }

GLogField		STRUC
key			ptr_t ?
value			gconstpointer ?
length			gssize ?
GLogField		ENDS

CALLBACKC(GLogWriterFunc, :GLogLevelFlags, :ptr, :gsize, :gpointer)

g_log_structured proto __Cdecl :ptr, :GLogLevelFlags, :vararg
g_log_structured_array proto __cdecl :GLogLevelFlags, :ptr, :gsize
g_log_variant proto __cdecl :ptr, :GLogLevelFlags, :ptr
g_log_set_writer_func proto __cdecl :GLogWriterFunc, :ptr, :GDestroyNotify
g_log_writer_supports_color proto __cdecl :gint
g_log_writer_is_journald proto __cdecl :gint
g_log_writer_format_fields proto __cdecl :GLogLevelFlags, :ptr, :gsize, :gboolean
g_log_writer_journald proto __cdecl :GLogLevelFlags, :ptr, :gsize, :gpointer
g_log_writer_standard_streams proto __cdecl :GLogLevelFlags, :ptr, :gsize, :gpointer
g_log_writer_default proto __cdecl :GLogLevelFlags, :ptr, :gsize, :gpointer
g_log_writer_default_set_use_stderr proto __cdecl :gboolean
g_log_writer_default_would_drop proto __cdecl :GLogLevelFlags, :ptr
g_log_get_debug_enabled proto __cdecl
g_log_set_debug_enabled proto __cdecl :gboolean

_g_log_fallback_handler proto __cdecl :ptr, :GLogLevelFlags, :ptr, :gpointer
g_return_if_fail_warning proto __cdecl :ptr, :ptr, :ptr
g_warn_message proto __cdecl :ptr, :ptr, :SINT, :ptr, :ptr
g_assert_warning proto __cdecl :ptr, :ptr, :SINT, :ptr, :ptr
g_log_structured_standard proto __Cdecl :ptr, :GLogLevelFlags, :ptr, :ptr, :ptr, :ptr, :vararg

ifndef G_LOG_DOMAIN
define G_LOG_DOMAIN 0
endif

g_error macro args:vararg
  exitm<g_log_structured_standard (G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, __FILE__, G_STRINGIFY (__LINE__), G_STRFUNC, args)>
  endm
g_message macro args:vararg
  exitm<g_log_structured_standard (G_LOG_DOMAIN, G_LOG_LEVEL_MESSAGE, __FILE__, G_STRINGIFY (__LINE__), G_STRFUNC, args)>
  endm
g_critical macro args:vararg
  exitm<g_log_structured_standard (G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, __FILE__, G_STRINGIFY (__LINE__), G_STRFUNC, args)>
  endm
g_warning macro args:vararg
  exitm<g_log_structured_standard (G_LOG_DOMAIN, G_LOG_LEVEL_WARNING, __FILE__, G_STRINGIFY (__LINE__), G_STRFUNC, args)>
  endm
g_info macro args:vararg
  exitm<g_log_structured_standard (G_LOG_DOMAIN, G_LOG_LEVEL_INFO, __FILE__, G_STRINGIFY (__LINE__), G_STRFUNC, args)>
  endm
g_debug macro args:vararg
  exitm<g_log_structured_standard (G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG, __FILE__, G_STRINGIFY (__LINE__), G_STRFUNC, args)>
  endm

CALLBACKC(GPrintFunc, :ptr)

g_print proto __Cdecl :ptr, :vararg
g_set_print_handler proto __cdecl :GPrintFunc
g_printerr proto __Cdecl :ptr, :vararg
g_set_printerr_handler proto __cdecl :GPrintFunc

endif
