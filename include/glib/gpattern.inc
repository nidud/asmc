ifndef __G_PATTERN_H__
define __G_PATTERN_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

;GPatternSpec*
g_pattern_spec_new proto __cdecl \
               pattern: ptr gchar

;void
g_pattern_spec_free proto __cdecl \
                 pspec: ptr GPatternSpec

;GPatternSpec
g_pattern_spec_copy proto __cdecl \
                 pspec: ptr GPatternSpec

;gboolean
g_pattern_spec_equal proto __cdecl \
                pspec1: ptr GPatternSpec,
                pspec2: ptr GPatternSpec

;gboolean
g_pattern_spec_match proto __cdecl \
                 pspec: ptr GPatternSpec,
         string_length: gsize,
                string: ptr gchar,
       string_reversed: ptr gchar

;gboolean
g_pattern_spec_match_string proto __cdecl \
                 pspec: ptr GPatternSpec,
                string: ptr gchar

g_pattern_match proto __cdecl \
                 pspec: ptr GPatternSpec,
         string_length: guint,
                string: ptr gchar,
       string_reversed: ptr gchar


g_pattern_match_string proto __cdecl \
                 pspec: ptr GPatternSpec,
                string: ptr gchar

;gboolean
g_pattern_match_simple proto __cdecl \
               pattern: ptr gchar,
                string: ptr gchar


endif
