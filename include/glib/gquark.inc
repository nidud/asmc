ifndef __G_QUARK_H__
__G_QUARK_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

GQuark	typedef guint32

g_quark_try_string		proto __cdecl :string_t
g_quark_from_static_string	proto __cdecl :string_t
g_quark_from_string		proto __cdecl :string_t
g_quark_to_string		proto __cdecl :GQuark
g_intern_string			proto __cdecl :string_t
g_intern_static_string		proto __cdecl :string_t

G_DEFINE_QUARK macro QN, q_n
	exitm<.err>
	endm

endif
