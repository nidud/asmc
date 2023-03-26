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

g_printf_string_upper_bound proto __cdecl :ptr gchar, :ptr

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

CALLBACKC(GLogFunc, :ptr gchar, :GLogLevelFlags, :ptr gchar, :gpointer)

;guint
g_log_set_handler proto __cdecl \
	    log_domain: ptr gchar,
	    log_levels: GLogLevelFlags,
	      log_func: GLogFunc,
	     user_data: gpointer

;guint
g_log_set_handler_full proto __cdecl \
	    log_domain: ptr gchar,
	    log_levels: GLogLevelFlags,
	      log_func: GLogFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
g_log_remove_handler proto __cdecl \
	    log_domain: ptr gchar,
	    handler_id: guint

;void
g_log_default_handler proto __cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
	       message: ptr gchar,
	   unused_data: gpointer

;GLogFunc
g_log_set_default_handler proto __cdecl \
	      log_func: GLogFunc,
	     user_data: gpointer

;void
g_log proto __Cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
		format: ptr gchar,
		      : vararg

;void
g_logv proto __cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
		format: ptr gchar,
		      : ptr

;GLogLevelFlags
g_log_set_fatal_mask proto __cdecl \
	    log_domain: ptr gchar,
	    fatal_mask: GLogLevelFlags

;GLogLevelFlags
g_log_set_always_fatal proto __cdecl \
	    fatal_mask: GLogLevelFlags


.enum GLogWriterOutput {
    G_LOG_WRITER_HANDLED = 1,
    G_LOG_WRITER_UNHANDLED = 0,
    }

GLogField		STRUC
key			ptr gchar ?
value			gconstpointer ?
length			gssize ?
GLogField		ENDS

CALLBACKC(GLogWriterFunc, :GLogLevelFlags, :ptr GLogField, :gsize, :gpointer)

;void
g_log_structured proto __Cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
		      : vararg

;void
g_log_structured_array proto __cdecl \
	     log_level: GLogLevelFlags,
		fields: ptr GLogField,
	      n_fields: gsize


;void
g_log_variant proto __cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
		fields: ptr GVariant


;void
g_log_set_writer_func proto __cdecl \
		  func: GLogWriterFunc,
	     user_data: gpointer,
	user_data_free: GDestroyNotify


;gboolean
g_log_writer_supports_color proto __cdecl \
	     output_fd: gint

;gboolean
g_log_writer_is_journald proto __cdecl \
	     output_fd: gint


;gchar
g_log_writer_format_fields proto __cdecl \
	     log_level: GLogLevelFlags,
		fields: ptr GLogField,
	      n_fields: gsize,
	     use_color: gboolean


;GLogWriterOutput
g_log_writer_journald proto __cdecl \
	     log_level: GLogLevelFlags,
		fields: ptr GLogField,
	      n_fields: gsize,
	     user_data: gpointer

;GLogWriterOutput
g_log_writer_standard_streams proto __cdecl \
	     log_level: GLogLevelFlags,
		fields: ptr GLogField,
	      n_fields: gsize,
	     user_data: gpointer

;GLogWriterOutput
g_log_writer_default proto __cdecl \
	     log_level: GLogLevelFlags,
		fields: ptr GLogField,
	      n_fields: gsize,
	     user_data: gpointer


;void
g_log_writer_default_set_use_stderr proto __cdecl \
	    use_stderr: gboolean

;gboolean
g_log_writer_default_would_drop proto __cdecl \
	     log_level: GLogLevelFlags,
	    log_domain: ptr char_t


;gboolean
g_log_get_debug_enabled proto __cdecl
;void
g_log_set_debug_enabled proto __cdecl \
	       enabled: gboolean


G_DEBUG_HERE macro
	exitm<.err>
	endm


;void
_g_log_fallback_handler proto __cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
	       message: ptr gchar,
	   unused_data: gpointer

g_return_if_fail_warning proto __cdecl \
	    log_domain: ptr char_t,
       pretty_function: ptr char_t,
	    expression: ptr char_t

g_warn_message proto __cdecl \
		domain: ptr char_t,
		  file: ptr char_t,
		  line: SINT,
		  func: ptr char_t,
	      warnexpr: ptr char_t

g_assert_warning proto __cdecl \
	    log_domain: ptr char_t,
		  file: ptr char_t,
		  line: SINT,
       pretty_function: ptr char_t,
	    expression: ptr char_t


g_log_structured_standard proto __Cdecl \
	    log_domain: ptr gchar,
	     log_level: GLogLevelFlags,
		  file: ptr gchar,
		  line: ptr gchar,
		  func: ptr gchar,
	message_format: ptr gchar,
		      : vararg


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

CALLBACKC(GPrintFunc, :ptr gchar)

g_print proto __Cdecl :ptr gchar, :vararg
g_set_print_handler proto __cdecl :GPrintFunc
g_printerr proto __Cdecl :ptr gchar, :vararg
g_set_printerr_handler proto __cdecl :GPrintFunc

g_warn_if_reached macro
	exitm<.err>
	endm
g_warn_if_fail macro expr
	exitm<.err>
	endm

ifdef G_DISABLE_CHECKS

g_return_if_fail macro expr
	exitm<.err>
	endm
g_return_val_if_fail macro expr,val
	exitm<.err>
	endm
g_return_if_reached macro
	exitm<.err>
	endm
g_return_val_if_reached macro val
	exitm<.err>
	endm

else

g_return_if_fail macro expr
	exitm<.err>
	endm
g_return_val_if_fail macro expr, val
	exitm<.err>
	endm
g_return_if_reached macro
	exitm<.err>
	endm
g_return_val_if_reached macro val
	exitm<.err>
	endm
endif

endif
