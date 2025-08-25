ifndef __G_PATTERN_H__
define __G_PATTERN_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_pattern_spec_new proto __cdecl :ptr
g_pattern_spec_free proto __cdecl :ptr
g_pattern_spec_copy proto __cdecl :ptr
g_pattern_spec_equal proto __cdecl :ptr, :ptr
g_pattern_spec_match proto __cdecl :ptr, :gsize, :ptr, :ptr
g_pattern_spec_match_string proto __cdecl :ptr, :ptr
g_pattern_match proto __cdecl :ptr, :guint, :ptr, :ptr
g_pattern_match_string proto __cdecl :ptr, :ptr
g_pattern_match_simple proto __cdecl :ptr, :ptr

endif
