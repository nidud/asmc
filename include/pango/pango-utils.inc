ifndef __PANGO_UTILS_H__
define __PANGO_UTILS_H__

include stdio.inc
include glib.inc
include pango/pango-font.inc

pango_split_file_list proto :ptr
pango_trim_string proto :ptr
pango_read_line proto :ptr, :ptr
pango_skip_space proto :ptr
pango_scan_word proto :ptr, :ptr
pango_scan_string proto :ptr, :ptr
pango_scan_int proto :ptr, :ptr
pango_parse_enum proto :GType, :ptr, :ptr, :gboolean, :ptr
pango_parse_style proto :ptr, :ptr, :gboolean
pango_parse_variant proto :ptr, :ptr, :gboolean
pango_parse_weight proto :ptr, :ptr, :gboolean
pango_parse_stretch proto :ptr, :ptr, :gboolean
pango_quantize_line_geometry proto :ptr, :ptr
pango_log2vis_get_embedding_levels proto :ptr, :sdword, :ptr
pango_is_zero_width proto :gunichar
pango_find_paragraph_boundary proto :ptr, :sdword, :ptr, :ptr

PANGO_VERSION_ENCODE macro major, minor, micro
  exitm<.err>
  endm

define PANGO_VERSION PANGO_VERSION_ENCODE(PANGO_VERSION_MAJOR, PANGO_VERSION_MINOR, PANGO_VERSION_MICRO)

PANGO_VERSION_CHECK macro major,minor,micro
  exitm<(PANGO_VERSION >= PANGO_VERSION_ENCODE(major,minor,micro))>
  endm

pango_version proto
pango_version_string proto
pango_version_check proto :sdword, :sdword, :sdword

endif
