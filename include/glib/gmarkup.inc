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

g_markup_error_quark proto __cdecl

.enum GMarkupParseFlags {
    G_MARKUP_DO_NOT_USE_THIS_UNSUPPORTED_FLAG = 1 shl 0,
    G_MARKUP_TREAT_CDATA_AS_TEXT	      = 1 shl 1,
    G_MARKUP_PREFIX_ERROR_POSITION	      = 1 shl 2,
    G_MARKUP_IGNORE_QUALIFIED		      = 1 shl 3
    }

GMarkupParser		STRUC
start_element		proc :ptr, :ptr, :ptr, :ptr, :gpointer, :ptr
end_element		proc :ptr, :ptr, :gpointer, :ptr
text			proc :ptr, :ptr, :gsize, :gpointer, :ptr
passthrough		proc :ptr, :ptr, :gsize, :gpointer, :ptr
error			proc :ptr, :ptr, :gpointer
GMarkupParser		ENDS

g_markup_parse_context_new proto __cdecl :ptr, :GMarkupParseFlags, :gpointer, :GDestroyNotify
g_markup_parse_context_ref proto __cdecl :ptr
g_markup_parse_context_unref proto __cdecl :ptr
g_markup_parse_context_free proto __cdecl :ptr
g_markup_parse_context_parse proto __cdecl :ptr, :ptr, :gssize, :ptr
g_markup_parse_context_push proto __cdecl :ptr, :ptr, :ptr
g_markup_parse_context_pop proto __cdecl :ptr
g_markup_parse_context_end_parse proto __cdecl :ptr, :ptr
g_markup_parse_context_get_element proto __cdecl :ptr
g_markup_parse_context_get_element_stack proto __cdecl :ptr
g_markup_parse_context_get_position proto __cdecl :ptr, :ptr, :ptr
g_markup_parse_context_get_user_data proto __cdecl :ptr
g_markup_escape_text proto __cdecl :ptr, :gssize
g_markup_printf_escaped proto __Cdecl :ptr, :vararg
g_markup_vprintf_escaped proto __cdecl :ptr, :ptr


.enum GMarkupCollectType {
    G_MARKUP_COLLECT_INVALID,
    G_MARKUP_COLLECT_STRING,
    G_MARKUP_COLLECT_STRDUP,
    G_MARKUP_COLLECT_BOOLEAN,
    G_MARKUP_COLLECT_TRISTATE,
    G_MARKUP_COLLECT_OPTIONAL = (1 shl 16)
    }

g_markup_collect_attributes proto __Cdecl :ptr, :ptr, :ptr, :ptr, :GMarkupCollectType, :ptr, :vararg

endif
