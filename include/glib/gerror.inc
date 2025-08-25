ifndef __G_ERROR_H__
define __G_ERROR_H__
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include stdarg.inc

include glib/gquark.inc

GError	STRUC
domain	GQuark ?
code	gint ?
message ptr_t ?
GError	ENDS

g_error_new proto __Cdecl :GQuark, :gint, :ptr, :vararg
g_error_new_literal proto __cdecl :GQuark, :gint, :ptr
g_error_new_valist proto __cdecl :GQuark, :gint, :ptr, :vararg
g_error_free proto __cdecl :ptr
g_error_copy proto __cdecl :ptr
g_error_matches proto __cdecl :ptr, :GQuark, :gint
g_set_error proto __Cdecl :ptr, :GQuark, :gint, :ptr, :vararg
g_set_error_literal proto __cdecl :ptr, :GQuark, :gint, :ptr
g_propagate_error proto __cdecl :ptr, :ptr
g_clear_error proto __cdecl :ptr
g_prefix_error proto __Cdecl :ptr, :ptr, :vararg
g_propagate_prefixed_error proto __Cdecl :ptr, :ptr, :ptr, :vararg

endif
