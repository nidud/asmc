ifndef __G_ERROR_H__
__G_ERROR_H__ equ <>
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

;GError*
g_error_new proto _CDecl \
		domain: GQuark,
		  code: gint,
		format: ptr gchar,
		      : vararg


;GError*
g_error_new_literal proto __cdecl \
		domain: GQuark,
		  code: gint,
	       message: ptr gchar

;GError*
g_error_new_valist proto __cdecl \
		domain: GQuark,
		  code: gint,
		format: ptr gchar,
		      : vararg


;void
g_error_free proto __cdecl \
		 error: ptr GError

;GError*
g_error_copy proto __cdecl \
		 error: ptr GError

;gboolean
g_error_matches proto __cdecl \
		 error: ptr GError,
		domain: GQuark,
		  code: gint

g_set_error proto _CDecl \
		   err: ptr GError,
		domain: GQuark,
		  code: gint,
		format: ptr gchar,
		      : vararg

g_set_error_literal proto __cdecl \
		   err: ptr GError,
		domain: GQuark,
		  code: gint,
	       message: ptr gchar


g_propagate_error proto __cdecl \
		  dest: ptr GError,
		   src: ptr GError


g_clear_error proto __cdecl \
		   err: ptr GError


g_prefix_error proto _CDecl \
		   err: ptr GError,
		format: ptr gchar,
		      : vararg


g_propagate_prefixed_error proto _CDecl \
		  dest: ptr GError,
		   src: ptr GError,
		format: ptr gchar,
		      : vararg

endif
