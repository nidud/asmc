ifndef __G_MARKUP_H__
define __G_MARKUP_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include stdarg.inc

include glib/gerror.inc
include glib/gslist.inc

.enum GMarkupError {
    G_MARKUP_ERROR_BAD_UTF8,
    G_MARKUP_ERROR_EMPTY,
    G_MARKUP_ERROR_PARSE,
    G_MARKUP_ERROR_UNKNOWN_ELEMENT,
    G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE,
    G_MARKUP_ERROR_INVALID_CONTENT,
    G_MARKUP_ERROR_MISSING_ATTRIBUTE
    }

G_MARKUP_ERROR equ <g_markup_error_quark>

;GQuark
g_markup_error_quark proto __cdecl

.enum GMarkupParseFlags {
    G_MARKUP_DO_NOT_USE_THIS_UNSUPPORTED_FLAG = 1 shl 0,
    G_MARKUP_TREAT_CDATA_AS_TEXT	      = 1 shl 1,
    G_MARKUP_PREFIX_ERROR_POSITION	      = 1 shl 2,
    G_MARKUP_IGNORE_QUALIFIED		      = 1 shl 3
    }

GMarkupParser		STRUC
start_element		proc :ptr GMarkupParseContext, :ptr gchar, :ptr ptr gchar, :ptr ptr gchar, :gpointer, :ptr GError
end_element		proc :ptr GMarkupParseContext, :ptr gchar, :gpointer, :ptr GError
text			proc :ptr GMarkupParseContext, :ptr gchar, :gsize, :gpointer, :ptr GError
passthrough		proc :ptr GMarkupParseContext, :ptr gchar, :gsize, :gpointer, :ptr GError
error			proc :ptr GMarkupParseContext, :ptr GError, :gpointer
GMarkupParser		ENDS

;GMarkupParseContext
g_markup_parse_context_new proto __cdecl \
		parser: ptr GMarkupParser,
		 flags: GMarkupParseFlags,
	     user_data: gpointer,
     user_data_dnotify: GDestroyNotify

;GMarkupParseContext
g_markup_parse_context_ref proto __cdecl \
	       context: ptr GMarkupParseContext

;void
g_markup_parse_context_unref proto __cdecl \
	       context: ptr GMarkupParseContext

;void
g_markup_parse_context_free proto __cdecl \
	       context: ptr GMarkupParseContext

;gboolean
g_markup_parse_context_parse proto __cdecl \
	       context: ptr GMarkupParseContext,
		  text: ptr gchar,
	      text_len: gssize,
		 error: ptr GError

;void
g_markup_parse_context_push proto __cdecl \
	       context: ptr GMarkupParseContext,
		parser: ptr GMarkupParser,
	     user_data: gpointer

;gpointer
g_markup_parse_context_pop proto __cdecl \
	       context: ptr GMarkupParseContext


;gboolean
g_markup_parse_context_end_parse proto __cdecl \
	       context: ptr GMarkupParseContext,
		 error: ptr GError

;const
g_markup_parse_context_get_element proto __cdecl \
	       context: ptr GMarkupParseContext

;const
g_markup_parse_context_get_element_stack proto __cdecl \
	       context: ptr GMarkupParseContext



;void
g_markup_parse_context_get_position proto __cdecl \
	       context: ptr GMarkupParseContext,
	   line_number: ptr gint,
	   char_number: ptr gint

;gpointer
g_markup_parse_context_get_user_data proto __cdecl \
	       context: ptr GMarkupParseContext



;gchar*
g_markup_escape_text proto __cdecl \
		  text: ptr gchar,
		length: gssize


;gchar
g_markup_printf_escaped proto _CDecl \
		format: ptr char_t,
		      : vararg

;gchar
g_markup_vprintf_escaped proto __cdecl \
		format: ptr char_t,


.enum GMarkupCollectType {
    G_MARKUP_COLLECT_INVALID,
    G_MARKUP_COLLECT_STRING,
    G_MARKUP_COLLECT_STRDUP,
    G_MARKUP_COLLECT_BOOLEAN,
    G_MARKUP_COLLECT_TRISTATE,
    G_MARKUP_COLLECT_OPTIONAL = (1 shl 16)
    }



;gboolean
g_markup_collect_attributes proto _CDecl \
	  element_name: ptr gchar,
       attribute_names: ptr gchar,
      attribute_values: ptr gchar,
		 error: ptr GError,
	    first_type: GMarkupCollectType,
	    first_attr: ptr gchar,
		      : vararg

endif
